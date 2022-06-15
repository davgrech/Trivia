#pragma once
#include <iostream>
#include <string>
#include <vector>

class question
{
	public:
		question(std::string question, std::vector<std::string> _possibleAnswers, std::string correctAnswer);
		question();
		std::string getQuestion();
		std::vector<std::string> getPossibleAnswers();
		std::string getCorrectAnswer();
		
		
	private:
		std::string m_question;
		std::string answer;
		std::vector<std::string>  m_possibleAnswers;

};