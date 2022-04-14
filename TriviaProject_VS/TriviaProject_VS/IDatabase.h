#include <iostream>
#include <string>
class IDatabase
{
public:
	bool doesUserExist(std::string userName);
	bool doesPasswordMatch(std::string v1, std::string v2);
	bool addNewUser(std::string userName, std::string userPassword, std::string userEmail);

private:

};