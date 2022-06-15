#include "question.h"

/*
every question is a vector of {A,B,C,D} THE ANSWER IS A a string
*/
question::question(std::string question, std::vector<std::string> _possibleAnswers, std::string correctAnswer)
{
    this->m_possibleAnswers = _possibleAnswers;
    this->m_question = question;
    this->answer = correctAnswer;
}

question::question()
{
    this->m_question = "";
}

std::string question::getQuestion()
{
    return this->m_question;
}

std::vector<std::string> question::getPossibleAnswers()
{
    return this->m_possibleAnswers;
}

std::string question::getCorrectAnswer()
{
   
    return this->answer;
    
}


