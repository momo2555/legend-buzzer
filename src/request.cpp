#include "request.h"
#include <memory>

Request::Request() {

}
void Request::setReceiver(Entity receiver) {
    header_.to = receiver;
}
void Request::setSender(Entity sender) {
    header_.from = sender;
}
void Request::setDeviceName(std::string name) {
    header_.device = name;
}
void Request::setMacAddress(std::string macAddress) {
    header_.mac = macAddress;
    
}

/*
    A request of type event
*/
void Request::asEvent(std::string eventName) {
    header_.type = RequestType::DEVICE_EVENT;
    event_ = eventName;
}

/*
    request of type data
*/
void Request::asData() {
    header_.type = RequestType::DEVICE_EVENT;
}
void Request::setData(std::string name, std::string data) {
    RequestData dataStored {};
    dataStored.type = RequestDataType::STRING;
    dataStored.stringValue = data;
    data_[name] = dataStored;
}
void Request::setData(std::string name, int data) {
    RequestData dataStored {};
    dataStored.type = RequestDataType::INT;
    dataStored.intValue = data;
    data_[name] = dataStored;
}
void Request::setData(std::string name, bool data) {
    RequestData dataStored {};
    dataStored.type = RequestDataType::BOOL;
    dataStored.boolValue = data;
    data_[name] = dataStored;
}
void Request::setData(std::string name, float data) {
    RequestData dataStored {};
    dataStored.type = RequestDataType::FLOAT;
    dataStored.floatValue = data;
    data_[name] = dataStored;
}

std::string Request::toString() {
    
    ArduinoJson::DynamicJsonDocument doc(1024);
    doc["header"]["from"] = entityToString_(header_.from);
    doc["header"]["to"] = entityToString_(header_.to);
    doc["header"]["type"] = typeToString_(header_.type);
    doc["header"]["mac"] = header_.mac;
    if(header_.type == RequestType::DEVICE_EVENT) {
        doc["event"] = event_;
        
    }else if (header_.type == RequestType::DEVICE_EVENT) {
        for (auto it = data_.begin(); it!=data_.end();it++) {
            
            switch(it->second.type) {
                case RequestDataType::INT:
                    doc["data"][it->first] = it->second.intValue;
                    break;
                case RequestDataType::STRING:
                    doc["data"][it->first] = it->second.stringValue;
                    break;
                case RequestDataType::BOOL:
                    doc["data"][it->first] = it->second.boolValue;
                    break;
                case RequestDataType::FLOAT:
                    doc["data"][it->first] = it->second.floatValue;
                    break;
                
            }
            
        }

    }
    std::string serializedData {""};
    ArduinoJson::serializeJson(doc, serializedData);
    return serializedData;
}


std::string Request::entityToString_(Entity entity) {
    std::string device {""};
    switch (entity) {
        case Entity::CONTROLLER:
            device = "controller";
            break;
        case Entity::DEVICE:
            device = "device";
            break;
        case Entity::MONITOR:
            device = "monitor";
            break;
    }
    return device;
}
std::string Request::typeToString_(RequestType type) {
    std::string typeString {""};
    switch (type) {
        case RequestType::DEVICE_DATA:
            typeString = "device_data";
            break;
        case RequestType::DEVICE_EVENT:
            typeString = "device_event";
            break;
    }
    return typeString;
}