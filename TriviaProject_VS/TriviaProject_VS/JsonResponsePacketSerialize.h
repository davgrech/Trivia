#include <iostream>
#include "Response.h"


class JRPS {
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse value);
	static std::vector<unsigned char> serializeResponse(LoginResponse value);
	static std::vector<unsigned char> serializeResponse(SignupResponse value);
};