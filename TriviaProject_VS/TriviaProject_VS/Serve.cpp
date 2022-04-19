#include "Serve.h"
#define _CRT_SECURE_NO_WARNINGS
static const unsigned short PORT = 2022;
static const unsigned int IFACE = 0;



serveTool::serveTool(RequestHandleFactory* handlerFactory)
{

	this->m_handlerFactory = handlerFactory;
	this->_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}


serveTool::~serveTool()
{
	closesocket(this->_socket);
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


void serveTool::startHandleRequests()
{
	bindAndListen();

	while (true) {


		TRACE("waiting for client... ");
		SOCKET client = accept(this->_socket, NULL, NULL);


		TRACE("Client accepted !");






		//start communicate
		std::thread communicate(&serveTool::cHandler, this, client);
		communicate.detach();
	}
}






void serveTool::cHandler(SOCKET client)
{
	
	char recMsg[2048];
	ZeroMemory(recMsg, 2048);

	int byteReceived = recv(client, recMsg, 2048, 0);

	std::cout << "Msg received: " << recMsg << std::endl;

	if (checkByteReceived(byteReceived)) {
		_clients.erase(client);
	}

	


	
	while (true) {

		std::string return_msg = recMsg;
		int id = recMsg[0] - 48;
		int len = std::stoi(return_msg.substr(1, 4));
		std::string data = return_msg.substr(5, len);
		std::vector<unsigned char> buffer(data.begin(), data.end());
		RequestInfo msg_to_Receive = createNewRequestInfo(id, buffer);

		ZeroMemory(recMsg, 2048);
		byteReceived = recv(client, recMsg, 2048, 0);

		std::cout << "Msg received: " << recMsg << std::endl;


		if (checkByteReceived(byteReceived)) {		
			_clients.erase(client);
			break;
		}
	}
	std::cout << "Client left..." << std::endl;
	_clients.erase(client);
}


RequestInfo createNewRequestInfo(int id, std::vector<unsigned char> value)
{
	time_t now = time(nullptr);

	RequestInfo handle{

		id,
		ctime(&now),
		value
	};


	return handle;
}

bool checkByteReceived(int ByteReceived)
{
	return ByteReceived == SOCKET_ERROR;
}



RequestInfo serveTool::createNewRequestInfo(int id, std::vector<unsigned char> value)
{
	time_t now = time(nullptr);

	RequestInfo handle{
		id,
		ctime(&now),
		value
	};


	return handle;
}


void serveTool::addToClients(SOCKET client, LoginRequestHandler request) 
{
	
	this->_clients.insert(std::pair< SOCKET, IRequestHandler*>(client, &request));
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
	