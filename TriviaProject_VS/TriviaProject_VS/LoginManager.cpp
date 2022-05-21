#include "LoginManager.h"


LoginManager::LoginManager(IDatabase* db)
{
	this->database = db;
}

bool LoginManager::signup(std::string name, std::string password, std::string email, std::string phone, std::string address, std::string birthDate)
{
	//fix order of arguments.
	return this->database->addNewUser(name, password, email, phone, address, birthDate);
}

bool LoginManager::login(std::string name, std::string password)
{
	LoggedUser user(name);
	if (!notloggedAlready(name))
	{
		throw std::exception("Logged already in other client");
	}
	if (this->database->doesUserExist(name) && this->database->doesPasswordMatch(name, password)) {
		this->m_loggedUsers.push_back(user);
		return true;
	}
	return false;
	
}

void LoginManager::logout(std::string name)
{
	LoggedUser user(name);
	
	auto it = std::find(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), user);
	if (it != this->m_loggedUsers.end()) {
		this->m_loggedUsers.erase(it);
	}
}

bool LoginManager::signout(std::string name)
{
	logout(name);
	
	return this->database->signout(name);
}

bool LoginManager::notloggedAlready(std::string name)
{
	LoggedUser user(name);
	auto it = std::find(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), user);
	
	return it == this->m_loggedUsers.end();
}
