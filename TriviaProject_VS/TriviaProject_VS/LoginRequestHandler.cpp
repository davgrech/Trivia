#include "LoginRequestHandler.h"
bool LoginRequestHandler::isRequestRelevant()
{
    return true;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo value)
{
    RequestResult u{
        value.buffer,
        NULL
    };

    return u;
}
