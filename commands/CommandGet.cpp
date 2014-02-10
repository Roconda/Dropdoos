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

	// get filesize
	ostringstream stream;
	long filesize = fs::file_size(filePath);

	if(filestream.is_open()) {
		char* defaultBuffer = new char[buffSize];

		ofstream ostr("/tmp/foto.png" , ios::binary);
		ostr.seekp(0);

		while(fzCounter != filesize) {

			if((filesize-fzCounter) >= buffSize) {
				filestream.read(defaultBuffer, sizeof(defaultBuffer));
				ostr << filestream.rdbuf();
				//sock->write(defaultBuffer);
				fzCounter += buffSize;
			}else{
				int remainder = filesize-fzCounter;

				// create small buffer
				char* smallBuff = new char[remainder];

				filestream.read(smallBuff, sizeof(smallBuff));
				ostr << filestream.rdbuf();
				//sock->write(smallBuff);
				fzCounter += remainder;

				ostr.close();
				delete [] smallBuff;
			}

			filestream.clear();
		}

		delete [] defaultBuffer;
		filestream.close();
		ostr.close();
		sock->writeline("0");

		return true;
	}else{
		filestream.close();
		sock->writeline("10");

		return true;
	}

}
