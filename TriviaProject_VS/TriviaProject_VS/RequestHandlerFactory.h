#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "Helper.h"
#include "LoginManager.h"
class LoginRequestHandler;


class RequestHandleFactory
{
	public:
		RequestHandleFactory& operator=(const RequestHandleFactory& other);
		RequestHandleFactory(IDatabase* db);
		LoginRequestHandler* createLoginRequestHandler();
		MenuRequestHanlder* createMenuRequestHandler();
		LoginManager& getLoginManager();

	private:
		IDatabase* m_database;
		LoginManager m_LoginManager;

};