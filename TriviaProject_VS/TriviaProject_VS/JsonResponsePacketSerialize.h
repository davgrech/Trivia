#pragma once

#include <iostream>
#include "Response.h"




class JRPS {
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse value);
	static std::vector<unsigned char> serializeResponse(LoginResponse value);
	static std::vector<unsigned char> serializeResponse(SignupResponse value);
	static std::vector<unsigned char> serializeResponse(SignoutResponse value);


	static std::vector<unsigned char> serializeResponse(LogoutResponse value);
	static std::vector<unsigned char> serializeResponse(GetRoomResponse value);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomResponse value);
	static std::vector<unsigned char> serializeResponse(JoinRoomResponse value);
	static std::vector<unsigned char> serializeResponse(CreateRoomResponse value);
	static std::vector<unsigned char> serializeResponse(getHighScoreResponse value);
	static std::vector<unsigned char> serializeResponse(getPersonalStatsResponse value);
	






};