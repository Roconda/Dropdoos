#ifndef COMMANDINFO_H
#define COMMANDINFO_H

#include "ICommand.h"
#include <string>
#include "../Socket.h"

class CommandInfo : public ICommand
{
public:
    CommandInfo();
    void read(char* c);
    bool execute();
};

#endif // COMMANDINFO_H
