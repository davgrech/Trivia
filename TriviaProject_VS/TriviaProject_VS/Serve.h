#include <iostream>
#include <WinSock2.h>

#include <exception>
#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <queue>

#include "LoginRequestHandler.h"
#include "packetMessage.h"

#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
class serveTool
{
public:
	serveTool(int port, int Iface);
	
	//main function 
	void serve();

	//receive messages handler thread function
	void receiveHandle();

	//communicate thread's function 
	void cHandler(SOCKET client);


	void addReceivedMessage(Packet x);

private:
	void bindAndListen();
	
	int _port;
	int _Iface;
	SOCKET _socket;

	std::mutex _mtx1;
	std::condition_variable _cv;
	
	std::map<SOCKET, LoginRequestHandler> _clients;
	std::queue<Packet> _Hmsgs;
};