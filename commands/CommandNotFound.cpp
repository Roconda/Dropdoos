#include "CommandNotFound.h"

CommandNotFound::CommandNotFound()
{
}

void CommandNotFound::read(char* c){
    return;
}

bool CommandNotFound::execute() {
	sock->writeline("2");
    return true;
}
