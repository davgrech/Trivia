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
    signupReq.dateOfBirth = j["date"];


    return signupReq;
}

GetPlayersInRoomRequest JRPD::deserializeGetPlayersRequest(std::vector<unsigned char> buffer)
{
    auto j = json::parse(buffer.begin(), buffer.end());
    GetPlayersInRoomRequest getPlayersReq;
    std::string strRoomId = j["roomId"];
    getPlayersReq.roomId = std::stoi(strRoomId);
    return getPlayersReq;
}

JoinRoomRequest JRPD::deserializeJoinRoomRequest(std::vector<unsigned char> buffer)
{
    auto j = json::parse(buffer.begin(), buffer.end());
    std::string strRoomId;
    JoinRoomRequest joinRoomReq;
    strRoomId = j["roomId"];
    joinRoomReq.roomId = std::stoi(strRoomId);
    return joinRoomReq;
}

CreateRoomRequest JRPD::deserializeCreateRoomRequest(std::vector<unsigned char> buffer)
{
    
    auto j = json::parse(buffer.begin(), buffer.end());
    CreateRoomRequest createRoomReq;
    std::string parsing;
    parsing = j["answerTimeout"];
    createRoomReq.answerTimeout = std::stoi(parsing);
    parsing = j["questionCount"];
    createRoomReq.questionCount = std::stoi(parsing);
    createRoomReq.roomName = j["roomName"];
    parsing = j["maxUsers"];
    createRoomReq.maxUsers = std::stoi(parsing);


    return createRoomReq;
}

SubmitAnswerRequest JRPD::deserializeSubmitAnswerRequest(std::vector<unsigned char> buffer)
{
    SubmitAnswerRequest submitAnswer;
    unsigned char chrAnswer;
    auto j = json::parse(buffer.begin(), buffer.end());

    chrAnswer = j["answerId"];
    submitAnswer.answerId = chrAnswer;

    return submitAnswer;
}
