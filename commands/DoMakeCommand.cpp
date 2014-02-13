#include "DoMakeCommand.h"
#include "CommandDir.h"
#include "CommandQuit.h"
#include "CommandInfo.h"
#include "CommandNotFound.h"
#include "CommandDel.h"
#include "CommandRen.h"
#include "CommandCreate.h"
#include "CommandGet.h"
#include "CommandPut.h"
#include "CommandSync.h"
#include "string.h"
#include "iostream"

DoMakeCommand::DoMakeCommand()
{
}

ICommand* DoMakeCommand::makeCommand(std::string& name) {
	if(name.compare("QUIT") == 0)
		return new CommandQuit();
	else if(name.compare("INFO") == 0)
		return new CommandInfo();
	else if(name.compare("DIR") == 0)
		return new CommandDir();
	else if(name.compare("DEL") == 0)
		return new CommandDel();
	else if(name.compare("REN") == 0)
		return new CommandRen();
	else if(name.compare("CREATE") == 0)
		return new CommandCreate();
	else if(name.compare("GET") == 0)
		return new CommandGet();
	else if(name.compare("PUT") == 0)
		return new CommandPut();
	else if(name.compare("SYNC") == 0)
		return new CommandSync();
	else
		return new CommandNotFound();
}
