#pragma once
#include <iostream>
#include <string>

class LoggedUser {

public:
	LoggedUser();
	LoggedUser(std::string name);
	std::string getUsername() const;

	friend bool operator == (const LoggedUser& a, const LoggedUser& b);
	
	friend bool operator >(const LoggedUser& a, const LoggedUser& b);
	bool operator<(const LoggedUser& lhs) const;
	bool operator == (const LoggedUser& a);
private:
	std::string m_username;
};