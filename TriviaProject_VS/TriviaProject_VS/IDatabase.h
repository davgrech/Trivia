#pragma once
#include <iostream>
#include <string>

class IDatabase;

class IDatabase
{
public:
	//1.0.0  - > 1.0.3
	virtual bool doesUserExist(std::string userName) = 0 ;
	virtual bool doesPasswordMatch(std::string v1, std::string v2) = 0;
	virtual bool addNewUser(std::string userName, std::string userPassword, std::string userEmail, std::string date, std::string address, std::string phonNumber) = 0;

	//2.0.0
	//virtual List<Questions> getQuestions(int) 
	virtual float getPlayersAverageAnswerTime(std::string user) = 0;
	virtual int getNumOfCorrectAnswers(std::string user) = 0;
	virtual int getNumOfTotalAnswers(std::string user) = 0;
	virtual int getNumOfPlayerGames(std::string user) = 0;


	virtual void open() = 0;
	virtual void close() = 0;
private:

};