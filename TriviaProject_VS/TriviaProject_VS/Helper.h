#pragma once
#include <WinSock2.h>
#include <vector>
#include <string>

enum msgType : byte
{
	CLIENT_SIGNUP = 0,
	CLIENT_LOGIN = 1,
	SEND_MENU = 2,
	SERVER_ERROR = 3,

};
