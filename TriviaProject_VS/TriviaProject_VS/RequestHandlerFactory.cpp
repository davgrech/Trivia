#include "RequestHandlerFactory.h"


#include "LoginManager.h"




RequestHandleFactory& RequestHandleFactory::operator=(const RequestHandleFactory& other)
{
    this->m_database = other.m_database;
    this->m_LoginManager = other.m_LoginManager;
    
    return *this;
}

RequestHandleFactory::RequestHandleFactory(IDatabase* db) :  m_database(db), m_LoginManager(db)
{
    this->m_database = db;
    this->m_LoginManager = LoginManager(db);
}
//}
//
LoginRequestHandler* RequestHandleFactory::createLoginRequestHandler()
{
    while (true) {
        try {
            return new LoginRequestHandler(*this);
        }
        catch (...) {}
    }

   
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

