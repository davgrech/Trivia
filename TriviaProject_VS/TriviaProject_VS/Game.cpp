#include "Game.h"

Game::Game(int idOfGame, std::vector<question> myQuestions, std::map<LoggedUser, GameData> listUsers) : m_players(listUsers), m_questions(myQuestions), id(idOfGame)
{
	
}

void Game::getQuestion(LoggedUser user)
{
}

void Game::submitAnswer(LoggedUser, std::string answer)
{
}

void Game::removePlayer(LoggedUser)
{
}

int Game::getId()
{
	return id;
}
