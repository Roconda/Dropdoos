//=============================================================================
// A very basic tcp-server
// (c) 8-12-2010, Frans Spijkerman, Avans Hogeschool
//=============================================================================

// system modules
#include <iostream>
#include <fstream>
using namespace std;

// our own modules
#include "Socket.h"

// constants
static const int MAXPATH = 256; // Maximale lengte van padnaam
static const int TCP_PORT = 1080;

//=============================================================================
void handle(Socket *socket)
//=============================================================================
{
	char line[MAXPATH + 1];

	cout << "Connected!\r\n";

	// say hello to client
	socket->write("Hello\r\n");

	// read first line of request
	if(socket->readline(line, MAXPATH))
	{
		// echo request to terminal
		cout << "Get request: " << line << "\r\n";
		// say bye to client
		socket->write("BYE!\r\n");
	}
	// close and delete socket (created by server's accept)
	delete socket;
}

//=============================================================================
// Example of a tcp-server
//=============================================================================
int main(int argc, const char * argv[])
//=============================================================================
{
	// CREATE A SERVER SOCKET 
	ServerSocket serverSocket(TCP_PORT);
	// WAIT FOR CONNECTION FROM CLIENT; WILL CREATE NEW SOCKET
	cout << "Server listening\r\n";
	while(Socket *socket = serverSocket.accept())
	{
		// COMMUNICATE WITH CLIENT OVER NEW SOCKET
		handle(socket);
		cout << "Server listening again\r\n";
	}
	return 0;
}

