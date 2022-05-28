
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Room.h"



struct ErrorResponse {
	std::string message;
} typedef ErrorResponse;

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

struct SignoutResponse {
	unsigned int status;
};

struct LogoutResponse {
	unsigned int status;
};

struct GetRoomResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
};

struct getHighScoreResponse {
	std::vector<std::string> statistics;
};

struct getPersonalStatsResponse {
	std::vector<std::string> statistics;
};

struct JoinRoomResponse {
	unsigned int status;
};

struct CreateRoomResponse {
	unsigned int status;
};




//Json requestPacketserialize
//Json responsePacketserialize
