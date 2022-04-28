#pragma once
#include <iostream>
#include <string>
#include "IRequestHandler.h"
class MenuRequestHanlder : public IRequestHandler
{
private:
	

public:
	virtual bool isRequestRelevant(RequestInfo request);
	virtual RequestResult handleRequest(RequestInfo value);
};