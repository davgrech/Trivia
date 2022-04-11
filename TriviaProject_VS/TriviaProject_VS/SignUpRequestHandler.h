#pragma once
#include "IRequestHandler.h"

class SignUpRequestHandler : public IRequestHandler
{
private:

public:
	SignUpRequestHandler() = default;
	bool isRequestRelevant(RequestInfo request) override;
	RequestResult handleRequest(RequestInfo value) override;
};