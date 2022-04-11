#include "SignUpRequestHandler.h"

bool SignUpRequestHandler::isRequestRelevant()
{
    return true;
}

RequestResult SignUpRequestHandler::handleRequest(RequestInfo value)
{
    RequestResult u{
        value.buffer,
        NULL
    };
    return u;
}
