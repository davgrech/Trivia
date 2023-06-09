#pragma once
#include <iostream>
#include <string>
#include "IDatabase.h"
#include "sqlite3.h"
#include <io.h>
#include "question.h"

// all about information Verification and REGEX BONOUS!
#include "informationVerification.h"


#define FILE_NOT_EXIST -1


//any callback function here -> they are static
#include "SQLCallbacks.h"

//questions - sql Table
#define Q1 "INSERT INTO QUESTIONS (QUESTION, A, B,C, D, ANSWER) VALUES('1', 'a', 'b', 'c', 'd', 'a');"
#define Q2 "INSERT INTO QUESTIONS (QUESTION, A, B,C, D, ANSWER) VALUES('2', 'a', 'b', 'c', 'd', 'a');"
#define Q3 "INSERT INTO QUESTIONS (QUESTION, A, B,C, D, ANSWER) VALUES('3', 'a', 'b', 'c', 'd', 'a');"
#define Q4 "INSERT INTO QUESTIONS (QUESTION, A, B,C, D, ANSWER) VALUES('4', 'a', 'b', 'c', 'd', 'a');"
#define Q5 "INSERT INTO QUESTIONS (QUESTION, A, B,C, D, ANSWER) VALUES('5', 'a', 'b', 'c', 'd', 'a');"
#define Q6 "INSERT INTO QUESTIONS (QUESTION, A, B,C, D, ANSWER) VALUES('6', 'a', 'b', 'c', 'd', 'a');"
#define Q7 "INSERT INTO QUESTIONS (QUESTION, A, B,C, D, ANSWER) VALUES('7', 'a', 'b', 'c', 'd', 'a');"
#define Q8 "INSERT INTO QUESTIONS (QUESTION, A, B,C, D, ANSWER) VALUES('8', 'a', 'b', 'c', 'd', 'a');"
#define Q9 "INSERT INTO QUESTIONS (QUESTION, A, B,C, D, ANSWER) VALUES('9', 'a', 'b', 'c', 'd', 'a');"
#define Q10 "INSERT INTO QUESTIONS (QUESTION, A, B,C, D, ANSWER) VALUES('10', 'a', 'b', 'c', 'd', 'a');"


class SqliteDatabase : public IDatabase 
{
public:
	SqliteDatabase();
	~SqliteDatabase();

	//1.0.0

	//login
	bool doesUserExist(std::string userName);
	bool doesPasswordMatch(std::string userName, std::string userPassword);
	bool addNewUser(std::string userName, std::string userPassword, std::string userEmail, std::string phonNumber, std::string date);
	bool signout(std::string userName);
	//2.0,0

	//statistics
	virtual float getPlayersAverageAnswerTime(std::string user);
	virtual int getNumOfCorrectAnswers(std::string user);
	virtual int getNumOfTotalAnswers(std::string user);
	virtual int getNumOfPlayerGames(std::string user) ;
	virtual int getWinnerPointOfUsers(std::string user);


	virtual std::vector<std::string> getTopFive();
	

	//4.0.0

	virtual std::vector<question> getQuestions(int number);

	//virtual void addUserStatistics();

	bool createTableOrInsert(std::string statement);
	void open();
	void close();
private:
	sqlite3* db;
	
};