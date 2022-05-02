 #include "SERVER.h"



Server::Server(IDatabase* database) : Communicator(&this->m_handlerFactory), m_database(database), m_handlerFactory(database)
{
	/*this->m_database = database;
	
	this->m_handlerFactory = RequestHandleFactory(database);
	this->Communicator = serveTool(&this->m_handlerFactory);*/
}
Server::~Server()
{
	delete this->m_database;
}
void Server::run()
{
	
	std::thread admin_thread(&Server::admin_acess_function , this);
	admin_thread.detach();

	//Communicator.checkMyUpdate();
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