#pragma once
#include <iostream>
#include <string>
#include <vector>

class question
{
	public:
		question(std::string question, std::vector<std::string> _possibleAnswers);
		question();
		std::string getQuestion();
		std::vector<std::string> getPossibleAnswers();
		std::string getCorrectAnswers();
		
		
	private:
		std::string m_question;
		std::vector<std::string>  m_possibleAnswers;

};