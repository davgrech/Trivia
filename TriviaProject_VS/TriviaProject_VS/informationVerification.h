
#include <regex>
#include <iostream>

#define MAX_VALID_YR 2030
#define MIN_VALID_YR 2022

#define REGEX_EMAIL "^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$"
#define REGEX_PASSWORD "^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,8}$"
#define REGEX_PHONE "0[0-9]{9}"
#define REGEX_ADDRESS "^[A-Za-z]+, [0-9]+, [A-Za-z]+$"
#define REGEX_DATE "^[0-9]{2}.[0-9]{2}.[0-9]{4}$"


#define ERROR_PASSWORD "Bad passowrd format: \n- 8 letters\n- at least one uppercase\n- at least one lowercase\n- at least one numberic\n- at least one special char(!,@,#,$,%,^,&,*)"
#define ERROR_EMAIL "Bad format of email: <x>@<y>.<z>"
#define ERROR_ADDRESS "Bad format of address: Street, Apt, City"
#define ERROR_PHONE "Bad format of phone: 10 numeric letters -> first letter must be 0"
#define ERROR_DATE "Bad format of date: dd.mm.yyyy"

bool isPasswordValid(std::string password);
bool isMailValid(std::string mail);
bool isAddressValid(std::string address);
bool isPhoneNumberValid(std::string phoneNumber);
bool isBirthDateValid(std::string birthdate);

bool isLeap(int year);
bool isValidDate(int d, int m, int y);