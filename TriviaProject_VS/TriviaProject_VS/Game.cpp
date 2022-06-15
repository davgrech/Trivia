#include "Game.h"
#include <chrono>
Game::Game(int timeForQuestion, int idOfGame, std::vector<question> myQuestions, std::map<LoggedUser, GameData> listUsers) : m_players(listUsers), m_questions(myQuestions), _id(idOfGame), _timeForQustion(timeForQuestion)
{
 
}

Game::Game()
{
	
}



std::string Game::getNotAnsweredQuestion(LoggedUser user)
{

	std::vector<std::string> myValidQuestions;
	for (auto it = m_questions.begin(); it != m_questions.end(); it++)
	{
		if (isNotInAnsweredQuestions(user, *it))
		{
			myValidQuestions.push_back(it->getQuestion());
		}
	}

	//get a random qeustion
	if (myValidQuestions.size())
	{
		srand(time(NULL));
		int random = rand() %myValidQuestions.size();
		auto it = myValidQuestions.cbegin();

		std::advance(it, random);
		return *it;
		
	}
	else
	{
		return "";
	}
	
}
bool Game::isNotInAnsweredQuestions(LoggedUser user, question myQuestion)
{
	std::vector<question> myAnsweredQuestions = this->m_players.at(user).hasAlreadyAnswered;
	for (auto it = myAnsweredQuestions.begin(); it != myAnsweredQuestions.end(); it++)
	{
		if (!it->getQuestion().compare(myQuestion.getQuestion()))
		{
			return false;
		}
	}
	return true;
}






question Game::getQuestionRequst(LoggedUser user)
{
	question myQuestion;
	this->m_players.at(user).startingPoint = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	std::string questionInString = getNotAnsweredQuestion(user);



	//putting some algorithem to get a random question that doesnt appear in alreadyAnswered 

	//if no questions left the output is ""
	for (auto it = m_questions.begin(); it != m_questions.end(); it++)
	{
		if (!it->getQuestion().compare(questionInString))
		{
			myQuestion = *it;
			this->m_players.at(user).currentQuestion = myQuestion;
			break;
		}
	}

	
	return myQuestion;
}
question Game::getCurrentQuestion(LoggedUser user)
{
	return this->m_players.at(user).currentQuestion;
}


bool Game::submitAnswer(LoggedUser user, std::string answer, int time )
{
	bool isCorrect = false;
	if (answer == "X")
	{
		m_players.at(user).wrongAnswerCount++;
		isCorrect = false;
	}
	else
	{
		if (!answer.compare(m_players.at(user).currentQuestion.getCorrectAnswer())) {


			isCorrect = true;
			m_players.at(user).correctAnswerCount++;
		}
		else
		{
			m_players.at(user).wrongAnswerCount++;
			isCorrect = false;

		}
	}
	

	//calculating avg time
	this->m_players.at(user).averangeAnswerTime = (this->m_players.at(user).averangeAnswerTime + time)
		/ (this->m_players.at(user).correctAnswerCount + this->m_players.at(user).wrongAnswerCount);


	//restarting starting point
	this->m_players.at(user).startingPoint = 0;

	//save the question that he answered
	this->m_players.at(user).hasAlreadyAnswered.push_back(m_players.at(user).currentQuestion);

	return isCorrect;
}

void Game::removePlayer(LoggedUser user)
{
	m_players.at(user).doesActive = false;
	
		
	;
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

int Game::getTimerPerQuestion()
{
	return this->_timeForQustion;
}


