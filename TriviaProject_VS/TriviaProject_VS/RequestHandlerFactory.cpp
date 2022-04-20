#include "RequestHandlerFactory.h"

#include "SqliteDatabase.h"
#include "LoginManager.h"


RequestHandleFactory::RequestHandleFactory(IDatabase* db) : m_database(db), m_LoginManager(db)
{
}
//}
//
LoginRequestHandler* RequestHandleFactory::createLoginRequestHandler()
{
    LoginRequestHandler* rq = new LoginRequestHandler(this, &this->m_LoginManager);
    return rq;
}

MenuRequestHanlder* RequestHandleFactory::createMenuRequestHandler()
{
    MenuRequestHanlder* value = new MenuRequestHanlder();

    return value;
}

LoginManager& RequestHandleFactory::getLoginManager()
{
    return this->m_LoginManager;
}

