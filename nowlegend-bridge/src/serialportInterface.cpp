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
