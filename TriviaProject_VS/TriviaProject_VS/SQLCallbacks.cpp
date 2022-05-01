#include "SQLCallbacks.h"
#include <string>
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
int getAvgTimeCallback(void* pAvgReturn, int argc, char** colData, char** colNames)
{
    float* avgTime = (float*)pAvgReturn;
    *avgTime = std::stof(colData[0]); 
    return 0;
}

int getCorrectAnswersCallback(void* pCorrectAnswersReturn, int argc, char** colData, char** colNames)
{
    int* correctAnswers = (int*)pCorrectAnswersReturn;
    *correctAnswers = std::stoi(colData[0]);
    return 0;
}
int getTotalAnswersCallback(void* pTotalAnswersReturn, int argc, char** colData, char** colName)
{
    int* totalAnswer = (int*)pTotalAnswersReturn;
    *totalAnswer = std::stoi(colData[0]);
    return 0;
}

int getTopFiveCallBack(void* pTopFive, int argc, char** colData, char** colName)
{
    std::vector<int>* myResult = (std::vector<int>*)pTopFive;
    myResult->push_back(std::stoi(colData[0]));

    return 0;
}

int getNumOfGamesCallback(void* pNumgames, int argc, char** colData, char** colName)
{
    int* numGames = (int*)pNumgames;
    *numGames = std::stoi(colData[0]);
    return 0;

}
