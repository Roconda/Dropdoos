#ifndef DOMAKECOMMAND_H
#define DOMAKECOMMAND_H

#include "icommand.h"

class DoMakeCommand
{
public:
    DoMakeCommand();
    static ICommand* makeCommand(std::string&);
};

#endif // DOMAKECOMMAND_H
