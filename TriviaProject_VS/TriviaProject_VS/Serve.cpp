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


	std::string msg;


	RequestResult reqResult;

	IRequestHandler* handler = this->m_handlerFactory->createLoginRequestHandler();
	while (true) {
		try
		{
			ZeroMemory(recMsg, 2048);
			byteReceived = recv(client, recMsg, 2048, 0);

			if (checkByteReceived(byteReceived)) { // if client disconnected check.
				_clients.erase(client);

				throw std::exception("User exit");
			}


			msg = recMsg; // convert to srting.

			//data processing
			int id = recMsg[0] - 48;
			int len = std::stoi(msg.substr(1, 4));
			std::string data = msg.substr(5, len);

			std::cout << "---------------------------------" << std::endl;
			std::cout << "Message received: " << std::endl;
			std::cout << "Id = " << id << std::endl;
			std::cout << "Length = " << len << std::endl;
			std::cout << "data = " << data << std::endl;


			std::vector<unsigned char> buffer(data.begin(), data.end());

			RequestInfo msgInfo = createNewRequestInfo(id, buffer);



			if (!(this->_clients.count(client) > 0)) //  client has to login first
			{


				if (handler->isRequestRelevant(msgInfo)) { // check if relevent



					reqResult = handler->handleRequest(msgInfo);


					//succee to login
					if (reqResult.newHandler != nullptr)
					{
						this->_mtx1.lock();
						addToClients(client, reqResult.newHandler);
						handler = reqResult.newHandler;
						this->_mtx1.unlock();
					}



				}
				else {
					throw std::exception("must login First");

				}
			}
			else
			{

				switch (id)
				{
				case CLIENT_SIGNUP:
				{
					throw std::exception("First Logout then try to signup");
					break;
				}
				case CLIENT_LOGIN:
				{
					throw std::exception("First Logout then try to login");
					break;
				}
				case CLIENT_LOGOUT:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						reqResult = handler->handleRequest(msgInfo);
					}

					break;
				}
				case CLIENT_SIGNOUT:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						reqResult = handler->handleRequest(msgInfo);
					}

					break;
				}
				case CLIENT_CREATE_ROOM:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						reqResult = handler->handleRequest(msgInfo);
					}

					break;
				}
				case CLIENT_JOIN_ROOM:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						reqResult = handler->handleRequest(msgInfo);
					}

					break;
				}
				case CLIENT_GET_PLAYERS_ROOM:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						reqResult = handler->handleRequest(msgInfo);
					}

					break;
				}
				case CLIENT_GET_ROOMS:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						reqResult = handler->handleRequest(msgInfo);
					}

					break;
				}
				case CLIENT_GET_STATS_USER:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						reqResult = handler->handleRequest(msgInfo);
					}

					break;
				}
				case CLIENT_HIGH_SCORE:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						reqResult = handler->handleRequest(msgInfo);
					}

					break;
				}
				default:
				{
					throw std::exception("not an request type");
				}

				}
				handler = reqResult.newHandler;

				this->_mtx1.lock();
				this->_clients.at(client) = handler;
				this->_mtx1.unlock();

			}


			//send json to the client -> 
			std::string responseString(reqResult.buffer.begin(), reqResult.buffer.end());
			std::cout << "Response sent: " << responseString << std::endl;
			if (send(client, responseString.c_str(), responseString.size(), 0) == INVALID_SOCKET) {
				this->_clients.erase(client);
				throw ClientError();
			}

		}
		catch (const std::exception& recieveIllegal)
		{
			std::cout << "Error: " << recieveIllegal.what() << std::endl;
			//creating message to send.
			ErrorResponse error;
			error.message = recieveIllegal.what();
			std::vector<unsigned char> errorMessage = JRPS::serializeResponse(error);
			std::string responseString(errorMessage.begin(), errorMessage.end());

			//sending
			try {
				if (send(client, responseString.c_str(), responseString.size(), 0) == INVALID_SOCKET) {
					throw std::exception("Error: while sending message to client.");
				}
				std::cout << "Response sent: " << responseString;
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


	