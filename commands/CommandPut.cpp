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

	sock->writeline("0");

	if(stream.is_open()) {
		char* buffer = new char[buffSize];
		int timer = 0;
		while(fzCounter != fSize) {
			timer++;
			if((fSize-fzCounter) >= buffSize) {
				// incoming file is at least the buffer's size
				sock->read(buffer, buffSize);
				stream.write(buffer, buffSize);

				fzCounter += buffSize;
			}else{
				// incoming file is smaller than the buffer's size
				int smallbuffSize = fSize - fzCounter;
				char* smallBuffer = new char[smallbuffSize];

				sock->read(smallBuffer, smallbuffSize);
				stream.write(smallBuffer, smallbuffSize);

				fzCounter += smallbuffSize;

				delete [] smallBuffer;
			}
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
}
