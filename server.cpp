//=============================================================================
// A very basic tcp-server
// (c) 8-12-2010, Frans Spijkerman, Avans Hogeschool
//=============================================================================

// system modules
#include <iostream>
#include <fstream>
using namespace std;

#include <string>

// our own modules
#include "Socket.h"

// constants
static const int MAXPATH = 1; // Maximale lengte van padnaam
static const int TCP_PORT = 1080;

//=============================================================================
void handle(Socket *socket)
//=============================================================================
{
    char line[MAXPATH + 1];

	cout << "Connected!\r\n";

	// say hello to client
	socket->write("Hello\r\n");

    while(socket->readline(line, MAXPATH)) {
        cout << line;
    }

    cout << endl;

    socket->write("BYE!\r\n");

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

