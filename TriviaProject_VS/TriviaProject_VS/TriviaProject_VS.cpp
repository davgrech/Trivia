#pragma comment (lib, "ws2_32.lib")
#include <iostream>
#include <fstream>
#include "WSAInitializer.h"
#include "serve.h"

int main()
{
    try {
        TRACE("Starting...");
        

    }
    catch (const std::exception& e) {
        std::cout << "somthing went wrong with the server" << std::endl;
    }
    
}

