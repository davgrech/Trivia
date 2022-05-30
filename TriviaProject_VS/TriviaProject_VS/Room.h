#pragma once
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
	Room();
	Room(RoomData dataOfroom, std::vector<LoggedUser> users);
	Room(RoomData dataOfroom);
	std::vector<LoggedUser> getAllUsers();
	std::vector<std::string> getAllUsersInString();
	void addUser(LoggedUser user);
	bool removeUser(LoggedUser user);
	int isActive();
	RoomData& getRoomData();
	std::string getName();
	bool isInRoomAlready(std::string  userName);
	void setAllUsers(std::vector<LoggedUser> value);
	void setState(int value);
	//includes
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
	
	
};