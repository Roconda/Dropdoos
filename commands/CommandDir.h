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
	~CommandDir();
    void read(char* c);
    bool execute();

    //properties
    string choosenDirectory;
};

#endif /* COMMANDDIR_H_ */
