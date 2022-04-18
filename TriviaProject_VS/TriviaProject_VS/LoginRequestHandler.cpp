#include "LoginRequestHandler.h"
#include "Response.h"
#include "JsonResponsePacketSerialize.h"
#include "JsonRequestPacketDeserialize.h"
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
    LoginRequestHandler * x = nullptr;
    LoginResponse loginResponse;
    loginResponse.status = 1;
    auto j = JRPS::serializeResponse(loginResponse);

    RequestResult u{
        j,
        x
    };

    return u;
}

RequestResult LoginRequestHandler::login(RequestInfo value)
{
    return RequestResult();
}

RequestResult LoginRequestHandler::signup(RequestInfo value)
{
    return RequestResult();
}
