 #include "SERVER.h"



Server::Server(IDatabase* database) : m_database(database), m_handlerFactory(m_database), Communicator(&m_handlerFactory)
{
}

void Server::run()
{
	
	std::thread admin_thread(&Server::admin_acess_function , this);
	admin_thread.detach();

	Communicator.startHandleRequests();
	
}


void Server::admin_acess_function()
{
	std::string msg;
	while (true) {
		std::cout << "Waiting for admin command: " << std::endl;
		std::cin >> msg;
		if (msg == "EXIT") {

			exit(1);
		}

	}
}