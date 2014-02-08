/*
 * CommandGet.h
 *
 *  Created on: Feb 5, 2014
 *      Author: tim
 */

#ifndef COMMANDGET_H_
#define COMMANDGET_H_

#include "ICommand.h"
#include "../Settings.h"

class CommandGet : public ICommand {
	public:
		CommandGet();
		~CommandGet();
		void read(char* c);
		bool execute();
	private:
		string file;
};

#endif /* COMMANDGET_H_ */
