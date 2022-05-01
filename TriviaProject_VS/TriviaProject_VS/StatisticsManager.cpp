#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* db) : m_database(db)
{
	this->m_database = db;
}

std::vector<std::string> StatisticsManager::getHighScore()
{
	
	return std::vector<std::string>();
}

std::vector<std::string> StatisticsManager::getUserStatustics(std::string username)
{

	return std::vector<std::string>();
}
