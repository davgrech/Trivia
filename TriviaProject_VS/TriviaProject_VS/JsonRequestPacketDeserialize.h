#pragma once

#include <iostream>
#include "Request.h"
#include "Room.h"

class JRPD {
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer);

	static GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<unsigned char> buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> buffer);

	//version 4.0.0
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(std::vector<unsigned char> buffer); 
	

};