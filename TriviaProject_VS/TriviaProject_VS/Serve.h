
#pragma once
#include <iostream>
#include <WinSock2.h>

#include <exception>
#include "ClientError.h"



#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <queue>
#include <vector>

#include "SignUpRequestHandler.h"



#include "LoggedUser.h"



#include "JsonRequestPacketDeserialize.h"
#include "JsonResponsePacketSerialize.h"

#include "RequestHandlerFactory.h"
#include "Helper.h"

#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);


bool checkByteReceived(int ByteReceived);
RequestInfo createNewRequestInfo(int id, std::vector<unsigned char> value);

class serveTool
{
public:
	serveTool& operator=(const serveTool& other);
	serveTool(RequestHandleFactory* handlerFactory);
	~serveTool();
	//main function 
	void bindAndListen();

	//communicate thread's function 
	void cHandler(SOCKET client);


	void startHandleRequests();
	void checkMyUpdate();

	
	void addToClients(SOCKET client, IRequestHandler* request);
	
	void addToSockToClient(SOCKET client, std::string x);
	void Disconnected(SOCKET socket, std::string userName);

private:
	
	
	
	SOCKET _socket;

	std::mutex _mtx1;

	std::map<SOCKET, IRequestHandler*> _clients;
	std::map <SOCKET, std::string> sock_to_user;
	RequestHandleFactory* m_handlerFactory;
};