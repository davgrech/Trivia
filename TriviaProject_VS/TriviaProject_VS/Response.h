
#pragma once
#include <iostream>
#include <vector>
#include <string>




struct ErrorResponse {
	std::string message;
} typedef ErrorResponse;

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

struct LogoutResponse {
	unsigned int status;
};

struct GetRoomsResponse {
	unsigned int status;
};

struct GetPlayersInRoomResponse {
	unsigned int status;
	std::vector<std::string> statistics;
};

struct getPersonalStatsResponse {
	unsigned int status;
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
