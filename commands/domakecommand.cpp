#include "domakecommand.h"
#include "commandquit.h"
#include "commandinfo.h"
#include "commandnotfound.h"
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
