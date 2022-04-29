#include "JsonResponsePacketSerialize.h"
#include <nlohmann/json.hpp>

using nlohmann::json;
/*
* func that inits a message according to agrred msg structure
*/
std::vector<unsigned char> ConvertMsg(std::string msg)
{
    std::vector<unsigned char> response;
    std::string sizeOfmsg;
    sizeOfmsg = std::to_string(msg.length());
    std::copy(msg.begin(), msg.end(), std::back_inserter(response));
    return response;
}

void SizeToValue(std::string size, std::vector<unsigned char>& value)
{
    for (int i = 0; i < 4 - size.length(); i++)
    {
        value.push_back('0');
    }
    for (int i = 0; i < size.length(); i++)
    {
        value.push_back(size[i]);
    }
}

std::vector<unsigned char> JRPS::serializeResponse(ErrorResponse value)
{
    json j;
    std::vector<unsigned char> response;
    std::string msg, sizeOfmsg;
    j["message"] = value.message;
    msg = j.dump();
    std::copy(msg.begin(), msg.end(), std::back_inserter(response));
    return response;

}

std::vector<unsigned char> JRPS::serializeResponse(LoginResponse value) // login code - 1
{
    json j;
    std::vector<unsigned char> response;
    std::string msg, sizeOfmsg;
    j["status"] = value.status;
    msg = j.dump();
    sizeOfmsg = std::to_string(msg.length());
    
    //response.push_back('1');
    //SizeToValue(sizeOfmsg, response);
    std::copy(msg.begin(), msg.end(), std::back_inserter(response));

    return response;
}

std::vector<unsigned char> JRPS::serializeResponse(SignupResponse value) // signup code - 0
{
    json j;
    std::vector<unsigned char> response;
    std::string msg, sizeOfmsg;
    j["status"] = value.status;
    msg = j.dump();
    sizeOfmsg = std::to_string(msg.length());

    //response.push_back('0');
    //SizeToValue(sizeOfmsg, response);
    std::copy(msg.begin(), msg.end(), std::back_inserter(response));

    return response;
}

std::vector<unsigned char> JRPS::serializeResponse(LogoutResponse value)
{
    json j;
    std::vector<unsigned char> response;
    std::string msg, sizeOfmsg;
    j["status"] = value.status;
    return ConvertMsg(j.dump());
}

std::vector<unsigned char> JRPS::serializeResponse(GetRoomResponse value)
{
    json j;
    std::vector<unsigned char> response;
    std::string msg, sizeOfmsg, rooms;
    j["status"] = value.status;
    for (auto RoomIt = value.rooms.begin(); RoomIt != value.rooms.end(); RoomIt++) // itrate through all rooms
    {
        rooms += RoomIt->name;
    }
    j["Rooms"] = rooms;
    return ConvertMsg(j.dump());
}

std::vector<unsigned char> JRPS::serializeResponse(GetPlayersInRoomResponse value)
{
    json j;
    std::vector<unsigned char> response;
    std::string msg, sizeOfmsg, Players;
    for (auto it = value.players.begin(); it != value.players.end(); it++)
    {
        Players += *it + ", ";
    }
    j["Players"] = Players;

    return ConvertMsg(j.dump());
}

std::vector<unsigned char> JRPS::serializeResponse(JoinRoomResponse value)
{
    json j;
    std::vector<unsigned char> response;
    std::string msg, sizeOfmsg;
    j["status"] = value.status;
    return ConvertMsg(j.dump());
}

std::vector<unsigned char> JRPS::serializeResponse(CreateRoomResponse value)
{
    json j;
    std::vector<unsigned char> response;
    std::string msg, sizeOfmsg;
    j["status"] = value.status;
    return ConvertMsg(j.dump());
}
