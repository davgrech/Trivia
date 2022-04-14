#include <iostream>
#include <string>
#include "IDatabase.h"
class SqliteDatabase : public IDatabase 
{
public:
	bool doesUserExist(std::string userName);
	bool doesPasswordMatch(std::string userName, std::string userPassword);
	bool addNewUser(std::string userName, std::string userPassword, std::string userEmail);
private:

};