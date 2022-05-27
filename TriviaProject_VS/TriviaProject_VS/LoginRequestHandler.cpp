#include "LoginRequestHandler.h"

#include "Helper.h"

#include "JsonResponsePacketSerialize.h"
#include "JsonRequestPacketDeserialize.h"

LoginRequestHandler::LoginRequestHandler(RequestHandleFactory& _RequestHandleFactory) : m_loginManager(_RequestHandleFactory.getLoginManager()), m_handlerFactory(_RequestHandleFactory)
{

}
bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
    return request.id == 1 || request.id == 99;
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
            //return SUCCESS RESPONSE
            LoggedUser v1(LoginReq.username);
            myResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(v1);

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
        std::cout << std::string(value.buffer.begin(), value.buffer.end());
        //deserialize request
        SignupReq = JRPD::deserializeSignupRequest(value.buffer);
        

        bool isSucceeded = this->m_loginManager.signup(SignupReq.username, SignupReq.password, SignupReq.email, SignupReq.phonNumber, SignupReq.dateOfBirth);
        if (isSucceeded) {
            LoggedUser v1(SignupReq.username);
            myResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(v1);

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

