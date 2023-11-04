#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <serialib.h>

#include <cstdlib>

#include <iostream>
#include <map>
#include <string>
#include <sstream>


#define SERIAL_PORT "/dev/ttyUSB0"

int main() {
    //int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    serialib serial;
    char buffer[100] {};
    char errorOpening = serial.openDevice(SERIAL_PORT, 115200);
    if (errorOpening!=1) return errorOpening;
    std::cout << "Successful connection to %s\n",SERIAL_PORT;

    while(true) {
        serial.readString(buffer, '\n', 100, 2000);
        std::cout << buffer << "\n";
    }


    /*while(true) {

    }*/
    return 0; 
}