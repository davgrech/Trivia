#include "Serve.h"
#define _CRT_SECURE_NO_WARNINGS
static const unsigned short PORT = 2022;
static const unsigned int IFACE = 0;



serveTool& serveTool::operator=(const serveTool& other)
{
	this->m_handlerFactory = other.m_handlerFactory;
	this->_socket = other._socket;
	
	return *this;
}

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



void serveTool::addToClients(SOCKET client, IRequestHandler* request)
{

	this->_clients.insert(std::pair< SOCKET, IRequestHandler*>(client, request));
}



void serveTool::cHandler(SOCKET client)
{
	int byteReceived = 0;

	char recMsg[2048];
	ZeroMemory(recMsg, 2048);

	std::string msg; 

	RequestResult reqResult;

	try
	{
		
		while (true) {

			byteReceived = recv(client, recMsg, 2048, 0);

			if (checkByteReceived(byteReceived)) { // ? 
				_clients.erase(client);
				throw ClientError();
			}

			std::cout << "Msg received: " << recMsg << std::endl;
			msg = recMsg; // convert to srting.

			//data processing
			int id = recMsg[0] - 48;
			int len = std::stoi(msg.substr(1, 4));
			std::string data = msg.substr(5, len);

			std::vector<unsigned char> buffer(data.begin(), data.end());
			RequestInfo msgInfo = createNewRequestInfo(id, buffer);

			if (!(this->_clients.count(client) > 0)) //  if not found in client map
			{
				LoginRequestHandler* LoginHandler = this->m_handlerFactory->createLoginRequestHandler();
				bool isRelevent = LoginHandler->isRequestRelevant(msgInfo); 
				if (isRelevent) { // check if relevent

					
						
					reqResult =  LoginHandler->handleRequest(msgInfo);


					//succee to login
					if (reqResult.newHandler != nullptr)
					{
						this->_mtx1.lock();
						addToClients(client, reqResult.newHandler);
						this->_mtx1.unlock();
					}
					
					
					
				}
				else {
					throw std::exception("Client must login first"); 

				}
			}
			else
			{
				//other codes
			}

			//send json to the client -> 
			std::string responseString(reqResult.buffer.begin(), reqResult.buffer.end());
			std::cout << "Response sent: " << responseString << std::endl;
			if (send(client, responseString.c_str(), responseString.size(), 0) == INVALID_SOCKET) {
				this->_clients.erase(client);
				throw ClientError();
			}
			
		}
		
	}
	catch (const std::exception& recieveIllegal)
	{
		
			//creating message to send.
			ErrorResponse error;
			error.message = recieveIllegal.what();
			std::vector<unsigned char> errorMessage = JRPS::serializeResponse(error);
			std::string responseString(errorMessage.begin(), errorMessage.end());

			//sending
			try {
				if (send(client, responseString.c_str(), responseString.size(), 0) == INVALID_SOCKET) {
					throw std::exception("error while sending message to client.");
				}
			}
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl;
			}
			



		
		
		
	}
	catch (ClientError& clientDisconnected)
	{
		std::cout << clientDisconnected.what() << std::endl;
	}
	
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


	