#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string name)
{
    this->m_username = name;
}

std::string LoggedUser::getUsername()
{
    return this->m_username;
}

bool operator==(const LoggedUser& a, const LoggedUser& b)
{
    return a.m_username == b.m_username;
}
