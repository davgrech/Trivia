#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "GameRequestHandler.h"

#include "GameManager.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

#include <string>
class MenuRequestHanlder;

class LoginRequestHandler;

class RoomMemberRequestHandler;

class RoomAdminRequestHandler;

class GameRequestHandler;

class RequestHandleFactory
{
	public:
		
		RequestHandleFactory(IDatabase* db);
		LoginRequestHandler* createLoginRequestHandler();
		MenuRequestHanlder* createMenuRequestHandler(LoggedUser logUser);
		RoomMemberRequestHandler* createRoomMemberRequest(std::string userName, int id);
		RoomAdminRequestHandler* createRoomAdminRequest(std::string userName, Room& room);
		GameRequestHandler* createGameRequestHandler(int id, LoggedUser user);


		RoomManager& getRoomManager();
		LoginManager& getLoginManager();
		StatisticsManager& getStatisticManager();
		GameManager& getGameManager();
		void deleteUser(std::string username);
		
	private:
		IDatabase* m_database;
		LoginManager m_LoginManager;
		RoomManager m_RoomManager;
		StatisticsManager m_StatisticManager;
		GameManager m_gameManager;
};