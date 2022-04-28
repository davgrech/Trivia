#include "SQLCallbacks.h"
int findUserCallback(void* pUser, int argc, char** colData, char** colNames)
{
    int* flag = (int*)pUser;
    *flag = 1;
    return 0;
}
int getPasswordCallback(void* pPassword, int argc, char** colData, char** colNames)
{
    std::string* password = (std::string*)pPassword;
    *password = colData[0];
    return 0;
}