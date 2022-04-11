#include "LoginRequestHandler.h"
bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
    if (request.id != 1)
    {
        return false;
    }
    return true;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo value)
{
    LoginRequestHandler *x = nullptr;
    RequestResult u{
        value.buffer,
        x
    };

    return u;
}
