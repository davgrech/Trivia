#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room& room, LoggedUser user, RequestHandleFactory& hadlerFactory) : m_room(room), m_roomManager(m_handlerFactory.getRoomManager()), m_handlerFactory(hadlerFactory)
{
    this->m_user = user;
    this->m_room = room;
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo value)
{
    return false;
}



RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo value)
{
    return RequestResult();
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo value)
{
    return RequestResult();
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo value)
{
    return RequestResult();
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo value)
{
    return RequestResult();
}
