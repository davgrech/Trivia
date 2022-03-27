#include "packetMessage.h"

Packet::Packet(SOCKET client, std::string msg) : _client(client), _msg(msg)
{

}

std::string Packet::getMessage()
{
	return this->_msg;
}

SOCKET Packet::getSocket()
{
	return this->_client;
}
