#ifndef SERIALPORT_INTERFACE_H
#define SERIALPORT_INTERFACE_H

#include "request.h"
#include <Arduino.h>

#define MAX_READ_BYTES 2000
class SerialportInterface {
    public:
        SerialportInterface();
        void init();
        Request readRequest();
        void writeRequest(Request request);
    private:
        char buffer[2000] {};

}

#endif