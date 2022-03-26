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
		LoginRequestHandler temp;
		SOCKET client = accept(this->_socket, NULL, NULL);
		TRACE("Client accepted !");


		/*
		future features: 
			1.recv tcp syn
			2.insert data 
			3. send hello whether all alright
		*/
		
		this->_clients.insert(std::pair<LoginRequestHandler, SOCKET>(temp, client));

		
		

		//start communicate
		std::thread communicate(&serveTool::cHandler, this, client);
		communicate.detach();
	}
}

void serveTool::receiveHandle()
{
	SOCKET client = 0;
	while (true) {
		try {
			std::unique_lock<std::mutex> lck(this->_mtx1);
			if (this->_Hmsgs.empty()) {
				this->_cv.wait(lck);
			}
			if (this->_Hmsgs.empty()) {
				continue;
			}
			//change
			std::string msg = this->_Hmsgs.front(); // this line takes the msg received and pop him froom the list in the global variable
			this->_Hmsgs.pop();
			lck.unlock();
			 
			//here we need to release the socket

		}
		catch (...) {

		}
		
	}
}
void serveTool::cHandler(SOCKET client)
{
	char recMsg[256];
	recv(client, recMsg, strlen(recMsg), 0);
	
	//if not exit and receive msg len > 0 keep going
	while (std::strcmp(recMsg, "EXIT") || std::strlen(recMsg) == 0) {


		//change the Hmsg
		addReceivedMessage(recMsg);
		recv(client, recMsg, strlen(recMsg), 0);
		
	}
	std::cout << "Client entered exit so the program shutdown" << std::endl;
	
	
}
void serveTool::addReceivedMessage()
{
	std::unique_lock<std::mutex> lck(_mtx1);
	this->_Hmsgs.push(recv);
	//this->_clients.insert(std::pair<LoginRequestHandler, SOCKET>(client));
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
