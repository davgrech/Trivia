#include "Room.h"

Room::Room(RoomData dataOfroom, std::vector<LoggedUser> users) : m_metadata(dataOfroom), m_users(users)
{
}

Room::Room(RoomData dataOfroom) : m_metadata(dataOfroom)
{
}

std::vector<std::string> Room::getAllUsers()
{
    std::vector<std::string> tempVec;
    for (auto itr = this->m_users.begin(); itr != this->m_users.end(); itr++)
    {
        tempVec.push_back(itr->getUsername());
    }
    return tempVec;
}

void Room::addUser(LoggedUser user)
{
    
    this->m_users.push_back(user);
    
}

bool Room::removeUser(LoggedUser user)
{
    auto it = std::find(this->m_users.begin(), this->m_users.end(), user);
    if (it != this->m_users.end()) {
        this->m_users.erase(it);
        return true;
    }
    return false;
}

bool Room::isActive()
{
    return this->m_metadata.isActive;
}
