#ifndef COMMANDNOTFOUND_H
#define COMMANDNOTFOUND_H
#include "icommand.h"

class CommandNotFound : public ICommand
{
public:
    CommandNotFound();
    void read(char c);
    bool execute();
};

#endif // COMMANDNOTFOUND_H
