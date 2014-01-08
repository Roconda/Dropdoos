#ifndef COMMANDQUIT_H
#define COMMANDQUIT_H
#include "icommand.h"
#include "Socket.h"
#include <string>

class CommandQuit : public ICommand
{
public:
    CommandQuit();
    bool isCommand(const std::string* command);
    void read(char c);
    std::string execute();
};

#endif // COMMANDQUIT_H
