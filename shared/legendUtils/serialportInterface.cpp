#include "serialportInterface.h"

SerialportInterface::SerialportInterface() {

}
void SerialportInterface::init() {
    Serial.begin(115200);
}  
Request SerialportInterface::readRequest() {
    int size = Serial.readBytesUntil('\n', buffer_, MAX_READ_BYTES);
    Request request((const unsigned char *)buffer_, size);
    return request;
}
void SerialportInterface::writeRequest(Request *request) {
    Logger::log(std::string("R") + request->toString());
}
