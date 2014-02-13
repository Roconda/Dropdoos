/*
 * CommandCreate.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: tim
 */
#include "boost/filesystem/operations.hpp"

#include "CommandCreate.h"
#include "../Settings.h"

namespace fs = boost::filesystem;

CommandCreate::CommandCreate(){
	directory = "";
}

CommandCreate::~CommandCreate(){

}

void CommandCreate::read(char* c){
	directory = string(c);
}

bool CommandCreate::execute(){
	string fullPath = string(Settings::getInstance().getCwd()).append(directory);

	if(directory.empty())
		sock->writeline("3");
	else if(fs::create_directories(fullPath.c_str()))
		sock->writeline("0");
	else if(fs::is_directory(fullPath.c_str()))
		sock->writeline("0");
	else
		sock->writeline("10");

	return true;
}
