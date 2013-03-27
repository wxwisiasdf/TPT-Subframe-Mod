#pragma once

#include <string>

namespace network
{
	class TcpSocket
	{
		int sock;
		bool blocking;
		bool connected;
		void * addr;
	public:
		TcpSocket();
		~TcpSocket();

		bool GetBlocking();
		void SetBlocking(bool block);

		bool Connected();
		bool Ready();
		bool Connect(std::string host, unsigned short port);
		bool Connect(sockaddr * address);
		void Close();

		int Send(const char* buffer, int length);
		int Recieve(char* buffer, int length);
	};
}