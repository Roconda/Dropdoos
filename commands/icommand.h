#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>
#include <regex>
#include "Socket.h"

class ICommand
{
public:
    ICommand();
    virtual void read(char c) = 0;
    virtual std::string execute() = 0;
};

#endif // ICOMMAND_H
