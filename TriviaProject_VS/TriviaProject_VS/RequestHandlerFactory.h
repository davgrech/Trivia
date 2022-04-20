#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "Helper.h"

class LoginRequestHandler;


class RequestHandleFactory
{
	public:

		RequestHandleFactory(IDatabase* db);
		LoginRequestHandler* createLoginRequestHandler();
		MenuRequestHanlder* createMenuRequestHandler();
		LoginManager& getLoginManager();

	private:
		IDatabase* m_database;
		LoginManager m_LoginManager;

};