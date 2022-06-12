#include "Game.h"
#include <chrono>
Game::Game(int timeForQuestion, int idOfGame, std::vector<question> myQuestions, std::map<LoggedUser, GameData> listUsers) : m_players(listUsers), m_questions(myQuestions), _id(idOfGame), _timeForQustion(timeForQuestion)
{
 
}

Game::Game()
{
	
}

question Game::getQuestion(LoggedUser user)
{
	
	this->m_players.at(user).startingPoint = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();



	//putting some algorithem to get a random question that doesnt appear in alreadyAnswered 
	return;
}
question Game::getCurrentQuestion(LoggedUser user)
{
	return this->m_players.at(user).currentQuestion;
}


bool Game::submitAnswer(LoggedUser user, std::string answer, int time )
{
	if (!answer.compare(m_players.at(user).currentQuestion.getCorrectAnswer())){

		m_players.at(user).correctAnswerCount++;
		

		this->m_players.at(user).averangeAnswerTime = (this->m_players.at(user).averangeAnswerTime + time)
			/ (this->m_players.at(user).correctAnswerCount + this->m_players.at(user).wrongAnswerCount);



		return true;
	}
	return false;
}

void Game::removePlayer(LoggedUser user)
{
	m_players.erase(user);
	m_players.at(user).doesActive = false;
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

int Game::getStartingPoint(LoggedUser user) const
{
	return this->m_players.at(user).startingPoint;
	
}

std::map<LoggedUser, GameData> Game::getPlayers() const
{
	return this->m_players;
}


bool Game::doesUserActive(LoggedUser user) const
{
	return this->m_players.at(user).doesActive;
}
