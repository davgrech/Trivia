#pragma once
#include <WinSock2.h>
#include <vector>
#include <string>

enum msgType : byte
{
	CLIENT_SIGNUP,
	CLIENT_LOGIN,
	CLIENT_MENU,
	SERVER_ERROR,

};
#define FAILED 0
#define SUCCESS 1
