#pragma once


#include <iostream>
#include "IRequestHandler.h"

#include "RequestHandlerFactory.h"
#include "GameManager.h"


class RequestHandleFactory;

class GameRequestHandler : public IRequestHandler
{
public:

	virtual bool isRequestRelevant(RequestInfo request);
	virtual RequestResult handleRequest(RequestInfo value);
	virtual std::string getType();
	GameRequestHandler(RequestHandleFactory& _handlerFactory, int id ,LoggedUser user);
private:
	Game m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandleFactory& m_handlerFactory;
	RequestResult getQuestions(RequestInfo myInfo);
	RequestResult submitAnswer(RequestInfo myInfo);
	RequestResult getGameResults(RequestInfo myInfo);
	RequestResult leaveGame(RequestInfo myInfo);
	
};