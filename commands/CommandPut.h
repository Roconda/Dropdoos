/*
 * CommandPut.h
 *
 *  Created on: Feb 13, 2014
 *      Author: tim
 */

#ifndef COMMANDPUT_H_
#define COMMANDPUT_H_

#include "ICommand.h"

class CommandPut : public ICommand {
public:
	CommandPut();
	~CommandPut();
	void read(char* c);
	bool execute();
private:
	string file;
	long fSize;
};

#endif /* COMMANDPUT_H_ */
