#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room& room, LoggedUser user, RequestHandleFactory& hadlerFactory) : m_room(room), m_roomManager(m_handlerFactory.getRoomManager()), m_handlerFactory(hadlerFactory)
{
    this->m_user = user;
    this->m_room = room;
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo value)
{
    return value.id == CLIENT_CLOSE_ROOM || value.id == CLIENT_START_GAME || value.id == CLIENT_GET_STATE;
}



RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo value)
{
    RequestResult res;
    switch (value.id)
    {
        case CLIENT_CLOSE_ROOM:
        {
            res = closeRoom(value);
            break;
        }
        case CLIENT_START_GAME:
        {
            res = startGame(value);
            break;
        }
        case CLIENT_GET_STATE:
        {
            res = getRoomState(value);
            break;
        }

    }
    return res;
}

std::string RoomAdminRequestHandler::getType()
{
    return typeid(this).name();
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
    m_roomManager.getRoom(this->m_room.getRoomData().id).getRoomData().isActive = ROOM_ACTIVE;
   
    return RequestResult();
}
