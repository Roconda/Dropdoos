/*
 * CommandPut.cpp
 *
 *  Created on: Feb 13, 2014
 *      Author: tim
 */

#include <stdlib.h>
#include <fstream>

#include "boost/filesystem/operations.hpp"

#include "CommandPut.h"
#include "../Settings.h"

namespace fs = boost::filesystem;

CommandPut::CommandPut() : file(""), fSize(0){

}

CommandPut::~CommandPut(){

}

void CommandPut::read(char* c){
	if(file.empty()) file = string(c);
	else fSize = strtol(c, NULL, 10);
}

bool CommandPut::execute(){
	string absolutePath = string(Settings::getInstance().getCwd()).append(file.c_str());

	cout << fSize << endl;

	if(file.empty()) {
		sock->writeline("2");
		return true;
	}

	int buffSize = 10240;

	ofstream stream(absolutePath, std::fstream::binary);

	long fzCounter = 0;

	if(stream.is_open()) {
		char* buffer = new char[buffSize];

		while(fzCounter != fSize) {
			if((fSize-fzCounter) >= buffSize) {
				// incoming file is at least the buffer's size
				sock->read(buffer, buffSize);
				stream.write(buffer, buffSize);
				cout << buffer;
				fzCounter += buffSize;
			}else{
				// incoming file is smaller than the buffer's size
				int smallbuffSize = fSize - fzCounter;
				char* smallBuffer = new char[smallbuffSize];

				sock->read(smallBuffer, smallbuffSize);
				stream.write(smallBuffer, smallbuffSize);
				cout << smallBuffer;

				fzCounter += smallbuffSize;

				delete [] smallBuffer;
			}
			cout << "FZ: " << fzCounter << endl;
		}

		delete [] buffer;
	}else{
		// Could not open file stream
		sock->writeline("10");
		return true;
	}

	stream.close();

	sock->writeline("0");
	return true;



	sock->writeline(absolutePath.c_str());

	return true;
}
