#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "IDatabase.h"

class StatisticsManager 
{
public:
	StatisticsManager(IDatabase* db);
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatustics(std::string username);
private:
	IDatabase* m_database;

};