//=============================================================================
// A very basic tcp-server
// (c) 8-12-2010, Frans Spijkerman, Avans Hogeschool
//=============================================================================

// system modules
#include <iostream>
using namespace std;

#include <string>
#include <vector>
#include <string.h>
#include <sstream>

// our own modules
#include "Socket.h"
#include "Settings.h"
#include "commands/DoMakeCommand.h"
#include "commands/CommandNotFound.h"
#include "commands/ICommand.h"

#include <stdio.h>
#ifdef WINDOWS
	#include <windows.h>
#else
	#include <signal.h>
#endif

// constants
static const int MAXPATH = 524288; // Maximale groote op de stack
static const int TCP_PORT = 1080;


/**
 * These methods handle interrupts and other signals.
 */
void signalHelper() {
	if(Settings::getInstance().currentSocket != nullptr)
		Settings::getInstance().currentSocket->close();

	// Remove objects
	delete Settings::getInstance().currentSocket;
	delete Settings::getInstance().serverSocket;

}
#ifdef WINDOWS
// See http://msdn.microsoft.com/en-us/library/ms685049%28VS.85%29.aspx
// TODO: test on windows
bool signalHandlerWindows(DWORD fdwCtrlType) {
	signalHelper();

	return true;
}
#else
void signalHandlerPosix(int signal) {
	signalHelper();

	quick_exit(0);
}
#endif

ICommand& getCommand(char* line) {
	string str(line);
	string buffer;
	stringstream ss(str);

	vector<string> splittedItems;

	// Voeg toe aan vector.
	while (ss >> buffer)
		splittedItems.push_back(buffer);

	// Roep factory aan.
	return *DoMakeCommand::makeCommand(splittedItems.front());;
}

//=============================================================================
void handle(Socket *socket)
//=============================================================================
{
	char line[MAXPATH];
	short int state = 0;
	ICommand* command;

	while(socket->readline(line, MAXPATH) != 0) {

		// Pointer has been deleted, set state to 0
		if(command == nullptr) state = 0;

		// check if command is found
		if(state == 0) {
			state = 1;
			command = &getCommand(line);
			command->setSocket(socket);

			cout << "Command: " << line << " has been called" << endl;
		}else if(strcmp(line, "EOC") != 0){
			// Command parameters
			command->read(line);
		}else{
			// end of command reached
			try{
				// executing command
				if(!command->execute()) {
					// empty line requirement
					socket->writeline("");

					break;
				}
			}catch(...) {
				// something unexpected happened
				socket->writeline("10");
			}

			// empty line requirement
			socket->writeline("");

			// delete pointer and mark as deleted
			delete command;
			command = nullptr;
		}

	}

	cout << "End of handle\r\n";
}

//=============================================================================
// Example of a tcp-server
//=============================================================================
int main(int argc, const char * argv[])
//=============================================================================
{

	while(true) {
		// CREATE A SERVER SOCKET
		Settings::getInstance().serverSocket = new ServerSocket(TCP_PORT);
		// WAIT FOR CONNECTION FROM CLIENT; WILL CREATE NEW SOCKET
		cout << "Server listening\r\n";

		#ifdef WINDOWS
			SetConsoleCtrlHandler( (PHANDLER_ROUTINE) signalHandlerWindows, TRUE );
		#else
			signal(SIGINT, signalHandlerPosix);
		#endif

		while((Settings::getInstance().currentSocket = Settings::getInstance().serverSocket->accept()))
		{
			cout << "Client connected\r\n";

			// COMMUNICATE WITH CLIENT OVER NEW SOCKET
			handle(Settings::getInstance().currentSocket);

			cout << "Server listening again\r\n";
		}

		delete Settings::getInstance().serverSocket;
	}
	return 0;
}

