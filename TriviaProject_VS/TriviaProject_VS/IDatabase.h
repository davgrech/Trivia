#pragma once
#include <iostream>
#include <string>
class IDatabase;

class IDatabase
{
public:
	virtual bool doesUserExist(std::string userName) = 0 ;
	virtual bool doesPasswordMatch(std::string v1, std::string v2) = 0;
	virtual bool addNewUser(std::string userName, std::string userPassword, std::string userEmail, std::string date, std::string address, std::string phonNumber) = 0;
	virtual void open() = 0;
	virtual void close() = 0;
private:

};