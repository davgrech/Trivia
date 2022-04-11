
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <nlohmann/json_fwd.hpp>

using nlohmann::json;

struct GetPlayersInRoomRequest
{
	unsigned int roomId;

}typedef GetPlayersInRoomRequest;

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct SubmitAnswerRequest
{
	unsigned int answerId;
};


struct LoginRequest {
	std::string username;
	std::string password;

} typedef LoginRequest;

struct SignupRequest {
	std::string username;
	std::string password;
	std::string email;

}typedef SignupRequest;
