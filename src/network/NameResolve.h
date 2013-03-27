#pragma once

#include <string>
#include <iterator>


class addrinfo;
class sockaddr;
namespace network
{
	class NameResolve
	{
	private:
		addrinfo * list;
	public:
		class iterator : public std::iterator<std::output_iterator_tag, sockaddr>
		{
		private:
			addrinfo * ptr;
		public:
			iterator(addrinfo * addr);
			iterator(const iterator& that);
			iterator & operator++();
			iterator operator++(int);
			sockaddr * operator*();
		};
		NameResolve(std::string hostname, unsigned short port);
		~NameResolve();
		iterator begin();
	};
}