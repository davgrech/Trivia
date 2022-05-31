#pragma once
#include "IDatabase.h"
#include "Game.h"
#include "Room.h"
#include <map>

class GameManager
{
public:
	GameManager(IDatabase* myDatabase);
	Game createGame(Room value);
	void deleteGame(Game x);
	Game& getGame(int _id);
private:
	IDatabase* m_database;
	std::map<int, Game> m_games;
};