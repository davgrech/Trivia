#pragma once
#include <exception>
#include <iostream>
class ClientError : public std::exception
{
public:
    const char* what() const noexcept override;
};