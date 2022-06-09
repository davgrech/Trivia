#include "GameRequestHandler.h"

bool GameRequestHandler::isRequestRelevant(RequestInfo request)
{
    return false;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo value)
{
    return RequestResult();
}

std::string GameRequestHandler::getType()
{
    return std::string();
}

GameRequestHandler::GameRequestHandler(RequestHandleFactory& _handlerFactory, int id, LoggedUser user) : m_user(user), m_handlerFactory(_handlerFactory)
, m_game(m_handlerFactory.getGameManager().getGame(id)), m_gameManager(_handlerFactory.getGameManager())
{
   
}

RequestResult GameRequestHandler::getQuestions(RequestInfo myInfo)
{
    return RequestResult();
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo myInfo)
{
    return RequestResult();
}

RequestResult GameRequestHandler::getGameResults(RequestInfo myInfo)
{
    return RequestResult();
}

RequestResult GameRequestHandler::leaveGame(RequestInfo myInfo)
{
    return RequestResult();
}
