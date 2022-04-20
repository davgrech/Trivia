#include "SqliteDatabase.h"
SqliteDatabase::SqliteDatabase()
{
    open();

}
SqliteDatabase::~SqliteDatabase()
{
    close();
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

bool SqliteDatabase::addNewUser(std::string userName, std::string userPassword, std::string userEmail)
{
    char* pError = NULL;
    if (!doesUserExist(userName))
    {
        std::string statement = "INSERT INTO PLAYERS (NAME, PASSWORD, EMAIL) VALUES('" + userName + "', '" + userPassword + "', '" + userEmail + "');";
        int result = sqlite3_exec(this->db, statement.c_str(), nullptr, nullptr, &pError);
        if (result) {
            std::cout << "Error was: " << pError << std::endl;
            free(pError);
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }
   
}

void SqliteDatabase::open()
{
    std::string sqlDatabaseName = "MyDb.sqlite";
    int doesFileExist = _access(sqlDatabaseName.c_str(),  0);

    int res = sqlite3_open(sqlDatabaseName.c_str(), &this->db);
    if (res != SQLITE_OK) {
        this->db = nullptr;
        std::cout << "Failed to open DB" << std::endl;
        exit(1);
    }

    if (doesFileExist == FILE_EXIST) {
        char* errMessage = nullptr;
        std::string playerStatement = "CREATE TABLE PLAYERS(NAME TEXT PRIMERY KEY NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);";
        int res = sqlite3_exec(this->db, playerStatement.c_str(), nullptr, nullptr, &errMessage);
        if (res != SQLITE_OK) {
            std::cout << errMessage << std::endl;
            close();
        }            
    }
}

void SqliteDatabase::close()
{
    if (this->db != nullptr) {
        sqlite3_close(this->db);
        db = nullptr;
    }
}


