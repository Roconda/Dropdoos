/*
 * CommandRen.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: tim
 */

#include "boost/filesystem/operations.hpp"

#include "CommandRen.h"
#include "../Settings.h"

namespace fs = boost::filesystem;

CommandRen::CommandRen(){
	src = "";
	dest = "";
}

CommandRen::~CommandRen(){

}

void CommandRen::read(char* c){

	if(src.empty())
		src = string(c);
	else
		dest = string(c);
}

bool CommandRen::execute(){
	string absRoot = string(Settings::getInstance().getCwd());

	// Check if both properties are set and aren't equal
	if((src.empty() || dest.empty()) || src.compare(dest) == 0)
		sock->writeline("2");
	else if(!fs::exists(string(absRoot).append(src).c_str()))
		sock->writeline("1");
	else{
		fs::rename(string(absRoot).append(src).c_str(), string(absRoot).append(dest).c_str());
		sock->writeline("0");
	}


	return true;
}
