#include "SignUpRequestHandler.h"

bool SignUpRequestHandler::isRequestRelevant(RequestInfo request)
{
    return !request.id;
}

RequestResult SignUpRequestHandler::handleRequest(RequestInfo value)
{
    RequestResult u{
        value.buffer,
        NULL
    };
    return u;
}
