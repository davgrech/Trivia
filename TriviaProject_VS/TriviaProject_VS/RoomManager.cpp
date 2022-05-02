#include "RoomManager.h"
RoomManager::RoomManager()
{
	m_rooms.insert({ 0,Room() });
}

void RoomManager::createRoom(LoggedUser user, RoomData var)
{
	this->m_rooms.insert(std::pair<unsigned int, Room>(var.id, Room(var)));
	this->m_rooms.at(var.id).addUser(user);
	
	
}

void RoomManager::deleteRoom(unsigned int ID)
{
	this->m_rooms.erase(ID);
}

unsigned int RoomManager::getRoomState(unsigned int ID)
{
	return this->m_rooms.at(ID).isActive();
}

std::vector<Room> RoomManager::getRooms()
{
	std::vector<Room> vec;
	for (auto it = this->m_rooms.begin(); it != this->m_rooms.end(); it++) {
		vec.push_back(it->second);
	}
	return vec;
}

Room& RoomManager::getRoom(unsigned int ID)
{
	
	
	
	if(this ->m_rooms.find(ID) != this->m_rooms.end()) {
		return this->m_rooms.at(ID);
	}
	else {
		return this->m_rooms.at(0);
	}
}
