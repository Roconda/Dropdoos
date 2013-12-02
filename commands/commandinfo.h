#ifndef COMMANDINFO_H
#define COMMANDINFO_H

#include "icommand.h"
#include <string>

class CommandInfo : public ICommand
{
public:
    CommandInfo();
    bool isCommand(const std::string* command);
    void read(char c);
    std::string execute();
};

#endif // COMMANDINFO_H
