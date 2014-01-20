#include "domakecommand.h"
#include "commandquit.h"
#include "commandnotfound.h"
#include "string.h"
#include "iostream"

DoMakeCommand::DoMakeCommand()
{
}

ICommand* DoMakeCommand::makeCommand(std::string& name) {
	if(name.compare("quit") == 0)
		return new CommandQuit();
	else
		return new CommandNotFound();
}
