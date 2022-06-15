#pragma once


#include <iostream>
#include "IRequestHandler.h"

#include "RequestHandlerFactory.h"
#include "GameManager.h"


class RequestHandleFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(RequestHandleFactory& _handlerFactory, int id, LoggedUser user);


	virtual bool isRequestRelevant(RequestInfo request);
	virtual RequestResult handleRequest(RequestInfo value);
	virtual std::string getType();


	
private:
	Game m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandleFactory& m_handlerFactory;

	//requests
	RequestResult getQuestions(RequestInfo myInfo);
	RequestResult submitAnswer(RequestInfo myInfo);
	RequestResult getGameResults(RequestInfo myInfo);
	RequestResult leaveGame(RequestInfo myInfo);
	bool isZeroPlayersActive();
	bool doesGameEnd(std::vector<PlayerResults> myResults);
	
};