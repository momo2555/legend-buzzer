#include "request.h"

Request::Request() : globalIndex_(0)
{
    // empty request
}
Request::Request(const unsigned char *rawData, int size)
{
    //requestBody_ = *( (*RequestBody<MAX_DATA_REQUEST_LENGTH>) rawData);
    memmove(&requestBody_, rawData, sizeof(requestBody_));
    globalIndex_ = requestBody_.header.dataLength;
}
void Request::setReceiver(Entity receiver, MacAddress receiverAddress)
{
    requestBody_.header.to = receiver;
    requestBody_.header.receiverAddress = receiverAddress;
}
void Request::setSender(Entity sender, MacAddress senderAddress)
{
    requestBody_.header.from = sender;
    requestBody_.header.senderAddress = senderAddress;
}
void Request::setDeviceName(const char *name)
{
    strncpy(requestBody_.header.device, name, STR_DEVICE_LEN);
    // header_.device = name;
}


// void Request::setMacAddress(std::array<uint8_t, STR_MAC_LEN> macAddress)
// {
//     requestBody_.header.mac = macAddress;
// }

/*
    A request of type event
*/
void Request::asEvent(const char *eventName)
{
    requestBody_.header.type = RequestType::DEVICE_EVENT;
    strncpy(requestBody_.event, eventName, STR_EVENT_LEN);
}

/*
    request of type data
*/
void Request::asData()
{
    requestBody_.header.type = RequestType::DEVICE_DATA;
}

void Request::asIdentification()
{
    requestBody_.header.type = RequestType::IDENTIFICATION;
}

/*
    as identification response
*/
void Request::asIdentificationResponse(IdentificationResult result)
{
    requestBody_.header.type = RequestType::CONFIRM_IDENTITY;
    setData<int>("res", static_cast<int>(result));
}

IdentificationResult Request::getIdentifactionResult()
{
    if(getType() == RequestType::CONFIRM_IDENTITY) {
        int res = std::get<int>(getDataAt(0).value); 
        return static_cast<IdentificationResult>(res);
        
    }
    return IdentificationResult::ERROR;
}

/*
    as echo request
*/
void Request::asEcho()
{
    requestBody_.header.type = RequestType::ECHO;
}

/*
    as echo response request
*/
void Request::asEchoResponse()
{
    requestBody_.header.type = RequestType::ECHO_RESPONSE;
}

void Request::asHeartbeat()
{
    requestBody_.header.type = RequestType::HEARTBEAT;
}

void Request::asHeartbeatResponse()
{
    requestBody_.header.type = RequestType::HEARTBEAT_RESPONSE;
}

std::string Request::toString()
{
    ArduinoJson::DynamicJsonDocument doc(1024);
    doc["header"]["from"] = entityToString_(requestBody_.header.from);
    doc["header"]["to"] = entityToString_(requestBody_.header.to);
    doc["header"]["type"] = typeToString_(requestBody_.header.type);
    /*doc["header"]["from_addr"] = IntArrayToMacAddress(requestBody_.header.senderAddress.data());
    doc["header"]["to_addr"] = IntArrayToMacAddress(requestBody_.header.receiverAddress.data());*/
    // doc["header"]["mac"] = requestBody_.header.mac;
    if (requestBody_.header.type == RequestType::DEVICE_EVENT)
    {
        doc["event"] = std::string(requestBody_.event);
    }
    else if (requestBody_.header.type == RequestType::DEVICE_DATA || 
             requestBody_.header.type == RequestType::CONFIRM_IDENTITY)
    {
        for (int i = 0; i < globalIndex_; i++)
        {
            switch (requestBody_.data[i].type)
            {
            case RequestDataType::INT:
                doc["data"][requestBody_.data[i].name] = std::get<int>(requestBody_.data[i].value);
                break;
            case RequestDataType::FLOAT:
                doc["data"][requestBody_.data[i].name] = std::get<float>(requestBody_.data[i].value);
                break;
            case RequestDataType::BOOL:
                doc["data"][requestBody_.data[i].name] = std::get<bool>(requestBody_.data[i].value);
                break;
            }
            // std::visit([doc, it](auto&& elem){doc["data"][it->first] = elem; }, it->second.value);
        }
    }
    std::string serializedData{""};
    ArduinoJson::serializeJson(doc, serializedData);
    return serializedData;
}

void Request::fromString(std::string jsonData)
{
    ArduinoJson::DynamicJsonDocument doc(1024);
    ArduinoJson::deserializeJson(doc, jsonData);
    requestBody_.header.from = toEntity_(doc["header"]["from"]);
    requestBody_.header.to = toEntity_(doc["header"]["to"]);
    requestBody_.header.type = toType_(doc["header"]["type"]);
    
    std::uint8_t from_addr[STR_MAC_LEN] {};
    macAddressToIntArray(doc["header"]["from_addr"].as<std::string>(), from_addr);
    std::copy(std::begin(from_addr), std::end(from_addr), requestBody_.header.senderAddress.begin());

    std::uint8_t to_addr[STR_MAC_LEN] {};
    macAddressToIntArray(doc["header"]["to_addr"].as<std::string>(), to_addr);
    std::copy(std::begin(to_addr), std::end(to_addr), requestBody_.header.receiverAddress.begin());
    
    if (requestBody_.header.type == RequestType::DEVICE_EVENT)
    {
        
        strncpy(requestBody_.event, doc["event"].as<const char *>(), STR_EVENT_LEN);
    }
    else if (requestBody_.header.type == RequestType::DEVICE_DATA || 
             requestBody_.header.type == RequestType::CONFIRM_IDENTITY)
    {

    }


}

std::string Request::entityToString_(Entity entity)
{
    std::string device{""};
    switch (entity)
    {
    case Entity::CONTROLLER:
        device = "controller";
        break;
    case Entity::DEVICE:
        device = "device";
        break;
    case Entity::MONITOR:
        device = "monitor";
        break;
    case Entity::MASTER:
        device = "master";
        break;
    default:
        device = "none";
        break;
    }
    return device;
}
std::string Request::typeToString_(RequestType type)
{
    std::string typeString{""};
    switch (type)
    {
    case RequestType::DEVICE_DATA:
        typeString = "device_data";
        break;
    case RequestType::DEVICE_EVENT:
        typeString = "device_event";
        break;
    case RequestType::IDENTIFICATION:
        typeString = "identification";
        break;
    case RequestType::CONFIRM_IDENTITY:
        typeString = "confirm_identity";
        break;
    
    }
    return typeString;
}

Entity Request::toEntity_(std::string data)
{
    Entity entity {Entity::NONE};
    if (data == "controller"){
        entity = Entity::CONTROLLER;
    }else if (data == "device"){
        entity = Entity::DEVICE;
    }else if (data == "monitor"){
        entity = Entity::MONITOR;
    }else if (data == "master"){
         entity = Entity::MASTER;
    }else if (data == "none"){
        entity = Entity::NONE;
    }
    return entity;
}

RequestType Request::toType_(std::string data)
{
    RequestType type {};
    if (data== "device_data") {
        type = RequestType::DEVICE_DATA;
    } else if (data == "device_event") {
        type = RequestType::DEVICE_EVENT;
    } else if (data == "identification") {
        type = RequestType::IDENTIFICATION;
    } else if (data == "confirm_identity") {
        type = RequestType::CONFIRM_IDENTITY;
    }
    return type;
}

RequestBody<MAX_DATA_REQUEST_LENGTH> Request::getRequestBody()
{
    return requestBody_;
}

RequestType Request::getType()
{
    return requestBody_.header.type;
}
Entity Request::getReceiverType()
{
    return requestBody_.header.to;
}
Entity Request::getSenderType()
{
    return requestBody_.header.from;
}

MacAddress Request::getReceiverAddress() {
    return requestBody_.header.receiverAddress;
}
MacAddress Request::getSenderAddress() {
    return requestBody_.header.senderAddress;
}

char *Request::getDeviceName()
{
}
RequestData Request::getDataAt(uint8_t index)
{
    RequestData requestData{};
    if (index < globalIndex_ && getType() == RequestType::DEVICE_DATA)
    {
        requestData = requestBody_.data[index];
    }
    return requestData;
}
