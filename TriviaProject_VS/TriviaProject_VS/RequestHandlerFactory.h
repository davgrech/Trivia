#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

#include <string>
class MenuRequestHanlder;

class LoginRequestHandler;

class RoomMemberRequestHandler;

class RoomAdminRequestHandler;

class RequestHandleFactory
{
	public:
		
		RequestHandleFactory(IDatabase* db);
		LoginRequestHandler* createLoginRequestHandler();
		MenuRequestHanlder* createMenuRequestHandler(LoggedUser logUser);
		RoomMemberRequestHandler* createRoomMemberRequest(std::string userName, int id);
		RoomAdminRequestHandler* createRoomAdminRequest(std::string userName, Room& room);



		RoomManager& getRoomManager();
		LoginManager& getLoginManager();
		StatisticsManager& getStatisticManager();
		void deleteUser(std::string username);
		
	private:
		IDatabase* m_database;
		LoginManager m_LoginManager;
		RoomManager m_RoomManager;
		StatisticsManager m_StatisticManager;
};