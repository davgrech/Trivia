#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

class RequestHandleFactory;

class LoginRequestHandler : public IRequestHandler
{
private:
	LoginManager* m_loginManager;
	RequestHandleFactory* m_handlerFactory;
public:

	LoginRequestHandler(RequestHandleFactory* _RequestHandleFactory, LoginManager* _LoginManager);
	
	//LoginRequestHandler() = default;

	//father function 
	virtual bool isRequestRelevant(RequestInfo request);
	virtual RequestResult handleRequest(RequestInfo value);

	//child functions
	/*RequestResult login(RequestInfo value);
	RequestResult signup(RequestInfo value);*/
};