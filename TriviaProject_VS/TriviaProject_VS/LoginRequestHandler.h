#pragma once
#include "IRequestHandler.h"
#include "Request.h"
class LoginRequestHandler : public IRequestHandler
{
private:

public:
	//LoginRequestHandler() = default;

	//father function 
	virtual bool isRequestRelevant(RequestInfo request);
	virtual RequestResult handleRequest(RequestInfo value);

	//child functions
	RequestResult login(RequestInfo value);
	RequestResult signup(RequestInfo value);
};