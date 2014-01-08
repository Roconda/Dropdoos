#include "commandnotfound.h"

CommandNotFound::CommandNotFound()
{
}

void CommandNotFound::read(char c){
    return;
}

string CommandNotFound::execute() {
    return "Command not found\r\n";
}
