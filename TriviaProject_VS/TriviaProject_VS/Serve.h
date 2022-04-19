
#pragma once
#include <iostream>
#include <WinSock2.h>

#include <exception>
#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <queue>


#include "SignUpRequestHandler.h"

#include <atomic>





#include "JsonRequestPacketDeserialize.h"
#include "JsonResponsePacketSerialize.h"

#include "RequestHandlerFactory.h"


#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);


bool checkByteReceived(int ByteReceived);


class serveTool
{
public:
	
	serveTool(RequestHandleFactory* handlerFactory);
	~serveTool();
	//main function 
	void bindAndListen();

	//communicate thread's function 
	void cHandler(SOCKET client);


	void startHandleRequests();
	RequestInfo createNewRequestInfo(int id, std::vector<unsigned char> value);

	SOCKET getSock();
	void addToClients(SOCKET client, LoginRequestHandler request);
	void admin_acess_function();
	

private:
	
	
	
	SOCKET _socket;

	std::mutex _mtx1;

	std::map<SOCKET, IRequestHandler*> _clients;
	
	RequestHandleFactory* m_handlerFactory;
};