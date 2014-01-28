/*
 * CommandDir.cpp
 *
 *  Created on: Jan 22, 2014
 *      Author: tim
 */

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"

#include <iostream>
#include <string>

#include "../Settings.h"
#include "CommandDir.h"

namespace fs = boost::filesystem;

CommandDir::CommandDir() {
	choosenDirectory = "";
}

void CommandDir::read(char* c){
	choosenDirectory = string(c);
}

bool CommandDir::execute() {
	fs::directory_iterator end_iter;
	const char* fullPathBuff;

	// command recognized
	sock->writeline("0");

	if(choosenDirectory.size() == 0)
		fullPathBuff = string(Settings::getInstance().getCwd()).c_str();
	else
		fullPathBuff = string(Settings::getInstance().getCwd()).append(choosenDirectory).c_str();

	// check if path exists and is a directory
	if(!fs::exists(fullPathBuff) || !fs::is_directory(fullPathBuff)) {
		sock->writeline("1");
		return true;
	}

	for( fs::directory_iterator dir_iter(fullPathBuff) ; dir_iter != end_iter ; ++dir_iter) {
		if (fs::is_regular_file(dir_iter->status()) || fs::is_directory(dir_iter->status()) ) {
			std::string buff(":");
			sock->writeline(buff.append(dir_iter->path().filename().c_str()).c_str());
		}
	}

	sock->writeline("0");
	return true;
}

CommandDir::~CommandDir(){
}
