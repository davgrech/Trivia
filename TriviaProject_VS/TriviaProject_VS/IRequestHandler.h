#pragma once
#include <iostream>
#include <ctime>
#include <vector>

class IRequestHandler;

struct RequestResult {

	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler;

}typedef RequestResult;


struct RequestInfo {
	int id;
	char* recevialTime;
	std::vector<unsigned char> buffer;
}typedef RequestInfo;



class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo request) = 0;
	virtual RequestResult handleRequest(RequestInfo value) = 0;

};




