#include <iostream>
#include <vector>
#include <string>

struct ErrorResponse {
	std::string message;
} typedef ErrorResponse;

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

class JRPS {
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse value);
	static std::vector<unsigned char> serializeResponse(LoginResponse value);
	static std::vector<unsigned char> serializeResponse(SignupResponse value);
};