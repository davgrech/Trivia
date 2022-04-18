#include "LoginManager.h"

void LoginManager::signup(std::string name, std::string password, std::string email)
{
	this->database->addNewUser(name, password, email);

}

void LoginManager::login(std::string name, std::string password)
{
	LoggedUser user(name);
	if (this->database->doesUserExist(name) && this->database->doesPasswordMatch(name, password)) {
		this->m_loggedUsers.push_back(user);
	}
}

void LoginManager::logout(std::string name)
{
	LoggedUser user(name);
	this->m_loggedUsers.erase(std::remove(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), 8) , this->m_loggedUsers.end());


	/*auto it = std::find(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), user);
	if (it != this->m_loggedUsers.end()){
		this->m_loggedUsers.erase(it);*/
}