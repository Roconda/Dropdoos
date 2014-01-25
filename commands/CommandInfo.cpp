#include "CommandInfo.h"
#include <iostream>

using namespace std;

CommandInfo::CommandInfo()
{
}

void CommandInfo::read(char* c){

}

bool CommandInfo::execute() {
	sock->writeline("0");
	sock->writeline(":Dropdoos version 0.1");
	sock->writeline("0");
	return true;
}
