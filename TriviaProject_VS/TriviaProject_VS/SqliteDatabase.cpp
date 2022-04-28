#include "SqliteDatabase.h"

SqliteDatabase::SqliteDatabase()
{
    open();

}


bool SqliteDatabase::doesUserExist(std::string userName)
{
    std::string statement = "SELECT * FROM PLAYERS WHERE NAME = '" + userName + "';";
    char* pError = NULL;
    int foundUser = 0;

    int result = sqlite3_exec(this->db, statement.c_str(), findUserCallback, &foundUser, &pError);
    if (result) {
        std::cout << "Error was: " << pError << std::endl;
        free(pError);
    }

    return foundUser;
}


bool SqliteDatabase::doesPasswordMatch(std::string userName, std::string userPassword)
{
    std::string realPassword;
    std::string statement = "SELECT PASSWORD FROM PLAYERS WHERE NAME = '" + userName + "';";
    char* pError = NULL;
    int result = sqlite3_exec(this->db, statement.c_str(), getPasswordCallback, &realPassword, &pError);

    return realPassword.compare(userPassword) == 0;

}


bool SqliteDatabase::addNewUser(std::string userName, std::string userPassword, std::string userEmail, std::string phonNumber, std::string address, std::string date)
{

    char* pError = NULL;
    if (!doesUserExist(userName))
    {

        if (!isPasswordValid(userPassword)) {
            throw(std::exception(ERROR_PASSWORD));
        }
        if (!isMailValid(userEmail)) {
            throw(std::exception(ERROR_EMAIL));
        }
        if (!isAddressValid(address)) {
            throw(std::exception(ERROR_ADDRESS));
        }
        if (!isBirthDateValid(date)) {
            throw(std::exception(ERROR_DATE));
        }
        
        if (!isPhoneNumberValid(phonNumber)) {
            throw(std::exception(ERROR_PHONE));
        }
       

        std::string statement = "INSERT INTO PLAYERS (NAME, PASSWORD, EMAIL, DATE, PHONE, ADDRESS) VALUES('" + userName + "', '" + userPassword + "', '" + userEmail + "', '" + date + "', '" + phonNumber + "', '" + address + "'); ";


        return createTableOrInsert(statement);
       
      
    }
    else
    {
        return false;
    }

}

float SqliteDatabase::getPlayersAverageAnswerTime(std::string user)
{
    return 0.0f;
}

int SqliteDatabase::getNumOfCorrectAnswers(std::string user)
{
    return 0;
}

int SqliteDatabase::getNumOfTotalAnswers(std::string user)
{
    return 0;
}

int SqliteDatabase::getNumOfPlayerGames(std::string user)
{
    return 0;
}


bool SqliteDatabase::createTableOrInsert(std::string statement)
{
    char* errMessage = nullptr;

    int res = sqlite3_exec(this->db, statement.c_str(), nullptr, nullptr, &errMessage);


    if (res != SQLITE_OK) {
        std::cout << errMessage << std::endl;
        close();
        return false;
    }
    return true;
}


void SqliteDatabase::open()
{
    std::string sqlDatabaseName = "MyDb.sqlite";
    int doesFileNotExist = _access(sqlDatabaseName.c_str(), 0);

    int res = sqlite3_open(sqlDatabaseName.c_str(), &this->db);

    if (res != SQLITE_OK) {
        this->db = nullptr;
        std::cout << "Failed to open DB" << std::endl;
        exit(1);
    }

    if (doesFileNotExist == FILE_NOT_EXIST) {
       
        std::string playerTableStatement = "CREATE TABLE PLAYERS(NAME TEXT PRIMERY KEY NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL, DATE TEXT NOT NULL, PHONE TEXT NOT NULL, ADDRESS NOT NULL);";
        createTableOrInsert(playerTableStatement);

        std::string questionsTableStatement = "CREATE TABLE QUESTIONS(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, QUESTION TEXT NOT NULL, A TEXT NOT NULL, B TEXT NOT NULL, C TEXT NOT NULL, D TEXT NOT NULL, ANSWER TEXT NOT NULL);";
        createTableOrInsert(questionsTableStatement);


        createTableOrInsert(Q1);
        createTableOrInsert(Q2);
        createTableOrInsert(Q3);
        createTableOrInsert(Q4);
        createTableOrInsert(Q5);
        createTableOrInsert(Q6);
        createTableOrInsert(Q7);
        createTableOrInsert(Q8);
        createTableOrInsert(Q9);
        createTableOrInsert(Q10);


    }   
}


void SqliteDatabase::close()
{
    if (this->db != nullptr) {
        sqlite3_close(this->db);
        db = nullptr;
    }
}


