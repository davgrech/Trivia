#include "LoginRequestHandler.h"

#include "Request.h"
#include "Response.h"

#include "JsonResponsePacketSerialize.h"
#include "JsonRequestPacketDeserialize.h"

LoginRequestHandler::LoginRequestHandler(RequestHandleFactory* _RequestHandleFactory, LoginManager* _LoginManager) : m_handlerFactory(_RequestHandleFactory), m_loginManager(_LoginManager)
{

}
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

