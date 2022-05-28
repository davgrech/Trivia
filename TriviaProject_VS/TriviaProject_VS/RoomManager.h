#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Room.h"
#include "LoggedUser.h"

class RoomManager
{
public:
	RoomManager();
	void createRoom(LoggedUser user, RoomData var);
	void deleteRoom(unsigned int ID);
	unsigned int getRoomState(unsigned int ID);
	std::string getName(unsigned int ID);
	std::vector<Room> getRooms();
	Room& getRoom(unsigned int ID);
	bool deleteUserInRoom(int id);

	//getters
	
private:
	std::map<unsigned int, Room> m_rooms;
};