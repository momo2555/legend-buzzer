#ifndef SERIALPORT_INTERFACE_H
#define SERIALPORT_INTERFACE_H

#include <serialib.h>
#include <memory>

#define SERIAL_PORT "/dev/ttyUSB0"
#define MAX_READ_BYTES 2000
enum class SerialStatus {
    CLOSE,
    OPEN,
    FAIL,
};

class SerialportInterface {
public:
    using ptr = std::unique_ptr<SerialportInterface>;
    SerialportInterface();
    void connect();
    void write(std::string msg);
    std::string read();

    bool isReady();
private:
    serialib serial;
    char buffer[MAX_READ_BYTES] {};
    SerialStatus status {SerialStatus::CLOSE};
};


#endif