#include "LoginRequestHandler.h"

#include "Request.h"
#include "Response.h"

#include "JsonResponsePacketSerialize.h"
#include "JsonRequestPacketDeserialize.h"

LoginRequestHandler::LoginRequestHandler(RequestHandleFactory& _RequestHandleFactory) : m_loginManager(_RequestHandleFactory.getLoginManager()), m_handlerFactory(_RequestHandleFactory)
{

}
bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
    return request.id == 1 || request.id == 0;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo value)
{
    RequestResult myResult;

    LoginRequest LoginReq;
    LoginResponse LoginRes;

    SignupRequest SignupReq;
    SignupResponse SignupRes;
    
    
   

    if (value.id == CLIENT_LOGIN) {

        //deserialize request
        LoginReq = JRPD::deserializeLoginRequest(value.buffer);
       
        bool isSucceeded = this->m_loginManager.login(LoginReq.username, LoginReq.password);

        if (isSucceeded) {
            this->m_loginManager.login(LoginReq.username, LoginReq.password);
            //return SUCCESS RESPONSE
            myResult.newHandler = this->m_handlerFactory.createMenuRequestHandler();

            LoginRes.status = SUCCESS;
            myResult.buffer = JRPS::serializeResponse(LoginRes);
        }
        else
        {
            //RETURN FAIL RESPONSE
            myResult.newHandler = nullptr;
            LoginRes.status = FAILED;
            myResult.buffer = JRPS::serializeResponse(LoginRes);
        }

        
    }
    else if (value.id == CLIENT_SIGNUP) {

        //deserialize request
        SignupReq = JRPD::deserializeSignupRequest(value.buffer);
        

        bool isSucceeded = this->m_loginManager.signup(SignupReq.username, SignupReq.password, SignupReq.email);
        if (isSucceeded) {
            myResult.newHandler = this->m_handlerFactory.createMenuRequestHandler();

            SignupRes.status = SUCCESS;
            myResult.buffer = JRPS::serializeResponse(SignupRes);
        }
        else {
            //RETURN FAIL RESPONSE
            myResult.newHandler = nullptr;
            SignupRes.status = FAILED;
            myResult.buffer = JRPS::serializeResponse(SignupRes);
        }

    }


    return myResult;
    
    
}

