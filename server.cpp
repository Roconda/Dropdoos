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
#include "commands/commandinfo.h"
#include "commands/icommand.h"

// constants
static const int MAXPATH = 1; // Maximale lengte van padnaam
static const int TCP_PORT = 1080;

//=============================================================================
void handle(Socket *socket)
//=============================================================================
{
    char line[MAXPATH + 1];

    cout << "Connected!\r\n";

    // Local variables to initiate the actual command object
    signed int hasCommand = -1;
    string* textCommand = new string();
    ICommand* command = NULL;


    while(socket->readline(line, MAXPATH)) {
        // Filter on first space delimiter
        if(hasCommand == -1) {
            if(line[0] != ' ') textCommand += line[0];
            else{
                // Validate command and initiate it.
                hasCommand = 0; // if is validated
                command = new CommandInfo();
            }
        }else{
            // do something
            hasCommand = 1;

        }
    }

    // Initiate command if found
    if(command != NULL){
        const char* message = command->execute().c_str();
        socket->write(message);
    }else{
        socket->write("Command not found\r\n");
    }

    cout << endl;

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

