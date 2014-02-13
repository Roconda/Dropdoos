/*
 * CommandSync.cpp
 *
 *  Created on: Feb 13, 2014
 *      Author: tim
 */
#include <sstream>

#include "boost/filesystem/operations.hpp"

#include "../Settings.h"
#include "CommandSync.h"

namespace fs = boost::filesystem;

CommandSync::CommandSync() : dir(""){

}

CommandSync::~CommandSync(){

}

void CommandSync::read(char* c){
	dir = string(c);
}

bool CommandSync::execute(){
	string absolutePath = string(Settings::getInstance().getCwd()).append(dir);
	fs::directory_iterator end_iter;

	if(!fs::exists(absolutePath) || !fs::is_directory(absolutePath)) {
		sock->writeline("1");
		return true;
	}

	// we are good to go!
	sock->writeline("0");

	for( fs::directory_iterator dir_iter(absolutePath) ; dir_iter != end_iter ; ++dir_iter) {
		if (fs::is_regular_file(dir_iter->status()) || fs::is_directory(dir_iter->status()) ) {
			stringstream ss;
			ss << fs::last_write_time(dir_iter->path());

			sock->writeline(dir_iter->path().filename().c_str());
			sock->writeline(ss.str().c_str());
			sock->writeline("NF");
		}
	}

	sock->writeline("EOF");
	sock->writeline("0");

	return true;
}
