#include "GameManager.h"



GameManager::GameManager(IDatabase* myDatabase)
{
    this->m_database = myDatabase;
}





Game GameManager::createGame(Room value)
{
    std::vector<question> question_list;
    std::map<LoggedUser, GameData> myUsersList;

    std::vector<LoggedUser> myUsers = value.getAllUsers();

    
    question_list = this->m_database->getQuestions(value.getRoomData().numOfQuestionsInGame);

    int id = value.getRoomData().id;

    
    
    for (auto itr = myUsers.begin(); itr != myUsers.end(); itr++)
    {
        
       myUsersList.insert(std::pair<LoggedUser, GameData>(*itr, GameData()));
    }
    
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

