#include "JsonRequestPacketDeserialize.h"

#include <nlohmann/json.hpp>
using nlohmann::json;
/*
* func that parses buffer (json format) to loginreq struct
*/
LoginRequest JRPD::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
    std::cout << std::string(buffer.begin(), buffer.end()) << std::endl;
    auto j = json::parse(buffer.begin(), buffer.end());
    LoginRequest loginreq;
    loginreq.username = j["username"];
    loginreq.password = j["password"];
    return loginreq;
    
}
/*
* same as before lol
*/
SignupRequest JRPD::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
   

    auto j = json::parse(buffer.begin(), buffer.end());
    SignupRequest signupReq;

    signupReq.username = j["username"];
    signupReq.password = j["password"];
    signupReq.email = j["email"];
    signupReq.phonNumber = j["phoneNumber"];
    signupReq.address = j["address"];
    signupReq.dateOfBirth = j["date"];


    return signupReq;
}
