#include <iostream>
#include <string>
#include <vector>

class question
{
	public:
		int getId();
		std::string getQuestion();
		std::vector<std::string> getPossibleAnswers();
		std::string getCorrectAnswer();

	private:
		unsigned int ID;
		std::string question;
		std::vector<std::string> _possible_answers;
		std::string _correct_answer;

};