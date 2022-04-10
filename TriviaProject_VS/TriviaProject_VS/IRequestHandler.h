#pragma once
#include <iostream>
#include <ctime>
#include <vector>


struct RequestInfo {
	int id;
	time_t recevialTime;
	std::vector<unsigned char> buffer;
}typedef RequestInfo;

struct RequestResult {
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler;
}typedef RequestResult;

class IRequestHandler 
{
public:
	virtual bool isRequestRelevant() = 0;
	virtual RequestResult handleRequest(RequestInfo value) = 0;

};