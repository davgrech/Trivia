#include "JsonRequestPacketDeserialize.h"

#include <nlohmann/json.hpp>
using nlohmann::json;

LoginRequest JRPD::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
    json j;
    LoginRequest value(
            j["password"].get<std::string>(),
            j["username"].get<std::string>()
        );
    return value;
    
}

SignupRequest JRPD::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
        json j;
    SignupRequest value(
        j["password"].get<std::string>(),
        j["username"].get<std::string>()
        j["email"].get<std::string>()
    );
    return value;
}
