/*
 * CommandDel.cpp
 *
 *  Created on: Jan 28, 2014
 *      Author: tim
 */

#include "boost/filesystem/operations.hpp"

#include "CommandDel.h"
#include "../Settings.h"

namespace fs = boost::filesystem;

CommandDel::CommandDel() {
	file = "";
}

void CommandDel::read(char* c) {
	file = string(c).c_str();
}

bool CommandDel::execute() {
	string absFile = string(Settings::getInstance().getCwd()).append(file).c_str();

	// check for argument
	if(file.empty()) {
		sock->writeline("3");
		return true;
	}

	// check if file exists, otherwise return errorno
	if(!fs::exists(absFile)){
		sock->write("1");
		return true;
	}

	if(fs::is_directory(file)) {
		// remove directory

		if(fs::remove_all(absFile))
			sock->writeline("0");
		else
			sock->writeline("10");
	}else if(fs::is_regular_file(file)) {
		// remove file

		if(fs::remove(absFile) == 1)
			sock->writeline("0");
		else
			sock->writeline("10");
	}else
		sock->writeline("1"); // not a regular file or directory

	return true;
}

CommandDel::~CommandDel(){

}
