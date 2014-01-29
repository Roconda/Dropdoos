/*
 * CommandRen.h
 *
 *  Created on: Jan 29, 2014
 *      Author: tim
 */

#ifndef COMMANDREN_H_
#define COMMANDREN_H_

#include "ICommand.h"

class CommandRen : public ICommand {
public :
	CommandRen();
	~CommandRen();
	void read(char* c);
	bool execute();

private:
	string src; // source file
	string dest; // destination file
};

#endif /* COMMANDREN_H_ */
