#pragma once
#include <WinSock2.h>
#include <vector>
#include <string>

enum msgType : byte
{
	//login related
	CLIENT_SIGNUP,
	CLIENT_LOGIN,
	CLIENT_LOGOUT,
	CLIENT_SIGNOUT,

	//rooms related
	CLIENT_CREATE_ROOM,
	CLIENT_JOIN_ROOM,
	CLIENT_GET_PLAYERS_ROOM,
	CLIENT_GET_ROOMS,

	//statistic related
	CLIENT_GET_STATS_USER,
	CLIENT_HIGH_SCORE, 
	
	

};
#define FAILED 0
#define SUCCESS 1
