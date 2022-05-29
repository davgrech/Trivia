#pragma once

#include <iostream>
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"




class RequestHandleFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
private:
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandleFactory& m_handlerFactory;
public:
	RoomAdminRequestHandler(Room& room, LoggedUser user, RequestHandleFactory& hadlerFactory);
	virtual bool isRequestRelevant(RequestInfo value);
	virtual RequestResult handleRequest(RequestInfo value);
	RequestResult closeRoom(RequestInfo value);
	RequestResult getRoomState(RequestInfo value);
	RequestResult startGame(RequestInfo value);
};