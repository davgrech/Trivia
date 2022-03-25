#include <iostream>
#include <WinSock2.h>
#include <exception>
#include <string>
#include <thread>
#include <mutex>
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
class serveTool
{
public:
	serveTool(int port, int Iface);
	void serve();
	void receiveHandle();
	void cHandler(SOCKET client);
private:
	void bindAndListen();
	
	int _port;
	int _Iface;
	SOCKET _socket;

	std::mutex _mtx1;
	std::condition_variable _cv;
};