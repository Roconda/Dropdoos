/*
 * CommandDir.h
 *
 *  Created on: Jan 22, 2014
 *      Author: tim
 */

#ifndef COMMANDDIR_H_
#define COMMANDDIR_H_

#include "ICommand.h"

class CommandDir : public ICommand {
public:
	CommandDir();
    void read(char c);
    bool execute();
};

#endif /* COMMANDDIR_H_ */
