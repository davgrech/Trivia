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
