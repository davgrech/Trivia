#include <iostream>
#include <WinSock2.h>
#include <queue>


#include "LoginRequestHandler.h"


class Packet {
public:
	Packet(SOCKET client, RequestInfo Hmsg);
	SOCKET getClient();
	RequestInfo getMsg();
private:
	SOCKET _client;
	RequestInfo _Hmsg;

};