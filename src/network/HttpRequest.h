namespace network
{
	class TcpSocket;
	class HttpRequest
	{
		Method method;
		TcpSocket * socket;
		std::vector<char> body;
	public:
		enum Method { GET, POST, HEAD }
		HttpRequest(std::string url, Method method = GET);
		void AddHeader(std::string name, std::string value);
		void AddBody(std::string name, std::string value);
		void AddBody(std::string name, char * data, int length);

		void Start();
		void End();
		bool IsComplete();
	};
}