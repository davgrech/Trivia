#include "JsonResponsePacketSerialize.h"
#include <nlohmann/json.hpp>

using nlohmann::json;

std::vector<unsigned char> JRPS::serializeResponse(ErrorResponse value)
{
    json j;
    j["message"] = value.message;
    
    return j;
}

std::vector<unsigned char> JRPS::serializeResponse(LoginResponse value)
{
    json j;
    j["status"] = value.status;
    return j;
}

std::vector<unsigned char> JRPS::serializeResponse(SignupResponse value)
{
    json j;
    j["status"] = value.status;
    return j;
}
