#include "GameRequestHandler.h"

bool GameRequestHandler::isRequestRelevant(RequestInfo request)
{
    return CLIENT_LEAVE_GAME == request.id || CLIENT_GET_QUESTION == request.id || CLIENT_SUBMIT_ANSWER == request.id || CLIENT_GET_GAME_RESULT == request.id;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo value)
{
    RequestResult myResult;
    
    switch (value.id)
    {
        case CLIENT_LEAVE_GAME:
        {
            myResult = leaveGame(value);
            break;
        }
        case CLIENT_GET_QUESTION:
        {
            myResult = getQuestions(value);
            break;
        }
        case CLIENT_SUBMIT_ANSWER:
        {
            myResult = submitAnswer(value);
            break;
        }
        case CLIENT_GET_GAME_RESULT:
        {
            myResult = getGameResults(value);
            break;
        }
        default:
        {
            throw std::exception("not in this handle");
            break;
        }
    }
    return myResult;
}

std::string GameRequestHandler::getType()
{
    return typeid(this).name();
}

GameRequestHandler::GameRequestHandler(RequestHandleFactory& _handlerFactory, int id, LoggedUser user) : m_user(user), m_handlerFactory(_handlerFactory),
m_gameManager(_handlerFactory.getGameManager()), m_game(_handlerFactory.getGameManager().getGame(id))
{
   
}

RequestResult GameRequestHandler::getQuestions(RequestInfo myInfo)
{
    GetQuestionResponse myResponse;
    question myQuestion;

    //get my current msg
    myQuestion = this->m_gameManager.getGame(this->m_game.getId()).getQuestionRequst(this->m_user);

    myResponse.question = myQuestion.getQuestion();
    myResponse.results = myQuestion.getPossibleAnswers();
    myResponse.correct = myQuestion.getCorrectAnswer();
    myResponse.question == "" ? myResponse.status = 0 : myResponse.status = 1;

   
    return RequestResult{JRPS::serializeResponse(myResponse), this};
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo myInfo)
{
    SubmitAnswerRequest myRequest;
    SubmitAnswerResponse myResponse;
    bool isCorrect;



    myRequest = JRPD::deserializeSubmitAnswerRequest(myInfo.buffer);

    //check if user finished to submit answers 
    if (this->m_gameManager.getGame(this->m_game.getId()).isFinishedToAnswerAllOfTheQusetions(this->m_user))
    {
        throw std::exception("my man just finished to answer all the questions already...");
    }


    //get question 
    
    question myQuestion = this->m_gameManager.getGame(this->m_game.getId()).getCurrentQuestion(this->m_user);

    //check if question of client is valid
    if (myRequest.answerId != "A" && myRequest.answerId != "B" && myRequest.answerId != "C" && myRequest.answerId != "D") {
        isCorrect =  this->m_gameManager.getGame(this->m_game.getId()).submitAnswer(this->m_user, "X", this->m_gameManager.getGame(this->m_game.getId()).getTimerPerQuestion());
        myResponse.status = isCorrect;
    }
    else
    {
        int x = int(myRequest.answerId[0]) - 'A';
        std::string myAnswer = myQuestion.getPossibleAnswers()[x];
        int time = 0;

        //calculate the time in seconds
        time = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count())
            - this->m_gameManager.getGame(this->m_game.getId()).getStartingPoint(this->m_user);

        //submit answer
        isCorrect = this->m_gameManager.getGame(this->m_game.getId()).submitAnswer(this->m_user, myAnswer, time);

        //return 0 if 
        myResponse.status = isCorrect;
    }
        
    //get the answer in string
   

    return RequestResult{JRPS::serializeResponse(myResponse), this};
}

RequestResult GameRequestHandler::getGameResults(RequestInfo myInfo)
{

    GetGameResultsResponse myResponse;
    myResponse.status = false;
    //check if players active
    if (!isZeroPlayersActive())
    {
        myResponse.results = this->m_gameManager.getGame(this->m_game.getId()).getResults();

        myResponse.status = doesGameEnd(myResponse.results);
    }
    
    if (!myResponse.status)
    {
        myResponse.results.clear();
        return RequestResult{ JRPS::serializeResponse(myResponse), this };
    }
    else
    {
        leaveGame(myInfo);
        return RequestResult{ JRPS::serializeResponse(myResponse), this->m_handlerFactory.createMenuRequestHandler(this->m_user) };
    }
    
   
}

RequestResult GameRequestHandler::leaveGame(RequestInfo myInfo)
{
    LeaveGameResponse myResponse;
    this->m_gameManager.getGame(this->m_game.getId()).removePlayer(this->m_user);
    if (isZeroPlayersActive())
    {
        //TODO: update stats of the game
        this->m_handlerFactory.getRoomManager().deleteRoom(this->m_game.getId());
        this->m_gameManager.deleteGame(this->m_game);
       

    }
  
    myResponse.status = 1;


    return RequestResult{JRPS::serializeResponse(myResponse), m_handlerFactory.createMenuRequestHandler(this->m_user)};
}

bool GameRequestHandler::isZeroPlayersActive()
{
    std::map<LoggedUser, GameData> myPlayers = this->m_gameManager.getGame(this->m_game.getId()).getPlayers();
    for (auto it = myPlayers.begin(); it != myPlayers.end(); it++)
    {
        if (it->second.doesActive)
        {
            return false;
        }
    }
    return true;
   
}



bool GameRequestHandler::doesGameEnd(std::vector<PlayerResults> myResults)
{
    for (auto itr = myResults.begin(); itr != myResults.end(); itr++) {
        
        //only check if player finished if he didnt leave. if he left
        if (this->m_gameManager.getGame(this->m_game.getId()).doesUserActive(itr->username))
        {

            //if one of the players didnt finish all the questions then game isnt finish

            if (itr->correctAnswerCount + itr->wrongAnswerCount != this->m_game.getNumOfQuestions())
            {
                return false;
            }
        }
        
    }
    return true;
}
