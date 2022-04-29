#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"


class MenuRequestHanlder;

class LoginRequestHandler;

class RequestHandleFactory
{
	public:
		RequestHandleFactory& operator=(const RequestHandleFactory& other);
		RequestHandleFactory(IDatabase* db);
		LoginRequestHandler* createLoginRequestHandler();
		MenuRequestHanlder* createMenuRequestHandler(LoggedUser logUser);
		RoomManager& getRoomManager();
		LoginManager& getLoginManager();

	private:
		IDatabase* m_database;
		LoginManager m_LoginManager;
		RoomManager m_RoomManager;
};