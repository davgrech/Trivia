#include "question.h"

/*
every question is a vector of {A,B,C,D} THE ANSWER IS A CHAR A/ B/ C/ D
*/
question::question(std::string question, std::vector<std::string> _possibleAnswers, std::string CHRcorrectAnswerIndex)
{
    this->m_possibleAnswers = _possibleAnswers;
    this->m_question = question;
    this->answer = CHRcorrectAnswerIndex;
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
    int ascii = int(this->answer.c_str()) - 17;
    return this->m_possibleAnswers[ascii];
    
}


