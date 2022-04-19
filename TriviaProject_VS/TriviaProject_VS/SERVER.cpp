 #include "SERVER.h"



Server::Server(IDatabase* database) : m_database(database), m_handlerFactory(m_database), Communicator(&m_handlerFactory)
{
}

void Server::run()
{
	
	std::thread admin_thread(&serveTool::admin_acess_function, &Communicator);
	admin_thread.detach();
	Communicator.startHandleRequests();
	
}

