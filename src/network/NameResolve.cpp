#ifdef WIN
#define _WIN32_WINNT 0x0501
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

#include <cstdio>
#include <cstring>
#include <algorithm>

#include "NameResolve.h"

using namespace network;

NameResolve::iterator::iterator(addrinfo * addr) :
	ptr(addr)
{

}

NameResolve::iterator::iterator(const iterator& that) :
	ptr(that.ptr)
{

}

NameResolve::iterator & NameResolve::iterator::operator++()
{
	if(ptr)
	{
		ptr = ptr->ai_next;
	}
	return *this;
}

NameResolve::iterator NameResolve::iterator::operator++(int)
{
	iterator tmp(*this);
	operator++();
	return tmp;
}

sockaddr * NameResolve::iterator::operator*()
{
	if(ptr)
		return ptr->ai_addr;
	return NULL;
}

NameResolve::NameResolve(std::string hostname, unsigned short port)
{
	char portString[6];
	std::sprintf(portString, "%u", port);

	addrinfo info;
	std::memset(&info, 0, sizeof(addrinfo));
	info.ai_family = AF_INET;
	getaddrinfo(hostname.c_str(), portString, &info, &list);
}

NameResolve::~NameResolve()
{
	if(list)
	{
		freeaddrinfo(list);
		list = NULL;
	}
}

NameResolve::iterator NameResolve::begin()
{
	return iterator(list);
}