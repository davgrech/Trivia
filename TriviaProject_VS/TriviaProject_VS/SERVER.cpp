 #include "SERVER.h"

void Server::run()
{
	serveTool communicator;
	std::thread admin_thread(&serveTool::admin_acess_function, &communicator);
	admin_thread.detach();

	communicator.bindAndListen();


	std::thread receive_thread(&serveTool::receiveHandle, &communicator);  //&serveTool::receiveHandle

	while (true) {
		LoginRequestHandler temp;

		TRACE("waiting for client... ");
		SOCKET client = accept(communicator.getSock(), NULL, NULL);


		TRACE("Client accepted !");
		
		communicator.addToClients(client, temp);




		//start communicate
		std::thread communicate(&serveTool::cHandler, &communicator, client);
		communicate.detach();
	}
}

