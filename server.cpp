//=============================================================================
// A very basic tcp-server
// (c) 8-12-2010, Frans Spijkerman, Avans Hogeschool
//=============================================================================

// system modules
#include <iostream>
#include <fstream>
using namespace std;

#include <string>
#include <vector>
#include <string.h>

// our own modules
#include "Socket.h"
#include "commands/domakecommand.h"
#include "commands/commandnotfound.h"
#include "commands/icommand.h"

// constants
static const int MAXPATH = 1024; // Maximale lengte van padnaam
static const int TCP_PORT = 10800;

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    std::stringstream ss(s);
    string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

ICommand& getCommand(char* line) {
    string str(line);
    string buffer;
    stringstream ss(str);

    vector<string> splittedItems;

    // Voeg toe aan vector.
    while (ss >> buffer)
        splittedItems.push_back(buffer);

    // We willen alleen elementen met waarde hebben.
    splittedItems.shrink_to_fit();

    // Roep factory aan.
    return *DoMakeCommand::makeCommand(splittedItems.front());;
}

//=============================================================================
void handle(Socket *socket)
//=============================================================================
{
    char line[MAXPATH];

    while(socket->readline(line, MAXPATH)) {
        ICommand& command = getCommand(line);

        cout << "C: " << command.execute().c_str();

        socket->write(command.execute().c_str());
    }

    cout << endl;

    handle(socket);
    // close and delete socket (created by server's accept)
    //delete socket;
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

