#pragma once
#include <iostream>
#include "serve.h"
class Server
{
public:
	Server() = default;
	void run();
private:
	serveTool Communicator;

};
