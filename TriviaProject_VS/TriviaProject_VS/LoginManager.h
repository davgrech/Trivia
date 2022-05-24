#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "LoggedUser.h"
#include "IDatabase.h"
#include "SqliteDatabase.h"




class LoginManager {
public:
	LoginManager(IDatabase* db);
	bool signup(std::string name, std::string password, std::string email, std::string phone, std::string birthDate);
	bool login(std::string name, std::string password);
	void logout(std::string name);
	bool signout(std::string name);
	bool notloggedAlready(std::string name);
private:
	IDatabase* database;
	std::vector<LoggedUser> m_loggedUsers;
};