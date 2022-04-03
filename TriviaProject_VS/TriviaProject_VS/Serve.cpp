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



void serveTool::receiveHandle()
{
	SOCKET client = 0;
	std::string received_msg;
	while (true) {
		try {
			std::unique_lock<std::mutex> lck(this->_mtx1);

			//We about to change the Hmsg format to json.


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

			
			std::string send_msg;
			if (received_msg == "EXIT") {
				send_msg = "EXIT";
			}
			else {
				send_msg = "Hello";
			}


			if (send(client, send_msg.c_str(), send_msg.size(), 0) == INVALID_SOCKET) {
			
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
	
	char recMsg[256];
	ZeroMemory(recMsg, 256);
	int byteReceived = recv(client, recMsg, 256, 0);

	std::cout << "Msg received: " << recMsg << std::endl;

	if (checkByteReceived(byteReceived)) {
		_clients.erase(client);
	}

	


	//&& exit_thread_flag
	// 
	//if not exit and receive msg len > 0 keep going
	while (std::strcmp(recMsg, "EXIT")) {


		
		Packet myPacket(client, recMsg);
		addReceivedMessage(myPacket);

		ZeroMemory(recMsg, 256);
		byteReceived = recv(client, recMsg, 256, 0);

		std::cout << "Msg received: " << recMsg << std::endl;


		if (checkByteReceived(byteReceived)) {		
			_clients.erase(client);
			break;
		}
	}
	std::cout << "Client left..." << std::endl;
	_clients.erase(client);

	//send him exit msg
	Packet myPacket(client, recMsg);
	addReceivedMessage(myPacket);
	
	
	
	
}

int checkByteReceived(int ByteReceived)
{
	if (ByteReceived == SOCKET_ERROR) {
		std::cerr << "Error in recv(). quitting" << std::endl;
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



void serveTool::addToClients(SOCKET client, LoginRequestHandler request) 
{
	
	this->_clients.insert(std::pair< SOCKET, IRequestHandler*>(client, &request));
}
SOCKET serveTool::getSock()
{
	return this->_socket;
}

void serveTool::admin_acess_function()
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
	