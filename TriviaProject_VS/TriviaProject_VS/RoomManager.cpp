#include "RoomManager.h"
RoomManager::RoomManager()
{
	
}

void RoomManager::createRoom(LoggedUser user, RoomData var)
{
	std::vector<Room> roomLst = this->getRooms();
	for (int i = 0; i < roomLst.size(); i++)
	{
		if (roomLst[i].isActive() == ROOM_OPEN)
		{
			if (roomLst[i].isInRoomAlready(user.getUsername()))
			{
				throw std::exception("user in a room already");
			}
		}

	}

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

std::string RoomManager::getName(unsigned int ID)
{
	return this->m_rooms.at(ID).getRoomData().name;
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
	
	
	Room* x = new Room();
	if(this ->m_rooms.find(ID) != this->m_rooms.end()) {
		return this->m_rooms.at(ID);
	}
	else {
		
		return *x;
	}
}

bool RoomManager::deleteUserInRoom(int id)
{
	std::string roomName = m_rooms.at(id).getName();
	for (LoggedUser user : m_rooms.at(id).getAllUsers())
	{
		std::cout << user.getUsername() << " has kicked out of room " << roomName << std::endl;
	}
	m_rooms.erase(id);

	
	return false;
}
