#pragma once

#include "IRequestHandler.h"
#include "StatisticsManager.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "LoginManager.h"


#include "JsonRequestPacketDeserialize.h"
#include "JsonResponsePacketSerialize.h"
#include "Helper.h"

#include "RequestHandlerFactory.h"

class RequestHandleFactory;

class MenuRequestHanlder : public IRequestHandler
{

public:
	MenuRequestHanlder(RequestHandleFactory& handleFactory, LoggedUser loggedUser);


	virtual bool isRequestRelevant(RequestInfo request);
	virtual RequestResult handleRequest(RequestInfo value);


private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandleFactory& m_handlerFactory;
	
	
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult getPersonalStats(RequestInfo info);
	RequestResult getHighScore();
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);
	RequestResult signout();
	RequestResult logout();


};