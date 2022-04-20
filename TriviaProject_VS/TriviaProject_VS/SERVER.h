#pragma once
#include <iostream>
#include "serve.h"

#include "SqliteDatabase.h"
class Server
{
public:
	Server(IDatabase* database);
	void admin_acess_function();
	void run();
private:
	RequestHandleFactory m_handlerFactory;
	serveTool Communicator;
	IDatabase* m_database;
};
