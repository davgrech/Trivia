#include <iostream>
#include <string>
#include <vector>
#include "LoggedUser.h"

struct RoomData {
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
};


class Room
{

public:
	std::vector<std::string> getAllUsers();
	void addUser(LoggedUser user);
	bool removeUser(LoggedUser user);

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
	
	
};