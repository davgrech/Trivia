#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
private:

public:
	LoginRequestHandler() = default;
	virtual bool isRequestRelevant();
	virtual RequestResult handleRequest(RequestInfo value);
};