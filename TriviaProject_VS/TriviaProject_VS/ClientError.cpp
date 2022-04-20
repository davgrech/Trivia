#include "ClientError.h"

const char* ClientError::what() const noexcept
{
    return "Client Disconnected";
}
