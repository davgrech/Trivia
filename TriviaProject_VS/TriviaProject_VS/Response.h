#include <iostream>
#include <vector>
#include <string>
#include <nlohmann/json_fwd.hpp>

using nlohmann::json;

struct ErrorResponse {
	std::string message;
} typedef ErrorResponse;

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

//Json requestPacketserialize
//Json responsePacketserialize
