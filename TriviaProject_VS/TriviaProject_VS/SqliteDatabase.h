#pragma once
#include <iostream>
#include <string>
#include "IDatabase.h"
#include "sqlite3.h"
#include <io.h>

#define FILE_EXIST -1

int findUserCallback(void* pUser, int argc, char** colData, char** colNames);
int getPasswordCallback(void* pPassword, int argc, char** colData, char** colNames);

class SqliteDatabase : public IDatabase 
{
public:
	SqliteDatabase();
	~SqliteDatabase();
	bool doesUserExist(std::string userName);
	bool doesPasswordMatch(std::string userName, std::string userPassword);
	bool addNewUser(std::string userName, std::string userPassword, std::string userEmail);
	void open();
	void close();
private:
	sqlite3* db;
	
};