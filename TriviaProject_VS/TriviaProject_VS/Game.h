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

	//this one will tell me what and when the player finished to answer all the questions
	std::vector<question> hasAlreadyAnswered;


	
};


class Game
{
public:
	Game(int timeForQuestion, int idOfGame, std::vector<question> myQuestions, std::map<LoggedUser, GameData> listUsers);
	Game();
	void getQuestion(LoggedUser user);
	void submitAnswer(LoggedUser user, std::string answer);
	void removePlayer(LoggedUser user);
	std::vector<PlayerResults> getResults();
	int getNumOfPlayers();
	int getNumOfQuestions();
	int getId();
private:
	int _id;
	int _timeForQustion;
	std::vector<question> m_questions;
	std::map<LoggedUser, GameData> m_players;
};