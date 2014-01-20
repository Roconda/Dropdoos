#ifndef COMMANDINFO_H
#define COMMANDINFO_H

#include "icommand.h"
#include <string>
#include "../Socket.h"

class CommandInfo : public ICommand
{
public:
    CommandInfo();
    void read(char c);
    std::string execute();
};

#endif // COMMANDINFO_H
