#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Room.h"
#include "LoggedUser.h"

class RoomManager
{
public:
	void createRoom(LoggedUser user, RoomData var);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();
private:
	std::map<unsigned int, Room> m_rooms;
};