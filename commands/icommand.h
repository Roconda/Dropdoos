#ifndef ICOMMAND_H
#define ICOMMAND_H

#include<string>

class ICommand
{
public:
    ICommand();
    virtual bool isCommand(const std::string* command) = 0;
    virtual void read(char c) = 0;
    virtual std::string execute() = 0;
};

#endif // ICOMMAND_H
