#include "GameManager.h"

GameManager::GameManager(IDatabase* myDatabase)
{
    this->m_database = myDatabase;
}




//Game GameManager::createGame(Room value)
//{
//    the id is the id of the room
//    std::vector<question> list;
//
//    int id;
//
//    return Game(list, value.getAllUsers());
//}

void GameManager::deleteGame(Game x)
{
    this->m_games.erase(x.getId());
}

Game& GameManager::getGame(int _id)
{
    return this->m_games.at(_id);
}


