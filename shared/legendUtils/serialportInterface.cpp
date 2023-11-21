#include "serialportInterface.h"

SerialportInterface::SerialportInterface() {

}
void SerialportInterface::init() {
    Serial.begin(115200);
}  
Request SerialportInterface::readRequest() {
    int size = Serial.readBytesUntil('\n', buffer_, MAX_READ_BYTES);
    if (buffer_[0] == 'R' && size > 0) {
        Logger::log(std::string("SIZE  = " + std::string(String(size).c_str()) + " - Receive SERIAL DATA = " + std::string(buffer_)));
        Request request {std::string(buffer_).substr(1)};
        return request;
    } else {
        return Request {};
    }
    
}
void SerialportInterface::writeRequest(Request *request) {
    Serial.println("R" + String(request->toString().c_str()));
}
