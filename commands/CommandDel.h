/*
 * CommandDel.h
 *
 *  Created on: Jan 28, 2014
 *      Author: tim
 */

#ifndef COMMANDDEL_H_
#define COMMANDDEL_H_
#include "ICommand.h"

class CommandDel : public ICommand {
	public :
		CommandDel();
		~CommandDel();
		void read(char* c);
		bool execute();

	private:
		// Chosen file
		string file;
};

#endif /* COMMANDDEL_H_ */
