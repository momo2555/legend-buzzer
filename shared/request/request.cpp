#include "request.h"

Request::Request() {

}
void Request::setReceiver(Entity receiver) {
    requestBody_.header.to = receiver;
}
void Request::setSender(Entity sender) {
    requestBody_.header.from = sender;
}
void Request::setDeviceName(const char* name) {
    strncpy(requestBody_.header.device, name, STR_DEVICE_LEN);
    //header_.device = name;
}
void Request::setMacAddress(std::array<uint8_t, STR_MAC_LEN> macAddress) {
    requestBody_.header.mac = macAddress;
}

/*
    A request of type event
*/
void Request::asEvent(const char* eventName) {
    requestBody_.header.type = RequestType::DEVICE_EVENT;
    strncpy(requestBody_.event, eventName, STR_EVENT_LEN);
    
}

/*
    request of type data
*/
void Request::asData() {
    requestBody_.header.type = RequestType::DEVICE_DATA;
}



std::string Request::toString() {
    
    ArduinoJson::DynamicJsonDocument doc(1024);
    doc["header"]["from"] = entityToString_(requestBody_.header.from);
    doc["header"]["to"] = entityToString_(requestBody_.header.to);
    doc["header"]["type"] = typeToString_(requestBody_.header.type);
    //doc["header"]["mac"] = requestBody_.header.mac;
    if(requestBody_.header.type == RequestType::DEVICE_EVENT) {
        doc["event"] = std::string(requestBody_.event);
        
    }else if (requestBody_.header.type == RequestType::DEVICE_DATA) {
        for (auto it = requestBody_.data.begin(); it!=requestBody_.data.end();it++) {
            switch (it->second.type) {
                case RequestDataType::INT:
                doc["data"][it->first] = std::get<int>(it->second.value);
                    break;
                case RequestDataType::FLOAT:
                doc["data"][it->first] = std::get<float>(it->second.value);
                    break;
                case RequestDataType::BOOL:
                doc["data"][it->first] = std::get<bool>(it->second.value);
                    break;
                
            }
            
            //std::visit([doc, it](auto&& elem){doc["data"][it->first] = elem; }, it->second.value);
            
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

RequestBody Request::getRequestBody() {
    return requestBody_;
}