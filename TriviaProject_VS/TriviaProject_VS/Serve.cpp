#include "Serve.h"
#define _CRT_SECURE_NO_WARNINGS
static const unsigned short PORT = 2022;
static const unsigned int IFACE = 0;


#include <mutex>

std::mutex login_manager;
std::mutex statistic_manager;
std::mutex room_manager;
std::mutex game_manager;
std::mutex user_map;
std::mutex connect_map;

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
	connect_map.lock();
	this->_clients.insert(std::pair< SOCKET, IRequestHandler*>(client, request));
	connect_map.unlock();
}

void serveTool::addToSockToClient(SOCKET client, std::string x)
{
	user_map.lock();
	this->sock_to_user.insert(std::pair< SOCKET,std::string>(client, x));
	user_map.unlock();
}

void serveTool::Disconnected(SOCKET socket, std::string userName)
{
	// if logged in
	if (this->sock_to_user.count(socket) > 0)
	{
		login_manager.lock();
		this->m_handlerFactory->deleteUser(this->sock_to_user.at(socket));
		login_manager.unlock();

		room_manager.lock();
		this->m_handlerFactory->getRoomManager().deleteUserInRoom(sock_to_user.at(socket));
		room_manager.unlock();
	}

	user_map.lock();
	sock_to_user.erase(socket);
	user_map.unlock();

	connect_map.lock();
	_clients.erase(socket);
	connect_map.unlock();
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
				Disconnected(client, sock_to_user.at(client));
				
				
				
				return;
			}


			msg = recMsg; // convert to srting.

			//data processing
			int id = (int)recMsg[0];
			int len = std::stoi(msg.substr(1, 4));
			std::string data = msg.substr(5, len);

			std::cout << "---------------------------------" << std::endl;
			std::cout << "Message received: " << std::endl;
			std::cout << "Id = " << id << std::endl;
			std::cout << "Length = " << len << std::endl;
			std::cout << "data = " << data << std::endl;


			std::vector<unsigned char> buffer(data.begin(), data.end());

			RequestInfo msgInfo = createNewRequestInfo(id, buffer);


			//if doesnt connected or doesnt logged ->true
			if (!(this->sock_to_user.count(client) > 0)) //  client has to login first
			{


				if (handler->isRequestRelevant(msgInfo)) { // check if relevent


					login_manager.lock();
					reqResult = handler->handleRequest(msgInfo);
					login_manager.unlock();

					//succee to login
					if (reqResult.newHandler != nullptr)
					{
						
						if (id == CLIENT_SIGNUP)
						{
							
							SignupRequest req = JRPD::deserializeSignupRequest(msgInfo.buffer);
							addToSockToClient(client, req.username);
						}
						else
						{
							
							LoginRequest req = JRPD::deserializeLoginRequest(msgInfo.buffer);
							addToSockToClient(client, req.username);
						}
						
						addToClients(client, reqResult.newHandler);
						handler = reqResult.newHandler;
						
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
						login_manager.lock();
						reqResult = handler->handleRequest(msgInfo);
						login_manager.unlock();
						//leave the room if he is in one  & leave logs
						
						room_manager.lock();
						this->m_handlerFactory->getRoomManager().deleteUserInRoom(sock_to_user.at(client));
						room_manager.unlock();
						
						user_map.lock();
						this->sock_to_user.erase(client);
						user_map.unlock();
						
					}

					break;
				}
				case CLIENT_SIGNOUT:
				{
					
					if (handler->isRequestRelevant(msgInfo)) {
						login_manager.lock();
						reqResult = handler->handleRequest(msgInfo);
						login_manager.unlock();
						//leave the room if he is in one  & leave logs
						room_manager.lock();
						this->m_handlerFactory->getRoomManager().deleteUserInRoom(sock_to_user.at(client));
						room_manager.unlock();

						user_map.lock();
						this->sock_to_user.erase(client);
						user_map.unlock();
					}

					break;
				}
				case CLIENT_CREATE_ROOM:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						room_manager.lock();
						reqResult = handler->handleRequest(msgInfo);
						room_manager.unlock();
					}

					break;
				}
				case CLIENT_JOIN_ROOM:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						room_manager.lock();
						reqResult = handler->handleRequest(msgInfo);
						room_manager.unlock();
					}

					break;
				}
				case CLIENT_GET_PLAYERS_ROOM:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						room_manager.lock();
						reqResult = handler->handleRequest(msgInfo);
						room_manager.unlock();
					}

					break;
				}
				case CLIENT_GET_ROOMS:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						room_manager.lock();
						reqResult = handler->handleRequest(msgInfo);
						room_manager.unlock();
					}

					break;
				}
				case CLIENT_GET_STATS_USER:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						statistic_manager.lock();
						reqResult = handler->handleRequest(msgInfo);
						statistic_manager.unlock();
					}

					break;
				}
				case CLIENT_HIGH_SCORE:
				{
					if (handler->isRequestRelevant(msgInfo)) {
						statistic_manager.lock();
						reqResult = handler->handleRequest(msgInfo);
						statistic_manager.unlock();
					}

					break;
				}
				default:
				{
					throw std::exception("not an request type");
				}

				}
				handler = reqResult.newHandler;

				connect_map.lock();
				this->_clients.at(client) = handler;
				connect_map.unlock();

			}


			//send json to the client -> 
			std::string responseString(reqResult.buffer.begin(), reqResult.buffer.end());
			std::cout << "Response sent: " << responseString << std::endl;
			if (send(client, responseString.c_str(), responseString.size(), 0) == INVALID_SOCKET) {

				Disconnected(client, sock_to_user.at(client));
				return;
				
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
					Disconnected(client, sock_to_user.at(client));
					return;
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
	return ByteReceived == 0 || ByteReceived == -1;
}


	