#include "serialportInterface.h"

SerialportInterface::SerialportInterface()
{
}

void SerialportInterface::connect()
{
    char errorStatus = serial.openDevice(SERIAL_PORT, 115200);
    if (errorStatus==1) {
        // no error
        status = SerialStatus::OPEN;
    }else {
        status = SerialStatus::FAIL;
    }
}

std::string SerialportInterface::read()
{
    std::string content {""};
    if(isReady()) {
        int readError = serial.readString(buffer, '\n', MAX_READ_BYTES, 100);
        content = std::string(buffer);
    }
    return content;
}

bool SerialportInterface::isReady()
{
    return status == SerialStatus::OPEN;
}
