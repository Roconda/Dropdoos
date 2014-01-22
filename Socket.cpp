//=============================================================================
// socket.cpp
// (c) 8-12-2010, Frans Spijkerman, Avans Hogeschool
// enhanced for cross-platform use by Bob Polis (c) 2013
//
// Implementation of classes Socket, ServerSocket and CientSocket
//=============================================================================


#include "Socket.h"

#if defined(WIN32) || defined(WIN64)

	#pragma comment(lib, "wsock32.lib")  // Tell linker to use this library

	//=============================================================================
	class WSA
	//=============================================================================
	// ONLY NEEDED IN MS-WINDOWS
	//
	// An instance of this class is created globally.
	// So constructor is automatically called before main()
	// and destructor is automatically called after main().
	// Result: Windows Socket API is active when needed.
	//=============================================================================
	{
	private:
		WSADATA data;
	public:
		WSA()
		{
			WORD version = MAKEWORD(1,1);
			WSAStartup(version, &data);
		}
		~WSA()
		{
			WSACleanup();
		}
	} wsa; // instance

#else // not Windows (POSIX system, like Linux or Mac OS X)

	#include <sys/socket.h>
	#include <sys/ioctl.h>
	#include <net/route.h>
	#include <net/if.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <sys/types.h>
	#include <netdb.h>
	#include <ifaddrs.h>
	#include <unistd.h>
	#include <cstring>
	#include <stdexcept>

#endif // _WINDOWS

//=============================================================================
size_t Socket::read(char *buf, size_t maxlen)
//=============================================================================
// read binary chunk
//=============================================================================
{
	size_t len = 0;
	// might come in parts
	while (size_t n = ::recv(sok, buf + len, int(maxlen - len), 0))
	{
		if (n == 0) break;
		len += n;
		if (len >= maxlen) break;
	}
	return len;
}

//=============================================================================
size_t Socket::read(wchar_t *buf, size_t maxlen)
//=============================================================================
// read wide characters (e.g. UTF-16)
//=============================================================================
{
	return read(reinterpret_cast<char*>(buf), maxlen);
}

//=============================================================================
size_t Socket::readline(char *buf, size_t maxlen)
//=============================================================================
// read a line: ignore '\r', stop at '\n'
//=============================================================================
{
	char c;
	size_t len = 0;
	while (size_t n = ::recv(sok, &c, 1, 0))
	{
		if (n == 0) break;
		if (c == '\n') break;
		else buf[len++] = c;
		if (len >= maxlen) break;
	}
	buf[len] = 0;
	return len;
}

//=============================================================================
size_t Socket::readline(wchar_t *buf, size_t maxlen)
//=============================================================================
// read a line: ignore '\r', stop at '\n'
//=============================================================================
{
	wchar_t c;
	size_t len = 0;
	while (size_t n = ::recv(sok, (char*)&c, 2, 0))
	{
		if (n == 0) break;
		if (c == '\n') break;
		else buf[len++] = c;
		if (len >= maxlen) break;
	}
	buf[len] = 0;
	return len;
}

//=============================================================================
void Socket::write(const char *buf, size_t len)
//=============================================================================
// write a buffer
//=============================================================================
{
	::send(sok, buf, (int)len, 0);
}

//=============================================================================
void Socket::write(const char *buf)
//=============================================================================
// write a zero delimited string 
//=============================================================================
{
	::send(sok, buf, (int)strlen(buf), 0);
}

//=============================================================================
void Socket::write(const wchar_t *buf)
//=============================================================================
// write a zero delimited string 
//=============================================================================
{
	::send(sok, (const char*)buf, (int)(sizeof(wchar_t)*wcslen(buf)), 0);
}

//=============================================================================
void Socket::writeline(const char *buf)
//=============================================================================
// write a zero delimited string 
//=============================================================================
{
	::send(sok, (const char*)buf, (int)(sizeof(char)*strlen(buf)), 0);
	::send(sok, (const char*)"\r\n", (int)(sizeof(char)*2), 0);
}

//=============================================================================
void Socket::writeline(const wchar_t *buf)
//=============================================================================
// write a zero delimited string 
//=============================================================================
{
	::send(sok, (const char*)buf, (int)(sizeof(wchar_t)*wcslen(buf)), 0);
	::send(sok, (const char*)L"\r\n", (int)(sizeof(wchar_t)*2), 0);
}

//=============================================================================
void Socket::close()
//=============================================================================
// close socket
//=============================================================================
{
#if defined(WIN32) || defined(WIN64)
	::closesocket(sok);
#else
	::close(sok);
#endif
	sok = 0;
}

//=============================================================================
ServerSocket::ServerSocket(int port)
//=============================================================================
{
	// Create a socket
	sok = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sok == -1) throw runtime_error("error creating socket");

	// Use SOCKADDR_IN to fill in address information
	struct sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY; 
	saServer.sin_port = htons(port); // Convert int to a value for the port

	// Bind the socket to our local server address
	int e = ::bind(sok, (struct sockaddr*)&saServer, sizeof(struct sockaddr));
	if (e == -1) throw runtime_error("error binding socket");

	// Make the socket listen
	e = ::listen(sok, 100);  // the number of clients that can be queued
	if (e == -1) throw runtime_error("error listening");
}

//=============================================================================
Socket *ServerSocket::accept()
//=============================================================================
// Wait for a client and return the connection socket
//=============================================================================
{
	int t = ::accept(sok, 0, 0);
	if (t == -1) throw runtime_error("error in accept");
	return new Socket(t);
}

//=============================================================================
ClientSocket::ClientSocket(const char *host, int port)
//=============================================================================
{
	// Create a socket
	sok = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sok == -1)
		throw runtime_error("error creating socket");

	struct sockaddr_in dest; 
	::memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;

	hostent *hp;
	hp = ::gethostbyname(host);
	::memcpy(&dest.sin_addr, hp->h_addr, hp->h_length);

	if (dest.sin_addr.s_addr == -1)
		throw runtime_error("cannot find address");

	dest.sin_port = htons(port);
	int result = ::connect(sok, (sockaddr *)&dest, sizeof(sockaddr));
	if (result == -1)
		throw runtime_error("error connecting");
}

