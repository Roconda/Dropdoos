#include "commandquit.h"

CommandQuit::CommandQuit()
{
}

void CommandQuit::read(char c){

}

bool CommandQuit::execute() {
    sock->close();

    return false;
}
