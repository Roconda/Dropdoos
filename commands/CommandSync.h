/*
 * CommandSync.h
 *
 *  Created on: Feb 13, 2014
 *      Author: tim
 */

#ifndef COMMANDSYNC_H_
#define COMMANDSYNC_H_

#include "ICommand.h"

class CommandSync : public ICommand {
public:
	CommandSync();
	~CommandSync();
	void read(char* c);
	bool execute();
private:
	string dir;
};

#endif /* COMMANDSYNC_H_ */
