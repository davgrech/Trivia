#include <iostream>
#include <WinSock2.h>

#include <exception>
#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <queue>

#include "LoginRequestHandler.h"
#include "SignUpRequestHandler.h"

#include <atomic>


#include "Packet.h"


#include "JsonRequestPacketDeserialize.h"
#include "JsonResponsePacketSerialize.h"



#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);


int checkByteReceived(int ByteReceived);


class serveTool
{
public:
	serveTool();
	~serveTool();
	//main function 
	void bindAndListen();

	
	void receiveHandle();

	//communicate thread's function 
	void cHandler(SOCKET client);


	void addReceivedMessage(Packet x);
	RequestInfo createNewRequestInfo(int id, std::vector<unsigned char> value);

	SOCKET getSock();
	void addToClients(SOCKET client, LoginRequestHandler request);
	void admin_acess_function();
	

private:
	
	
	
	SOCKET _socket;

	std::mutex _mtx1;
	std::condition_variable _cv;
	
	std::map<SOCKET, IRequestHandler*> _clients;
	std::queue<Packet> _Hmsgs;
};