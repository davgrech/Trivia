#include "Serve.h"
static const unsigned short PORT = 2022;
static const unsigned int IFACE = 0;


serveTool::serveTool()
{
	this->_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}
serveTool::~serveTool()
{
	closesocket(this->_socket);
}

void serveTool::serve()
{
	bindAndListen();
	std::thread receive_thread(&serveTool::receiveHandle, this);
	while (true) {
		LoginRequestHandler temp;
		TRACE("waiting for client... ");
		SOCKET client = accept(this->_socket, NULL, NULL);
		TRACE("Client accepted !");


		/*
		future features: 
			1.recv tcp syn
			2.insert data 
			3. send hello whether all alright
		*/
		
		this->_clients.insert(std::pair<SOCKET, LoginRequestHandler>(client, temp));

		
		

		//start communicate
		std::thread communicate(&serveTool::cHandler, this, client);
		communicate.detach();
	}
}

void serveTool::receiveHandle()
{
	SOCKET client = 0;
	std::string received_msg;
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
			Packet msg = this->_Hmsgs.front(); // this line takes the msg received and pop him froom the list in the global variable
			this->_Hmsgs.pop();
			lck.unlock();
			client = msg.getSocket();
			received_msg = msg.getMessage();

			std::cout << "Msg received: " << received_msg << std::endl;

			
			if (send(client, "HELLO", received_msg.size(), 0) == INVALID_SOCKET) {
				throw std::exception("Error while sending message to client");
			}

			 
			//here we need to release the socket

		}
		catch (...) {

		}
		
	}
}


void serveTool::cHandler(SOCKET client)
{
	
	char cleanMsg[256];
	ZeroMemory(cleanMsg, 256);
	int byteReceived = recv(client, cleanMsg, 256, 0);

	if (checkByteReceived(byteReceived)) {
		std::cerr << "connection err" << std::endl;
		_clients.erase(client);
	}

	//if not exit and receive msg len > 0 keep going
	while (std::strcmp(cleanMsg, "EXIT") && byteReceived != 0) {


		ZeroMemory(cleanMsg, 256);
		Packet myPacket(client, cleanMsg);
		addReceivedMessage(myPacket);
		byteReceived = recv(client, cleanMsg, strlen(cleanMsg), 0);

		if (checkByteReceived(byteReceived)) {
			_clients.erase(client);
		}
		
	}
	
	
	
}

int checkByteReceived(int ByteReceived)
{
	if (ByteReceived == SOCKET_ERROR) {
		std::cerr << "Error in recv(). quitting" << std::endl;
		return 1;
	}
	else if (ByteReceived == 0) {
		std::cout << "client disconnected" << std::endl;
		return 1;
	}
	else
	{
		return 0;
	}
	
}
void serveTool::addReceivedMessage(Packet x)
{
	std::unique_lock<std::mutex> lck(_mtx1);
	this->_Hmsgs.push(x);
	lck.unlock();
	this->_cv.notify_all();
}


void serveTool::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	if (::bind(this->_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (::listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");
}
