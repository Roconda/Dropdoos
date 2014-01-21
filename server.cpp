//=============================================================================
// A very basic tcp-server
// (c) 8-12-2010, Frans Spijkerman, Avans Hogeschool
//=============================================================================

// system modules
#include <iostream>
#include <fstream>
#include <memory>
using namespace std;

#include <string>
#include <vector>
#include <string.h>
#include <sstream>

// our own modules
#include "Socket.h"
#include "commands/domakecommand.h"
#include "commands/commandnotfound.h"
#include "commands/icommand.h"

// constants
static const int MAXPATH = 1024; // Maximale lengte van padnaam
static const int TCP_PORT = 1080;

ICommand& getCommand(char* line) {
	string str(line);
	string buffer;
	stringstream ss(str);

	vector<string> splittedItems;

	// Voeg toe aan vector.
	while (ss >> buffer)
		splittedItems.push_back(buffer);

	// We willen alleen elementen met waarde hebben.
	//splittedItems.shrink_to_fit();

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
		if(command == NULL) state = 0;

		// check if command is found
		if(state == 0) {
			state = 1;
			command = &getCommand(line);
			command->setSocket(socket);
		}else if(strcmp(line, "EOC") != 0){
			// read
			cout << "State read\r\n";

		}else{
			// end of command reached
			if(!command->execute()) break;

			// delete pointer and mark as deleted
			delete command;
			command = NULL;
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
		ServerSocket* serverSocket = new ServerSocket(TCP_PORT);
		// WAIT FOR CONNECTION FROM CLIENT; WILL CREATE NEW SOCKET
		cout << "Server listening\r\n";

		while(Socket *socket = serverSocket->accept())
		{
			cout << "Client connected\r\n";

			// COMMUNICATE WITH CLIENT OVER NEW SOCKET
			handle(socket);

			cout << "Server listening again\r\n";

		}

		delete serverSocket;
	}
	return 0;
}

