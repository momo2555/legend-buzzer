#ifndef SERIALPORT_INTERFACE_H
#define SERIALPORT_INTERFACE_H

#include "request.h"
#include <Arduino.h>
#include "logger.h"

#define MAX_READ_BYTES 2000
class SerialportInterface {
    public:
    using ptr = std::shared_ptr<SerialportInterface>;
        SerialportInterface();
        void init();
        Request readRequest();
        void writeRequest(Request *request);
    private:
        char buffer_[MAX_READ_BYTES] {};
        


};

#endif