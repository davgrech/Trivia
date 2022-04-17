#pragma once
#include <iostream>
#include "serve.h"

#include "SqliteDatabase.h"
class Server
{
public:
	Server();
	
	void run();
private:
	serveTool Communicator;
	IDatabase* m_database;
};
