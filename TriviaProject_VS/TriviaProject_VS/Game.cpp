#include "Game.h"

Game::Game(int timeForQuestion, int idOfGame, std::vector<question> myQuestions, std::map<LoggedUser, GameData> listUsers) : m_players(listUsers), m_questions(myQuestions), _id(idOfGame), _timeForQustion(timeForQuestion)
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

int Game::getNumOfPlayers()
{
	return this->m_players.size();
}

int Game::getId()
{
	return _id;
}
