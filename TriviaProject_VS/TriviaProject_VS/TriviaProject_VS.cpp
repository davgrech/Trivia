#pragma comment (lib, "ws2_32.lib")
#include <iostream>
#include <fstream>
#include "WSAInitializer.h"

#include "SERVER.h"



int main()
{
    try {
        TRACE("Starting...");
        WSAInitializer as_told_us;
        Server manager;
        manager.run();

    }
    catch (const std::exception& e) {
        std::cout << "somthing went wrong with the server" << std::endl;
    }
    
}

