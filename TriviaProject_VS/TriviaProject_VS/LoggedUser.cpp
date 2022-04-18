#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string name)
{
    this->m_username = name;
}

std::string LoggedUser::getUsername()
{
    return this->m_username;
}
