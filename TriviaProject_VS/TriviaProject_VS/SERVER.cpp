 #include "SERVER.h"



Server::Server(IDatabase* database) : m_database(database), m_handlerFactory(m_database), Communicator(&m_handlerFactory)
{
}

void Server::run()
{
	
	std::thread admin_thread(&serveTool::admin_acess_function, &Communicator);
	admin_thread.detach();

	Communicator.bindAndListen();
	

	std::thread receive_thread(&serveTool::receiveHandle, &Communicator);  //&serveTool::receiveHandle

	while (true) {
		

		TRACE("waiting for client... ");
		SOCKET client = accept(Communicator.getSock(), NULL, NULL);


		TRACE("Client accepted !");
		
		




		//start communicate
		std::thread communicate(&serveTool::cHandler, &Communicator, client);
		communicate.detach();
	}
}

