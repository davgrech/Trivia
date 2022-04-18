#include <iostream>
#include <string>
#include "IDatabase.h"
#include "LoginRequestHandler.h"
class RequestHandleFactory
{
private:
	IDatabase* m_database;

public:
	LoginRequestHandler* createLoginRequestHandler();

};