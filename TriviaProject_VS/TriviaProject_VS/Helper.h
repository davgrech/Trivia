#pragma once
#include <WinSock2.h>
#include <vector>
#include <string>

enum msgType : byte
{
	//login related
	CLIENT_SIGNUP = 0,
	CLIENT_LOGIN =1,
	CLIENT_LOGOUT = 2,
	CLIENT_SIGNOUT = 3,

	//rooms related
	CLIENT_CREATE_ROOM = 4,
	CLIENT_JOIN_ROOM = 5,
	CLIENT_GET_PLAYERS_ROOM = 6,
	CLIENT_GET_ROOMS = 7,

	//3.0.0
	CLIENT_LEAVE_ROOM = 8,
	CLIENT_GET_STATE = 9,
	CLIENT_START_GAME = 10,
	CLIENT_CLOSE_ROOM = 11,


	//statistic related
	CLIENT_GET_STATS_USER = 12,
	CLIENT_HIGH_SCORE = 13, 
	
	

};




enum roomState
{
	ROOM_CLOSE,
	ROOM_OPEN,
	ROOM_ACTIVE
};


#define FAILED 0
#define SUCCESS 1
