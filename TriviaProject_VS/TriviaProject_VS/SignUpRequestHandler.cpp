#include "SignUpRequestHandler.h"
#include "Response.h"
#include "JsonResponsePacketSerialize.h"

bool SignUpRequestHandler::isRequestRelevant(RequestInfo request)
{
    return !request.id;
}

RequestResult SignUpRequestHandler::handleRequest(RequestInfo value)
{
    SignUpRequestHandler* x = nullptr;
    SignupResponse Signup;
    Signup.status = 1;
    auto j = JRPS::serializeResponse(Signup);
    RequestResult u{
        j,
        NULL
    };
    return u;
}
