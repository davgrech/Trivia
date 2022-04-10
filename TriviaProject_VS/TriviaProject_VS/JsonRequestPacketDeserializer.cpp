#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::DeserializeLoginRequest(char* buffer)
{
	return LoginRequest();
}

SignupRequest JsonRequestPacketDeserializer::DeserializeSignupRequest(char* buffer)
{
	return SignupRequest();
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(char* buffer)
{
	return GetPlayersInRoomRequest();
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(char* buffer)
{
	return JoinRoomRequest();
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(char* buffer)
{
	return CreateRoomRequest();
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubminAnswerRequest(char* buffer)
{
	return SubmitAnswerRequest();
}
