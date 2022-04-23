#include "informationVerification.h"

bool isPasswordValid(std::string password)
{
    std::regex pattern(REGEX_PASSWORD);
    return std::regex_match(password, pattern);

}

bool isMailValid(std::string mail)
{
    std::regex pattern(REGEX_EMAIL);
    return std::regex_match(mail, pattern);
}

bool isAddressValid(std::string address)
{
    std::regex pattern(REGEX_ADDRESS);
    return std::regex_match(address, pattern);
}

bool isPhoneNumberValid(std::string phoneNumber)
{
    std::regex pattern(REGEX_PHONE);
    return std::regex_match(phoneNumber, pattern);
}

bool isBirthDateValid(std::string birthdate)
{
    std::regex pattern(REGEX_DATE);

    if (std::regex_match(birthdate, pattern)) {

        int day = std::stoi(birthdate.substr(0, 2));
        int month = std::stoi(birthdate.substr(3, 2));
        int year = std::stoi(birthdate.substr(6, birthdate.size()));

        std::cout << "the date is " << day << "/" << month << "/" << year << std::endl;

        return isValidDate(day, month, year);
    }

}

bool isLeap(int year)
{
    return (((year % 4 == 0) &&
        (year % 100 != 0)) ||
        (year % 400 == 0));

}

bool isValidDate(int d, int m, int y)
{
    // If year, month and day
   // are not in given range
    if (y > MAX_VALID_YR ||
        y < MIN_VALID_YR)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > 31)
        return false;

    // Handle February month
    // with leap year
    if (m == 2)
    {
        if (isLeap(y))
            return (d <= 29);
        else
            return (d <= 28);
    }

    // Months of April, June,
    // Sept and Nov must have
    // number of days less than
    // or equal to 30.
    if (m == 4 || m == 6 ||
        m == 9 || m == 11)
        return (d <= 30);

    return true;
}