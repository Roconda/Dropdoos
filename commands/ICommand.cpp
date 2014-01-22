#include "ICommand.h"


ICommand::ICommand()
{
}

void ICommand::setSocket(Socket* s) {
	this->sock = s;
}


ICommand::~ICommand() {

}
