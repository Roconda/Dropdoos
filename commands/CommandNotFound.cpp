#include "CommandNotFound.h"

CommandNotFound::CommandNotFound()
{
}

void CommandNotFound::read(char* c){
    return;
}

bool CommandNotFound::execute() {
	sock->write("2\r\n");
    return true;
}
