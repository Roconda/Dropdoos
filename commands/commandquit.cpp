#include "commandquit.h"

CommandQuit::CommandQuit()
{
}

void CommandQuit::read(char c){

}

bool CommandQuit::execute() {
	sock->writeline("0");
    sock->close();

    return false;
}
