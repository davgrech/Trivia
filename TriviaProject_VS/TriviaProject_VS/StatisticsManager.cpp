#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* db) : m_database(db)
{
	this->m_database = db;
}

std::vector<std::string> StatisticsManager::getHighScore()
{
	std::vector<std::string> myResult = this->m_database->getTopFive();
	return myResult;
}

std::vector<std::string> StatisticsManager::getUserStatustics(std::string username)
{
	std::string temp;
	std::vector<std::string> myResult;

	
	temp = "CORRECT_ANSWERS: ";
	temp += std::to_string(this->m_database->getNumOfCorrectAnswers(username));
	myResult.push_back(temp);

	temp = "TOTAL ANSWERS: ";
	temp += std::to_string(this->m_database->getNumOfTotalAnswers(username));
	myResult.push_back(temp);

	temp = "GAMES: ";
	temp += std::to_string(this->m_database->getNumOfPlayerGames(username));
	myResult.push_back(temp);

	temp = "AVG_TIME: ";
	temp += std::to_string(this->m_database->getPlayersAverageAnswerTime(username));
	myResult.push_back(temp);

	temp = "WINNER_POINTS: ";
	temp += std::to_string(this->m_database->getWinnerPointOfUsers(username));
	myResult.push_back(temp);

	// (CORRECT_ANSWERS: X), (CORRECT_ANSWERS: X), (CORRECT_ANSWERS: X), (CORRECT_ANSWERS: X) 
	return myResult;
}
