#include "MenuRequestHandler.h"

MenuRequestHanlder::MenuRequestHanlder(RequestHandleFactory& handleFactory, LoggedUser loggedUser) : m_handlerFactory(handleFactory), m_user(loggedUser), m_roomManager(handleFactory.getRoomManager()), m_statisticsManager(handleFactory.getStatisticManager())
{

    
}

bool MenuRequestHanlder::isRequestRelevant(RequestInfo request)
{
    return request.id == CLIENT_CREATE_ROOM || 
           request.id == CLIENT_JOIN_ROOM   ||
           request.id == CLIENT_GET_STATS_USER ||
           request.id == CLIENT_GET_PLAYERS_ROOM ||
           request.id == CLIENT_GET_ROOMS ||
           request.id == CLIENT_SIGNOUT ||
           request.id == CLIENT_LOGOUT ||
           request.id == CLIENT_HIGH_SCORE;
}

RequestResult MenuRequestHanlder::handleRequest(RequestInfo value)
{
    
    return RequestResult();
}

RequestResult MenuRequestHanlder::signout(RequestInfo info)
{
   
    return RequestResult();
}

RequestResult MenuRequestHanlder::getRooms(RequestInfo info)
{
    return RequestResult();
}

RequestResult MenuRequestHanlder::getPlayersInRoom(RequestInfo info)
{
    return RequestResult();
}

RequestResult MenuRequestHanlder::getPersonalStats(RequestInfo info)
{
    
    return RequestResult();
}

RequestResult MenuRequestHanlder::getHighScore(RequestInfo info)
{
    return RequestResult();
}

RequestResult MenuRequestHanlder::joinRoom(RequestInfo info)
{
    return RequestResult();
}

RequestResult MenuRequestHanlder::createRoom(RequestInfo info)
{
    return RequestResult();
}
