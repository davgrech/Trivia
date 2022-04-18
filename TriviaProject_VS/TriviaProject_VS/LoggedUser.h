#include <iostream>
#include <string>

class LoggedUser {
public:
	LoggedUser(std::string name);
	std::string getUsername();

private:
	std::string m_username;
};