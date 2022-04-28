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
    //check if user already in
    //check if max players in room
    if (std::find(this->m_users.begin(), this->m_users.end(), user.getUsername()) != this->m_users.end()) {
        throw std::exception("Already in the room");
    }
    else {
        if (this->m_users.size() != this->m_metadata.maxPlayers) {
            this->m_users.push_back(user);
        }
        else {
            
            std::string errorMsg = "The room is already full max players -> " + std::to_string(this->m_metadata.maxPlayers);
            throw std::exception(errorMsg.c_str());
        }
        
    }
    
    
}

bool Room::removeUser(LoggedUser user)
{

    
    if (std::find(this->m_users.begin(), this->m_users.end(), user.getUsername()) != this->m_users.end())
    {
        this->m_users.erase(std::find(this->m_users.begin(), this->m_users.end(), user.getUsername()));
    }
    else
    {
        throw std::runtime_error("User is not at the room");
    }
    

}

bool Room::isActive()
{
    return this->m_metadata.isActive;
}
