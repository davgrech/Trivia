#include <iostream>
#include <string>
#include <vector>
#include "LoggedUser.h"
#include "IDatabase.h"
#include "SqliteDatabase.h"


#include <algorithm>
class LoginManager {
public:
	void signup(std::string name, std::string password, std::string email);
	void login(std::string name, std::string password);
	void logout(std::string name);
private:
	IDatabase* database;
	std::vector<LoggedUser> m_loggedUsers;
};