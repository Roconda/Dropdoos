#include "icommand.h"


ICommand::ICommand()
{
}

void ICommand::setSocket(Socket* s) {
	this->sock = s;
}
