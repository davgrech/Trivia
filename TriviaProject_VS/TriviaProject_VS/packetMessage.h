#include <iostream>
#include <WinSock2.h>
class Packet {
public:
	Packet(SOCKET client, std::string msg);
	std::string getMessage();
	SOCKET getSocket();
private:
	SOCKET _client;
	std::string _msg;
};