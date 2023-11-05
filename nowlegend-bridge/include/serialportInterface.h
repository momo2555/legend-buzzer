#ifndef SERIALPORT_INTERFACE_H
#define SERIALPORT_INTERFACE_H

#include <serialib.h>

#define SERIAL_PORT "/dev/ttyUSB0"

enum class SerialStatus {
    CLOSE,
    OPEN,
    FAIL,
};

class SerialportInterface {
public:
    SerialportInterface();
    void connect();
    void write();
    void read();
private:
    serialib serial;
    char buffer[2000] {};
    SerialStatus status {SerialStatus::CLOSE};
};


#endif