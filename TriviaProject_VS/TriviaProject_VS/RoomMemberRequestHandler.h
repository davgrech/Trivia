#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"




class RequestHandleFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
private:
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandleFactory& m_handlerFactory;

	RequestResult leaveRoom(RequestInfo value);
	RequestResult getRoomState(RequestInfo value);
public:
	RoomMemberRequestHandler(Room& room, LoggedUser user, RequestHandleFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo value);
	virtual RequestResult handleRequest(RequestInfo value);
	virtual std::string getType();
	int GetID();
	std::string getUserName();
};