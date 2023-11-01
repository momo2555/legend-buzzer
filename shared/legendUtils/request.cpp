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
void Request::asIdentificationResponse(identificationResult result)
{
    requestBody_.header.type = RequestType::CONFIRM_IDENTITY;
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
    // doc["header"]["mac"] = requestBody_.header.mac;
    if (requestBody_.header.type == RequestType::DEVICE_EVENT)
    {
        doc["event"] = std::string(requestBody_.event);
    }
    else if (requestBody_.header.type == RequestType::DEVICE_DATA)
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
    }
    return typeString;
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
