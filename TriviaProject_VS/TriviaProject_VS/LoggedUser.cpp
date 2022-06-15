#include "LoggedUser.h"
LoggedUser::LoggedUser()
{
    this->m_username = "";
}
LoggedUser::LoggedUser(std::string name)
{
    this->m_username = name;
}

std::string LoggedUser::getUsername() const
{
    return this->m_username;
}

bool LoggedUser::operator<(const LoggedUser& lhs) const
{
    if (this->m_username.compare(lhs.m_username) < 0)
        return true;
    else
        return false;
}

bool LoggedUser::operator==(const LoggedUser& a)
{
    return this->m_username == a.m_username;
}

bool operator==(const LoggedUser& a, const LoggedUser& b)
{
    return a.m_username == b.m_username;
}


bool operator>(const LoggedUser& a, const LoggedUser& b)
{
    return a.m_username > a.m_username;
}
