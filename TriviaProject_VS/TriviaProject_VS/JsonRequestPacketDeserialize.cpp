#include "JsonRequestPacketDeserialize.h"

#include <nlohmann/json.hpp>
using nlohmann::json;

LoginRequest JRPD::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
    json j;
    LoginRequest value;
    value.username = j["username"].get<std::string>();
    value.password = j["password"].get<std::string>();
    return value;
    
}

SignupRequest JRPD::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
        json j;

        SignupRequest value;
        
        value.username = j["useranme"].get<std::string>();
        value.password = j["password"].get<std::string>();
        value.email = j["email"].get<std::string>();
    return value;
}
