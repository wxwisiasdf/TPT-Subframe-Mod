namespace network
{
	class HttpRequest
	{
		HttpRequest(std::string);
		void AddHeader(std::string name, std::string value);

		void Start();
		void End();
		bool GetComplete();
	};
}