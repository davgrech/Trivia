#pragma comment (lib, "ws2_32.lib")
#include <iostream>
#include <fstream>
#include "WSAInitializer.h"
#include "serve.h"

#define PORT 1025
#define IFACE 0


int main()
{
    try {
        TRACE("Starting...");
        WSAInitializer as_told_us;
        serveTool manager(PORT, IFACE);
        manager.serve();

    }
    catch (const std::exception& e) {
        std::cout << "somthing went wrong with the server" << std::endl;
    }
    
}

