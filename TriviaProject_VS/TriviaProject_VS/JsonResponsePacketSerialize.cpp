#include "JsonResponsePacketSerialize.h"
#include <nlohmann/json.hpp>

using nlohmann::json;
/*
* func that inits a message according to agrred msg structure
*/
std::vector<unsigned char> ConvertMsg(std::string msg)
{
    std::vector<unsigned char> response;
    

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
    std::string msg;
    j["status"] = value.status;
    msg = j.dump();
   

    
    std::copy(msg.begin(), msg.end(), std::back_inserter(response));

    return response;
}

std::vector<unsigned char> JRPS::serializeResponse(SignoutResponse value)
{
    json j;
    std::string msg;
    std::vector<unsigned char> response;
  
    j["status"] = value.status;
    msg = j.dump();
    

    
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


std::vector<unsigned char> JRPS::serializeResponse(GetRoomResponse response)
{
    std::string json = "{\"Rooms\": [";
    
    for (RoomData room : response.rooms) {
        
        json += "{\"id\":" + std::to_string(room.id);
        json += ",\"name\":\"" + room.name + "\"";
        json += ",\"numberOfQuestions\":" + std::to_string(room.numOfQuestionsInGame);
        json += ",\"timePerQuestion\":" + std::to_string(room.timePerQuestion);
        json += ",\"maxPlayers\":" + std::to_string(room.maxPlayers) + "},";
    }

    if (response.rooms.size() != 0) // if not empty
        json = json.substr(0, json.size() - 1);
    
   
    json += "]}";

    std::vector<unsigned char> v_response(json.begin(), json.end());
    return v_response;

}

std::vector<unsigned char> JRPS::serializeResponse(GetPlayersInRoomResponse value)
{
    bool isFirstLoop = true;
    std::string str = "{\"Players\": [";
    for (std::vector<std::string>::iterator it = value.players.begin(); it != value.players.end(); ++it)
    {
        if (isFirstLoop)
            isFirstLoop = false;
        else
            str += ", ";

        str += "\"" + *it + "\"";
    }
    str += "]}";
    std::vector<unsigned char> v_response(str.begin(), str.end());
    return v_response;

}

std::vector<unsigned char> JRPS::serializeResponse(JoinRoomResponse value)
{
    json j;
    std::vector<unsigned char> response;
    
    j["status"] = value.status;
    return ConvertMsg(j.dump());
}

std::vector<unsigned char> JRPS::serializeResponse(CreateRoomResponse value)
{
    json j;
    std::vector<unsigned char> response;

    j["Id"] = value.Id;
    
    return ConvertMsg(j.dump());
}




/*
HighScores = '1#name=x,2#name=x,
*/
std::vector<unsigned char> JRPS::serializeResponse(getHighScoreResponse value)
{
    json j;
    int i = 1;
    std::vector<unsigned char> response;
    
    std::string scores;
    std::string myScores;
    
    for (auto it = value.statistics.begin(); it != value.statistics.end(); it++) {
        
        scores +=  *it + ", ";
    }
    
    j["HighScores"] = scores;

    return ConvertMsg(j.dump());
}



/*
 PersonalScore = 'name:X, CORRECT_ANS=X, TOTAL_ANS=X, GAMES=X, AVG_TIME=X, WINNER_POINTS=X,' 

*/
std::vector<unsigned char> JRPS::serializeResponse(getPersonalStatsResponse value)
{
    json j;
    std::vector<unsigned char> response;
    std::string scores;
    std::string myScores;
    for (auto it = value.statistics.begin(); it != value.statistics.end(); it++) {
        scores += *it + ",";
    }
    if (scores.size() != 0)
    {
        myScores = scores.substr(0, scores.size() - 1);
    }
    
    j["PersonalScore"] = myScores;

    return ConvertMsg(j.dump());
}

std::vector<unsigned char> JRPS::serializeResponse(CloseRoomResponse value)
{
    json j;
    std::vector<unsigned char> response;

    j["status"] = value.status;
    return ConvertMsg(j.dump());
}

std::vector<unsigned char> JRPS::serializeResponse(StartGameResponse value)
{
    json j;
    std::vector<unsigned char> response;

    j["status"] = value.status;
    return ConvertMsg(j.dump());
}

std::vector<unsigned char> JRPS::serializeResponse(GetRoomStateResponse value)
{
    json j;
    j["status"] = value.status;
    j["questionCount"] = value.questionCount;
    j["answerTimeout"] = value.answerTimeout;
    j["hasGameBegun"] = value.hasGameBegun;
    j["players"] = value.players;
    
    std::cout << j;
    return ConvertMsg(j.dump());
}

std::vector<unsigned char> JRPS::serializeResponse(LeaveRoomResponse value)
{
    json j;
   
    j["status"] = value.status;
    return ConvertMsg(j.dump());
}

std::vector<unsigned char> JRPS::serializeResponse(GetGameResultsResponse value)
{
    std::string json = "{\"status\":\"" + std::to_string(value.status) + "\", \"Results\": [";
    for (PlayerResults item : value.results)
    {
        json += "{\"averageAnswerTime\":\"" + std::to_string(item.averageAnswerTime) + "\",";
        json += "\"correctAnswerCount\":\"" + std::to_string(item.correctAnswerCount) + "\",";
        json += "\"username\": \"" + item.username + "\",";
        json += "\"wrongAnswerCount\": \"" + std::to_string(item.wrongAnswerCount) + "\"},";
    }
    if (value.results.size() != 0) // if not empty
        json = json.substr(0, json.size() - 1);


    json += "]}";

    std::vector<unsigned char> v_response(json.begin(), json.end());
    return v_response;
}

std::vector<unsigned char> JRPS::serializeResponse(SubmitAnswerResponse value)
{
    
    json j;
    j["status"] = value.status;
   
    
    return ConvertMsg(j.dump());
}

std::vector<unsigned char> JRPS::serializeResponse(GetQuestionResponse value)
{
    json j;
    value.question;
    value.results;
    value.status;
    j["question"] = value.question;
    j["status"] = value.status;
    j["results"] = value.results;




    std::cout << j << std::endl; 
    return ConvertMsg(j.dump());
}

std::vector<unsigned char> JRPS::serializeResponse(LeaveGameResponse value)
{
    json j;
    j["status"] = value.status;


   

    return ConvertMsg(j.dump());
}
