#pragma once
#include "LoginRequestHandler.h"
class LoginRequestHandler;


class RequestHandleFactory
{
	public:

		RequestHandleFactory(IDatabase* db);
		LoginRequestHandler* createLoginRequestHandler();
		LoginManager& getLoginManager();

	private:
		IDatabase* m_database;
		LoginManager m_LoginManager;

};