#include "RequestHandlerFactory.h"


#include "LoginManager.h"






RequestHandleFactory::RequestHandleFactory(IDatabase* db) : m_database(db), m_LoginManager(db), m_StatisticManager(db), m_gameManager(db) {}


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

RoomMemberRequestHandler* RequestHandleFactory::createRoomMemberRequest(std::string userName, int id)
{
    while (true) {
        try {
            
            return new RoomMemberRequestHandler(m_RoomManager.getRoom(id),LoggedUser(userName), (*this));
        }
        catch (...) {}
    }
}

RoomAdminRequestHandler* RequestHandleFactory::createRoomAdminRequest(std::string userName, Room& room)
{
    while (true) {
        try {
            return new RoomAdminRequestHandler(room, LoggedUser(userName), (*this));
        }
        catch (...) {}
    }
}

GameRequestHandler* RequestHandleFactory::createGameRequestHandler(int id, LoggedUser user)
{
    while (true)
    {
        try {
            return new GameRequestHandler((*this), id, user);
        }
        catch(...){}
    }
    return nullptr;
}


RoomManager& RequestHandleFactory::getRoomManager()
{
    return this->m_RoomManager;
}

LoginManager& RequestHandleFactory::getLoginManager()
{
    return this->m_LoginManager;
}

StatisticsManager& RequestHandleFactory::getStatisticManager()
{
    return this->m_StatisticManager;
}

GameManager& RequestHandleFactory::getGameManager()
{
    return this->m_gameManager;
}

void RequestHandleFactory::deleteUser(std::string username)
{
    this->m_LoginManager.logout(username);
}

