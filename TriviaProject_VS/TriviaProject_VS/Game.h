#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "LoggedUser.h"
#include "question.h"
#include "Response.h"
struct GameData
{
	//this one will tlel me which is the current answer
	question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averangeAnswerTime;
	bool doesActive;
	unsigned int startingPoint; 
	//this one will tell me what and when the player finished to answer all the questions
	std::vector<question> hasAlreadyAnswered;


	
};


class Game
{
public:
	Game(int timeForQuestion, int idOfGame, std::vector<question> myQuestions, std::map<LoggedUser, GameData> listUsers);
	Game();
	question getQuestion(LoggedUser user);
	question getCurrentQuestion(LoggedUser user);


	bool submitAnswer(LoggedUser user, std::string answer,int time);
	void removePlayer(LoggedUser user);
	std::vector<PlayerResults> getResults();
	int getNumOfPlayers();
	int getNumOfQuestions();
	int getId();
	int getStartingPoint(LoggedUser user) const;
	std::map<LoggedUser, GameData> getPlayers() const;

	bool doesUserActive(LoggedUser user) const;
private:
	int _id;
	int _timeForQustion;
	std::vector<question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	
};