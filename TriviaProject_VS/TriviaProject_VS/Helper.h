#pragma once
#include <WinSock2.h>
#include <vector>
#include <string>

enum msgType : byte
{
	//login related
	CLIENT_SIGNUP = 99,
	CLIENT_LOGIN =1,
	CLIENT_LOGOUT = 2,
	CLIENT_SIGNOUT = 3,

	//rooms related
	CLIENT_CREATE_ROOM = 4,
	CLIENT_JOIN_ROOM = 5,
	CLIENT_GET_PLAYERS_ROOM = 6,
	CLIENT_GET_ROOMS = 7,

	//statistic related
	CLIENT_GET_STATS_USER = 8,
	CLIENT_HIGH_SCORE = 9, 
	
	

};
#define FAILED 0
#define SUCCESS 1
