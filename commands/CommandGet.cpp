/*
 * CommandGet.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: tim
 */
#include "boost/filesystem/operations.hpp"
#include <inttypes.h>
#include <sstream>
#include <fstream>

#include "CommandGet.h"
#include "../Settings.h"

namespace fs = boost::filesystem;

CommandGet::CommandGet(){
	file = "";
}

CommandGet::~CommandGet(){

}

void CommandGet::read(char* c){
	file = string(c);
}

bool CommandGet::execute(){
	string root = Settings::getInstance().getCwd();
	string filePath = string(root).append(file);

	// GET requested file does not exist.
	if(!fs::exists(filePath)) {
		sock->writeline("1");
		return true;
	}

	sock->writeline("0");

	// get filesize
	ostringstream stream;
	long filesize = fs::file_size(filePath);
	stream << filesize;

	// return filesize to client
	sock->writeline((stream.str()).c_str());

	int buffSize = 1024;
	long fzCounter = 0;  // counts if we reached the filesize
	ifstream filestream(filePath.c_str(), ifstream::binary);


	if(filestream.is_open()) {
		char* defaultBuffer = new char[buffSize];

		while(fzCounter != filesize) {
			if((filesize-fzCounter) >= buffSize) {
				filestream.read(defaultBuffer, sizeof(defaultBuffer));
				sock->write(defaultBuffer);
				fzCounter += buffSize;
			}else{
				// create small buffer
				char* smallBuff = new char[filesize-fzCounter];

				filestream.read(smallBuff, sizeof(smallBuff));
				sock->write(smallBuff);
				fzCounter += filesize-fzCounter;

				delete [] smallBuff;
			}
		}

		delete [] defaultBuffer;
		sock->writeline("0");
		filestream.close();
		return true;
	}

	sock->writeline("10");
	filestream.close();
	return true;
}
