#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>
#include "../Socket.h"

class ICommand
{
public:
    ICommand();
    virtual ~ICommand();
    void setSocket(Socket* s);
    virtual void read(char* c) = 0;
    virtual bool execute() = 0;

    //properties
    Socket* sock;
};

#endif // ICOMMAND_H
