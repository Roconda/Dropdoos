#include "DoMakeCommand.h"
#include "CommandQuit.h"
#include "CommandInfo.h"
#include "CommandNotFound.h"
#include "string.h"
#include "iostream"

DoMakeCommand::DoMakeCommand()
{
}

ICommand* DoMakeCommand::makeCommand(std::string& name) {
	if(name.compare("QUIT") == 0)
		return new CommandQuit();
	else if(name.compare("INFO") == 0){
		return new CommandInfo();
	}
	else
		return new CommandNotFound();
}
