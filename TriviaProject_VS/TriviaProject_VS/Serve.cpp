#include "Serve.h"

serveTool::serveTool(int port, int Iface)
{
	this->_Iface = Iface;
	this->_port = port;
	
}

void serveTool::serve()
{
	bindAndListen();
	std::thread receive_thread(&serveTool::receiveHandle, this);
	while (true) {
		SOCKET client = accept(this->_socket, NULL, NULL);
		TRACE("Client accepted !");
		std::thread communicate(&serveTool::cHandler, this, client);
		communicate.detach();
	}
}

void serveTool::receiveHandle()
{
}
void serveTool::cHandler(SOCKET client)
{
	char recMsg[256];
	recv(client, recMsg, strlen(recMsg), 0);
	LoginRequestHandler loginHandle;
	while (std::strcmp(recMsg, "EXIT") == 1 || std::strlen(recMsg) == 0) {
		addReceivedMessage(client, loginHandle);
		recv(client, recMsg, strlen(recMsg), 0);
		//manipulate msg then create LoginRequest in the future but for now keep it simple
	}
	std::cout << "Client entered exit so the program shutdown" << std::endl;
	
	
}
void serveTool::addReceivedMessage(SOCKET client, LoginRequestHandler loginHandle)
{
	std::unique_lock<std::mutex> lck(_mtx1);
	this->_clients.insert(std::pair<LoginRequestHandler, SOCKET>(loginHandle, client));
	lck.unlock();
	this->_cv.notify_all();
}
void serveTool::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(this->_port);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = this->_Iface;
	if (::bind(this->_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (::listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");
}
