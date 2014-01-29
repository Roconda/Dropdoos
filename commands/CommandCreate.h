/*
 * CommandCreate.h
 *
 *  Created on: Jan 29, 2014
 *      Author: tim
 */

#ifndef COMMANDCREATE_H_
#define COMMANDCREATE_H_

#include "ICommand.h"

class CommandCreate : public ICommand {
public :
	CommandCreate();
	~CommandCreate();
	void read(char* c);
	bool execute();

private:
	// Chosen dir
	string directory;
};

#endif /* COMMANDCREATE_H_ */
