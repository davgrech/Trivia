#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, LoggedUser user, RequestHandleFactory& handlerFactory) : m_room(room), m_roomManager(handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{
    this->m_user = user;
    this->m_room = room;
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo value)
{
    return false;
}


RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo value)
{
    return RequestResult();
}

std::string RoomMemberRequestHandler::getType()
{
    return std::string();
}

int RoomMemberRequestHandler::GetID()
{
    return 0;
}

std::string RoomMemberRequestHandler::getUserName()
{
    return std::string();
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo value)
{
    return RequestResult();
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo value)
{
    return RequestResult();
}
