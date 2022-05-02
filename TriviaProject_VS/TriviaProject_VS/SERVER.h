#pragma once
#pragma comment (lib, "ws2_32.lib")
#include <iostream>
#include "serve.h"
#include "RequestHandlerFactory.h"
#include "SqliteDatabase.h"
#include <exception>
class Server
{
public:
	Server(IDatabase* database);
	~Server();
	void admin_acess_function();
	void run();
	
private:
	RequestHandleFactory m_handlerFactory;
	serveTool Communicator;
	IDatabase* m_database;
};
