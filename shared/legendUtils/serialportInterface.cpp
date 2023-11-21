#include "serialportInterface.h"

SerialportInterface::SerialportInterface() {

}
void SerialportInterface::init() {
    Serial.begin(115200);
}  
Request SerialportInterface::readRequest() {
    int size = Serial.readBytesUntil('\n', buffer_, MAX_READ_BYTES);
    if (buffer_[0] == 'R') {
        Request request {std::string(buffer_).substr(1)};
        return request;
    } else {
        return Request {};
    }
    
}
void SerialportInterface::writeRequest(Request *request) {
    Serial.println("R" + String(request->toString().c_str()));
}
