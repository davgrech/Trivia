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
