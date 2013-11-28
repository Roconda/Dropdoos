#pragma once
//=============================================================================
// socket.h 
// (c) 8-12-2010, Frans Spijkerman, Avans Hogeschool
//
// Definition of classes Socket, ServerSocket and CientSocket
//
// Socket:
//	Abstraction of tcp-socket using Windows Sockets API (WSA)
//
// ServerSocket:
//  Socket to listen to clients on a tcp-port
//
// ClientSocket:
//	Socket to connect to a server on a tcp-port
//=============================================================================

#if defined(WIN32) || defined(WIN64)
	#include <winsock2.h>
#else // POSIX
	typedef int SOCKET;
#endif // _WINDOWS

#include <iostream>
using namespace std;

//=============================================================================
class Socket
//=============================================================================
{
protected:
	SOCKET sok;

public:
	Socket() : sok(0){}
	Socket(SOCKET sok) : sok(sok) {}
	~Socket() {	if (sok > 0) close(); };

	void set(SOCKET sok) { this->sok = sok; }
	void close();

	// READ NUMBER OF CHARACTERS
	size_t read(char *buf, size_t maxlen);
	size_t read(wchar_t *buf, size_t maxlen);

	// READ LINE OF CHARACTERS
	size_t readline(char *buf, size_t maxlen);
	size_t readline(wchar_t *buf, size_t maxlen);

	void write(const char *buf, size_t len);
	void write(const char *buf);
	void write(const wchar_t *buf);
	void writeline(const wchar_t *buf);
	void writeline(const char *buf);
};

//=============================================================================
class ServerSocket : public Socket
//=============================================================================
{
public:
	ServerSocket(int port);
	Socket *accept();
};

//=============================================================================
class ClientSocket : public Socket
//=============================================================================
{
public:
	ClientSocket(const char *host, int port);
};
