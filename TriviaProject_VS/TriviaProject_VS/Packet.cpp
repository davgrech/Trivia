#include "Packet.h"

Packet::Packet(SOCKET client, RequestInfo Hmsg) : _client(client), _Hmsg(Hmsg)
{
}

SOCKET Packet::getClient()
{
    return _client;
}

RequestInfo Packet::getMsg()
{
    return _Hmsg;
}
