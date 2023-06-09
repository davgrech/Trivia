#include "GameManager.h"



GameManager::GameManager(IDatabase* myDatabase)
{
    this->m_database = myDatabase;
}





Game GameManager::createGame(Room value)
{
    std::vector<question> question_list;
    std::map<LoggedUser, GameData> myUsersList =  std::map<LoggedUser, GameData>();

    std::vector<LoggedUser> myUsers = value.getAllUsers();
    std::map<std::string, GameData> proTest = std::map<std::string, GameData>();
    
    question_list = this->m_database->getQuestions(value.getRoomData().numOfQuestionsInGame);

    int id = value.getRoomData().id;

    
    GameData tempGameData;
    std::vector<std::string> x;
    tempGameData.averangeAnswerTime = 0;
    tempGameData.correctAnswerCount = 0;
    tempGameData.wrongAnswerCount = 0;
    tempGameData.doesActive = true;
    for (auto itr = myUsers.begin(); itr != myUsers.end(); itr++)
   {
        myUsersList.insert({ LoggedUser(*itr), tempGameData });
        
       
        
    }
    this->m_games.insert(std::pair<int, Game>(id, Game(value.getRoomData().timePerQuestion, id, question_list, myUsersList)));
    
    return Game(value.getRoomData().timePerQuestion, id, question_list, myUsersList);
}

void GameManager::deleteGame(Game x)
{
    this->m_games.erase(x.getId());
}

Game& GameManager::getGame(int _id)
{
    Game* x = new Game();
    
    if (this->m_games.find(_id) != this->m_games.end())
    {
        return this->m_games.at(_id);

    }
    else
    {
        return *x;
    }
}

