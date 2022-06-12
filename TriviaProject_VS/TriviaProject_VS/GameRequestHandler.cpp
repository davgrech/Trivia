#include "GameRequestHandler.h"

bool GameRequestHandler::isRequestRelevant(RequestInfo request)
{
    return CLIENT_LEAVE_GAME || CLIENT_GET_QUESTION || CLIENT_SUBMIT_ANSWER || CLIENT_GET_GAME_RESULT;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo value)
{
    RequestResult myResult;
    
    switch (value.id)
    {
        case CLIENT_LEAVE_GAME:
        {
            myResult = leaveGame(value);
            break;
        }
        case CLIENT_GET_QUESTION:
        {
            myResult = getQuestions(value);
            break;
        }
        case CLIENT_SUBMIT_ANSWER:
        {
            myResult = submitAnswer(value);
            break;
        }
        case CLIENT_GET_GAME_RESULT:
        {
            myResult = getGameResults(value);
            break;
        }
        default:
        {
            throw std::exception("not in this handle");
            break;
        }
    }
    return myResult;
}

std::string GameRequestHandler::getType()
{
    return typeid(this).name();
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

    GetGameResultsResponse myResponse;
    myResponse.results = this->m_gameManager.getGame(this->m_game.getId()).getResults();
    myResponse.status;
    myResponse.status = (int)doesGameEnd(myResponse.results);
    if (!myResponse.status)
    {
        myResponse.results.clear();
        return RequestResult{ JRPS::serializeResponse(myResponse), this };
    }
    else
    {
        return RequestResult{ JRPS::serializeResponse(myResponse), this->m_handlerFactory.createMenuRequestHandler(this->m_user) };
    }
    
   
}

RequestResult GameRequestHandler::leaveGame(RequestInfo myInfo)
{
    LeaveGameResponse myResponse;
    this->m_gameManager.getGame(this->m_game.getId()).removePlayer(this->m_user);
    myResponse.status = 1;


    return RequestResult{JRPS::serializeResponse(myResponse), m_handlerFactory.createMenuRequestHandler(this->m_user)};
}

bool GameRequestHandler::doesGameEnd(std::vector<PlayerResults> myResults)
{
    for (auto itr = myResults.begin(); itr != myResults.end(); itr++) {
        //if one of the players didnt finish all the questions then game isnt finish
        if (itr->correctAnswerCount + itr->wrongAnswerCount != this->m_game.getNumOfQuestions())
        {
            return false;
        }
    }
    return true;
}
