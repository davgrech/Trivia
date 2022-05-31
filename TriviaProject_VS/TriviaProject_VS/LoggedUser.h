#pragma once
#include <iostream>
#include <string>

class LoggedUser {

public:
	LoggedUser();
	LoggedUser(std::string name);
	std::string getUsername();

	friend bool operator == (const LoggedUser& a, const LoggedUser& b);
private:
	std::string m_username;
};