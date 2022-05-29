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
    this->m_handlerFactory.getRoomManager().deleteRoom(m_room.getRoomData().id);
    CloseRoomResponse res;
    res.status = ROOM_CLOSE;

    return RequestResult{JRPS::serializeResponse(res), this->m_handlerFactory.createMenuRequestHandler(this->m_user)};
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo value)
{
    GetRoomStateResponse res;
    res.answerTimeout = this->m_room.getRoomData().timePerQuestion;

    this->m_room.getRoomData().isActive == ROOM_ACTIVE ? res.hasGameBegun = true : res.hasGameBegun = false;

    res.players = this->m_room.getAllUsers();
    res.questionCount = this->m_room.getRoomData().numOfQuestionsInGame;
    res.status = this->m_room.getRoomData().isActive;

    switch (res.status)
    {
        case ROOM_CLOSE:
        {
            return RequestResult{ JRPS::serializeResponse(res), m_handlerFactory.createMenuRequestHandler(this->m_user) };
            break;
        }
        case ROOM_OPEN:
        {
            return RequestResult{ JRPS::serializeResponse(res), this };
            break;
        }
        case ROOM_ACTIVE:
        {

            //will be changed to game handler
            return RequestResult{ JRPS::serializeResponse(res), this };
            break;
        }
        default:
        {
            throw std::exception("getRoomState - not in switch");
        }
    }
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo value)
{
    StartGameResponse res;
    res.status = ROOM_ACTIVE;
    m_roomManager.getRoom(this->m_room.getRoomData().id).getRoomData().isActive = ROOM_ACTIVE;
   
    return RequestResult{JRPS::serializeResponse(res), this};
}
