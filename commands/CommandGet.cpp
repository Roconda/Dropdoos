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
#include <string.h>

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
	if(!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
		sock->writeline("1");
		return true;
	}

	sock->writeline("0");

	int buffSize = 10240;
	long fzCounter = 0;  // counts if we reached the filesize
	ifstream filestream(filePath.c_str(), ios::binary);

	// create stream
	ostringstream stream;
	long filesize = fs::file_size(filePath);

	if(filestream.is_open()) {
		char* defaultBuffer = new char[buffSize];

		filestream.seekg(filestream.beg);

		while(fzCounter != filesize) {

			if((filesize-fzCounter) >= buffSize) {
				// Chunk is large enough, use default buffer
				filestream.read(defaultBuffer, buffSize);
				sock->write(defaultBuffer, buffSize);

				fzCounter += buffSize;
			}else{
				// Chunk is too small, create a tiny buffer
				int remainder = filesize-fzCounter;

				// create small buffer
				char* smallBuff = new char[remainder];

				filestream.read(smallBuff, remainder);
				sock->write(smallBuff, remainder);

				fzCounter += remainder;

				delete [] smallBuff;
			}

		}

		delete [] defaultBuffer;

		filestream.close();
		sock->writeline("0");

		return true;
	}else{
		filestream.close();
		sock->writeline("10");

		return true;
	}

}
