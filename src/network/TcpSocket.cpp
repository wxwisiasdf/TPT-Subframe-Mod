#ifdef WIN
#define _WIN32_WINNT 0x0501
//#include <iphlpapi.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#endif

#include "NameResolve.h"
#include "TcpSocket.h"

using namespace network;

#ifndef WIN
#define SOCKET_ERROR -1
#endif

#ifdef WIN
static bool sockReady = false;
#endif

TcpSocket::TcpSocket():
	blocking(false),
	connected(false),
	sock(SOCKET_ERROR)
{
	if(!sockReady)
	{
#ifdef WIN
		WSADATA wsadata;
		if (!WSAStartup(MAKEWORD(2,2), &wsadata))
			sockReady = true;
#else
		signal(SIGPIPE, SIG_IGN);
		sockReady = true;
#endif
	}
}
TcpSocket::~TcpSocket()
{
	Close();
}

bool TcpSocket::GetBlocking()
{
	return blocking;
}
void TcpSocket::SetBlocking(bool block)
{
	blocking = block;
}

bool TcpSocket::Connected()
{
	return connected;
}
bool TcpSocket::Ready()
{
	if(sock == SOCKET_ERROR)
		return false;
	if(!connected)
	{
		if (!connect(sock, (struct sockaddr *)&addr, sizeof(addr)))
			return true;
#if WIN
		else if(WSAGetLastError() == WSAEISCONN)
			return true;
		else if(WSAGetLastError() != WSAEINPROGRESS && WSAGetLastError() != WSAEALREADY && WSAGetLastError() != WSAEWOULDBLOCK && WSAGetLastError() != WSAEINVAL)
			return false; 
#else
#if defined(MACOSX) || defined(BSD)
		else if(errno == EISCONN)
			return true;
#endif
		else if(errno != EINPROGRESS && errno != EALREADY)
			return false;
#endif
	}
	return true;
}

bool TcpSocket::Connect(std::string host, unsigned short port)
{
	NameResolve resolve(host, port);
	NameResolve::iterator iter = resolve.begin();
	while(*iter)
	{
		Connect(*iter);
		iter++;
	}
}

bool TcpSocket::Connect(sockaddr * address)
{

#ifdef WIN
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == SOCKET_ERROR)
		return false;

	//Set blocking state
	unsigned long nonBlocking = blocking ? 0 : 1;
	if (ioctlsocket(sock, FIONBIO, &nonBlocking) == SOCKET_ERROR)
		return false;

	//Connect!
	if (!connect(sock, (sockaddr*)&addr, sizeof(addr)))
		return true;
	else if(WSAGetLastError() == WSAEISCONN)
		return true;
	else if(WSAGetLastError() != WSAEINPROGRESS && WSAGetLastError() != WSAEALREADY && WSAGetLastError() != WSAEWOULDBLOCK && WSAGetLastError() != WSAEINVAL)
		return false; 
#else
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		return false;

	//Set blocking state
	int sockControl = fcntl(sock, F_GETFL);
	if (sockControl < 0)
		return false;
	if (fcntl(sock, F_SETFL, sockControl | O_NONBLOCK) < 0)
		return false;

	//Connect!
	if (!connect(sock, (sockaddr*)&addr, sizeof(addr)))
		return true;
#if defined(MACOSX) || defined(BSD)
	else if(errno == EISCONN)
		return true;
#endif
	else if(errno != EINPROGRESS && errno != EALREADY)
		return false;
#endif
	return true;
}
void TcpSocket::Close()
{
	if(Connected())
	{
#ifdef WIN
		closesocket(sock);
#else
		close(sock);
#endif
	}
}

int TcpSocket::Send(const char* buffer, int length)
{
	int retVal = -1;
	if(connected)
	{
		retVal = send(sock, buffer, length, 0);
		if(retVal == SOCKET_ERROR)
			return -1;
		return retVal;
	}
	return -1;
}
int TcpSocket::Recieve(char* buffer, int length)
{
	int retVal = -1;
	if(connected)
	{
		retVal = recv(sock, buffer, length, 0);
		if(retVal == SOCKET_ERROR)
			return -1;
		return retVal;
	}
	return -1;
}