#pragma once
#include "IRequestHandler.h"
class LoginRequestHandler : public IRequestHandler
{
private:

public:
	//LoginRequestHandler() = default;
	virtual bool isRequestRelevant(RequestInfo request);
	virtual RequestResult handleRequest(RequestInfo value);
};