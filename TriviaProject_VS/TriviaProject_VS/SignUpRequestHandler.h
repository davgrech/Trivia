#include "IRequestHandler.h"

class SignUpRequestHandler : public IRequestHandler
{
private:

public:
	SignUpRequestHandler() = default;
	virtual bool isRequestRelevant();
	virtual RequestResult handleRequest(RequestInfo value);
};