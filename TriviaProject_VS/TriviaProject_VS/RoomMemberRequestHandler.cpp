#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, LoggedUser user, RequestHandleFactory& handlerFactory) : m_room(room), m_roomManager(handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{
    this->m_user = user;
    this->m_room = room;
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo value)
{
    return CLIENT_LEAVE_ROOM || CLIENT_GET_STATE;
}


RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo value)
{
    RequestResult result;
    switch (value.id)
    {
        case CLIENT_LEAVE_ROOM:
        {
            result = this->leaveRoom(value);
            break;
        }
        case CLIENT_GET_STATE:
        {
            result = this->getRoomState(value);
            break;
        }
    }
    return result;
}


int RoomMemberRequestHandler::GetID()
{
    return this->m_room.getRoomData().id;
}

std::string RoomMemberRequestHandler::getUserName()
{
    return this->m_user.getUsername();
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo value)
{
    bool isLeft = m_room.removeUser(m_user);
    LeaveRoomResponse res;
    isLeft ? res.status = 1 : res.status = 0;
    return RequestResult{ JRPS::serializeResponse(res ), m_handlerFactory.createMenuRequestHandler(m_user)};
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo value)
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
            return RequestResult{JRPS::serializeResponse(res), this };
            break;
        }
        default:
        {
            throw std::exception("getRoomState - not in switch");
        }
    }
}