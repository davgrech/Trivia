#include "Game.h"

Game::Game(int timeForQuestion, int idOfGame, std::vector<question> myQuestions, std::map<LoggedUser, GameData> listUsers) : m_players(listUsers), m_questions(myQuestions), _id(idOfGame), _timeForQustion(timeForQuestion)
{
 
}

Game::Game()
{
	
}

void Game::getQuestion(LoggedUser user)
{

}

void Game::submitAnswer(LoggedUser user, std::string answer)
{
}

void Game::removePlayer(LoggedUser user)
{
	m_players.erase(user);
	
}

std::vector<PlayerResults> Game::getResults()
{
	PlayerResults temp;
	std::vector<PlayerResults> myGameResults;
	for (auto it = this->m_players.begin(); it != this->m_players.end(); it++)
	{
		temp.averageAnswerTime = it->second.averangeAnswerTime;
		temp.correctAnswerCount = it->second.correctAnswerCount;
		temp.username = it->first.getUsername();
		temp.wrongAnswerCount = it->second.wrongAnswerCount;
		myGameResults.push_back(temp);
	}
	return myGameResults;
}

int Game::getNumOfPlayers()
{
	return this->m_players.size();
}
int Game::getNumOfQuestions()
{
	return this->m_questions.size();
}
int Game::getId()
{
	return _id;
}
