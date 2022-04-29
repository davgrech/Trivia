#include "RequestHandlerFactory.h"


#include "LoginManager.h"




RequestHandleFactory& RequestHandleFactory::operator=(const RequestHandleFactory& other)
{
    this->m_database = other.m_database;
    this->m_LoginManager = other.m_LoginManager;
    
    return *this;
}

RequestHandleFactory::RequestHandleFactory(IDatabase* db) : m_database(db), m_LoginManager(db) {}


LoginRequestHandler* RequestHandleFactory::createLoginRequestHandler()
{
    while (true) {
        try {
            return new LoginRequestHandler(*this);
        }
        catch (...) {}
    }
    
   
}
MenuRequestHanlder* RequestHandleFactory::createMenuRequestHandler(LoggedUser logUser)
{
    while (true) {
        try {
            return new MenuRequestHanlder((*this), logUser);
        }
        catch (...) {}
    }

}


RoomManager& RequestHandleFactory::getRoomManager()
{
    return this->m_RoomManager;
}

LoginManager& RequestHandleFactory::getLoginManager()
{
    return this->m_LoginManager;
}

