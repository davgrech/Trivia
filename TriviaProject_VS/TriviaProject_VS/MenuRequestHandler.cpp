#include "MenuRequestHandler.h"

MenuRequestHanlder::MenuRequestHanlder(RequestHandleFactory& handleFactory, LoggedUser loggedUser) : m_handlerFactory(handleFactory), m_user(loggedUser), m_roomManager(handleFactory.getRoomManager()), m_statisticsManager(handleFactory.getStatisticManager())
{

    
}

bool MenuRequestHanlder::isRequestRelevant(RequestInfo request)
{
    return request.id == CLIENT_CREATE_ROOM || 
           request.id == CLIENT_JOIN_ROOM   ||
           request.id == CLIENT_GET_STATS_USER ||
           request.id == CLIENT_GET_PLAYERS_ROOM ||
           request.id == CLIENT_GET_ROOMS ||
           request.id == CLIENT_SIGNOUT ||
           request.id == CLIENT_LOGOUT ||
           request.id == CLIENT_HIGH_SCORE;
}

RequestResult MenuRequestHanlder::handleRequest(RequestInfo value)
{
    RequestResult myResult;
    
    //roomManager related
    if (value.id == CLIENT_GET_ROOMS){ //done
        myResult = getRooms(value);
    }
    else if (value.id == CLIENT_GET_PLAYERS_ROOM) { // done
        myResult = getPlayersInRoom(value);
    }
    else if (value.id == CLIENT_JOIN_ROOM) { //done
        myResult = joinRoom(value);
    }
    else if (value.id == CLIENT_CREATE_ROOM) { // done
        myResult = createRoom(value);
    }
    //statistic related
    else if (value.id == CLIENT_GET_STATS_USER) { // done
        myResult = getPersonalStats(value);
    }
    else if (value.id == CLIENT_HIGH_SCORE) { // done
        myResult = getHighScore();
    }
    //login manager related
    else if (value.id == CLIENT_SIGNOUT) { //done 
        myResult = signout();
       


    }
    else if (value.id == CLIENT_LOGOUT) { // done
        myResult = logout();
    }
    else
    {
        throw(std::exception("Not in cases of MenuRequest"));
    }
    return myResult;
}


RequestResult MenuRequestHanlder::signout()
{
    SignoutResponse signoutRes;

    std::string user = this->m_user.getUsername();

    this->m_handlerFactory.getLoginManager().signout(user);
     signoutRes.status = SUCCESS;

     return RequestResult{JRPS::serializeResponse(signoutRes), this->m_handlerFactory.createLoginRequestHandler()};
}

RequestResult MenuRequestHanlder::logout()
{
    LogoutResponse logoutRes;
    this->m_handlerFactory.getLoginManager().logout(this->m_user.getUsername());

    logoutRes.status = SUCCESS;
    return RequestResult{JRPS::serializeResponse(logoutRes), this->m_handlerFactory.createLoginRequestHandler()};
}

std::string MenuRequestHanlder::getType()
{
    return typeid(this).name();
}

RequestResult MenuRequestHanlder::getRooms(RequestInfo info)
{
    GetRoomResponse getRoomRes;
    std::vector<Room> rooms = this->m_roomManager.getRooms();
    for (auto it = rooms.begin(); it != rooms.end(); it++) {
        if (it->isActive() == ROOM_OPEN) {
            getRoomRes.rooms.push_back(it->getRoomData());
        }
    }
    getRoomRes.status = 1;

    return RequestResult{JRPS::serializeResponse(getRoomRes), this};
}

RequestResult MenuRequestHanlder::getPlayersInRoom(RequestInfo info)
{
    GetPlayersInRoomResponse PlayersInRoomRes;
    GetPlayersInRoomRequest getPlayersInRoomReq;

    getPlayersInRoomReq  = JRPD::deserializeGetPlayersRequest(info.buffer);
    std::vector<std::string> myUsers = this->m_roomManager.getRoom(getPlayersInRoomReq.roomId).getAllUsersInString();
    
    PlayersInRoomRes.players = myUsers;
   
    return RequestResult{JRPS::serializeResponse(PlayersInRoomRes), this};
}

RequestResult MenuRequestHanlder::getPersonalStats(RequestInfo info)
{
    getPersonalStatsResponse statsRes;
    statsRes.statistics = this->m_statisticsManager.getUserStatustics(this->m_user.getUsername());

    return RequestResult{JRPS::serializeResponse(statsRes), this};
}

RequestResult MenuRequestHanlder::getHighScore()
{
    getHighScoreResponse HighScoreRes;
    HighScoreRes.statistics = this->m_statisticsManager.getHighScore();

    return RequestResult{JRPS::serializeResponse(HighScoreRes), this};
}

RequestResult MenuRequestHanlder::joinRoom(RequestInfo info)
{
    JoinRoomRequest roomReq;
    JoinRoomResponse roomRes;

    roomReq = JRPD::deserializeJoinRoomRequest(info.buffer);
    Room room = this->m_roomManager.getRoom(roomReq.roomId);
    if (room.getRoomData().name == "") {
        throw std::exception("the room doesnt exist");
    }
    if (room.getRoomData().isActive != ROOM_OPEN){
        throw std::exception("room closed or active");
    }
    this->m_roomManager.getRoom(roomReq.roomId).addUser(this->m_user);
    roomRes.status = SUCCESS; 

    // will be changed
    return RequestResult{ JRPS::serializeResponse(roomRes), m_handlerFactory.createRoomMemberRequest(this->m_user.getUsername(), roomReq.roomId)};
}

RequestResult MenuRequestHanlder::createRoom(RequestInfo info)
{
    CreateRoomRequest createRoomReq;
    CreateRoomResponse createRoomRes;

    //int id = random_a_valid_RoomId()

    int newID = rand();
    while (this->m_roomManager.getRoom(newID).getRoomData().name != "" || this->m_handlerFactory.getGameManager().getGame(newID).getNumOfPlayers() != 0)
    {
        newID = rand();
    }


    createRoomReq = JRPD::deserializeCreateRoomRequest(info.buffer);
    if (createRoomReq.maxUsers > 4) {
        throw std::exception("4 players is the largest room!");
    }
    if (createRoomReq.roomName == "") {
        throw std::exception("name cant be empty");
    }
    if (createRoomReq.maxUsers < 1) {
        throw std::exception("at least one player in a room!");
    }
    if (createRoomReq.questionCount > 10) {
        throw std::exception("not more than 10 question!");
    }
    //{"message":"
    if (createRoomReq.questionCount < 1) {
        throw std::exception("at least 1 question!");
    }
    if (createRoomReq.answerTimeout < 3)
    {
        throw std::exception("at least 4 seconds of timout!");
    }
    /*
    unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
    */
    RoomData RoomInfo
    {
        newID, // to check !!!!!! will be changed
        createRoomReq.roomName,
        createRoomReq.maxUsers,
        createRoomReq.questionCount,
        createRoomReq.answerTimeout,
        ROOM_OPEN

    };
    this->m_roomManager.createRoom(m_user, RoomInfo);

    createRoomRes.Id = newID;
    


    //will be changed
    return RequestResult{JRPS::serializeResponse(createRoomRes), m_handlerFactory.createRoomAdminRequest(this->m_user.getUsername(), this->m_roomManager.getRoom(newID))};
}
