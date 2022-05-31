#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "LoggedUser.h"
#include "question.h"

struct GameData
{
	question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averangeAnswerTime;
};


class Game
{
public:
	Game(int timeForQuestion, int idOfGame, std::vector<question> myQuestions, std::map<LoggedUser, GameData> listUsers);
	void getQuestion(LoggedUser user);
	void submitAnswer(LoggedUser, std::string answer);
	void removePlayer(LoggedUser);
	int getId();
private:
	int _id;
	int _timeForQustion;
	std::vector<question> m_questions;
	std::map<LoggedUser, GameData> m_players;
};