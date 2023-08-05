class Server;
class Location;

class Config
{
	public:

	private:
		std::vector<Server> _servers;
};

class Server
{
	public:

	private:
		std::vector<int> 			_listen;
		std::vector<std::string>	_server_name;
		std::string					_root;
		std::vector<Location>		_locations;

}

class Location
{
	public:

	private:
		std::string				_url;
		bool					_dir_listing;
		std::string				_default_file;
}
