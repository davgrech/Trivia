#pragma once
#include <iostream>
#include <vector>
#include "question.h"
int findUserCallback(void* pUser, int argc, char** colData, char** colNames);
int getPasswordCallback(void* pPassword, int argc, char** colData, char** colNames);
int getAvgTimeCallback(void* pAvgReturn, int argc, char** colData, char** colNames);
int getCorrectAnswersCallback(void* pCorrectAnswersReturn, int argc, char** colData, char** colNames);
int getNumOfGamesCallback(void* pNumgames, int argc, char** colData, char** colName);
int getTotalAnswersCallback(void* pTotalAnswersReturn, int argc, char** colData, char** colName);
int getPointsCallBack(void* pTopFive, int argc, char** colData, char** colName);
int getQuestionsCallBack(void* pQuestions, int argc, char** colData, char** colName);