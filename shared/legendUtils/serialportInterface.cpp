#include "serialportInterface.h"

SerialportInterface::SerialportInterface() {

}
void SerialportInterface::init() {
    Serial.begin(115200);
}  
Request SerialportInterface::readRequest() {
    int size = Serial.readBytesUntil("\n", buffer, MAX_READ_BYTES);
    Request request(buffer, size);
}
void SerialportInterface::writeRequest(Request request) {
    Serial.prinln("R" + request.toString().c_str());
}
