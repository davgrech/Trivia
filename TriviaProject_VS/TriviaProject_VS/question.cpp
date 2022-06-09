#include "question.h"

/*
every question is a vector of {0,1,2,3,4} stings each index is answer and 4 is the right answer
*/
question::question(std::string question, std::vector<std::string> _possibleAnswers)
{
    this->m_possibleAnswers = _possibleAnswers;
    this->m_question = question;

}

question::question()
{
}

std::string question::getQuestion()
{
    return this->m_question;
}

std::vector<std::string> question::getPossibleAnswers()
{
    return this->m_possibleAnswers;
}

std::string question::getCorrectAnswers()
{
    return this->m_possibleAnswers[4];
}


