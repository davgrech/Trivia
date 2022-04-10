#pragma once
#include "Request.h"
class JsonRequestPacketDeserializer {
	LoginRequest DeserializeLoginRequest(char* buffer);
	SignupRequest DeserializeSignupRequest(char* buffer);

	GetPlayersInRoomRequest deserializeGetPlayersRequest(char* buffer);
	JoinRoomRequest deserializeJoinRoomRequest(char* buffer);
	CreateRoomRequest deserializeCreateRoomRequest(char* buffer);

	SubmitAnswerRequest deserializeSubminAnswerRequest(char* buffer);
};