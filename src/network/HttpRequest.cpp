#include "TcpSocket.h"
#include "Format.h"

using namespace network;

HttpRequest(std::string url, Method method)
{
	this->method = method;
	socket = new TcpSocket();
}

HttpRequest & AddHeader(std::string name, std::string value)
{
	return *this;
}

HttpRequest & AddBody(std::string name, std::string value)
{
	return AddBody(name, value.data(), value.size());
}

HttpRequest & AddBody(std::string name, char * data, int length)
{
	if(method == POST) {

	}
	return *this;
}

void Start()
{
	if(method == POST)
	{
		AddHeader("Content-Length", format::NumberToString(body.size()));
	}
}

void End()
{

}

bool IsComplete()
{

}
