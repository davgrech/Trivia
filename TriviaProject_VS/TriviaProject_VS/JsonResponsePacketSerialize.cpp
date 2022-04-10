#include "JsonResponsePacketSerialize.h"
#include <nlohmann/json.hpp>

using nlohmann::json;

std::vector<unsigned char> JRPS::serializeResponse(ErrorResponse value)
{
    json j;

    return std::vector<unsigned char>();
}

std::vector<unsigned char> JRPS::serializeResponse(LoginResponse value)
{
    return std::vector<unsigned char>();
}

std::vector<unsigned char> JRPS::serializeResponse(SignupResponse value)
{
    return std::vector<unsigned char>();
}
