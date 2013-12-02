#include "commandinfo.h"
#include <iostream>

using namespace std;

CommandInfo::CommandInfo()
{
}

bool CommandInfo::isCommand(const std::string* command){
    return true;
}

void CommandInfo::read(char c){

}

string CommandInfo::execute() {
    return "Het werkt!\r\n";
}
