#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <cstring>
#include <map>
#include <variant>
#include <array>
#include <memory>
#include <ArduinoJson.hpp>

#define STR_MAC_LEN 6
#define STR_DEVICE_LEN 13
#define STR_EVENT_LEN 20
#define STR_REQ_DATA_NAME_LEN 7
#define MAX_DATA_REQUEST_LENGTH 12

typedef std::array<uint8_t, STR_MAC_LEN> MacAddress;

enum Entity : std::uint8_t
{
    MONITOR = 0,
    CONTROLLER,
    DEVICE

};
enum identificationResult : uint8_t
{
    ACCEPTED = 0,
    REFUSED
};
enum RequestType : std::uint8_t
{
    DEVICE_EVENT = 0, // send an event
    DEVICE_DATA,      // Send data
    ECHO,             // send an echo to the master
    ECHO_RESPONSE,    // the master respond with a echo
    IDENTIFICATION,   // send an isentification
    CONFIRM_IDENTITY, // confirm the identification
    ALIVE,            // Say to master that the device is alive to not trigger the watchdog
};
enum RequestDataType : std::uint8_t
{
    INT = 0,
    FLOAT,
    BOOL,
    STRING
};
struct RequestHeader
{
    RequestType type{};
    uint8_t dataLength{0};
    Entity from{};
    Entity to{};
    std::array<uint8_t, STR_MAC_LEN> mac{};
    char device[STR_DEVICE_LEN]{""};
};

struct RequestData
{
    RequestDataType type{};
    char name[STR_REQ_DATA_NAME_LEN]{""};
    std::variant<int, float, bool> value;
};

typedef std::map<std::string, RequestData> DataList;

template <std::size_t t>
struct RequestBody
{
    // typedef t dataMaxSize;
    RequestHeader header{};
    char event[STR_EVENT_LEN]{""};
    // DataList data {};
    std::array<RequestData, t> data{};
};

class Request
{
public:
    Request();
    Request(const unsigned char *rawData, int size);
    ~Request(){};
    void setReceiver(Entity receiver);
    void setSender(Entity sender);
    void setDeviceName(const char *name);
    void setMacAddress(std::array<uint8_t, STR_MAC_LEN> macAddress);

    /*
        A request of type event
    */
    void asEvent(const char *eventName);

    /*
        request of type data
    */
    void asData();
    template <typename T>
    void setData(std::string name, T data)
    {
        if (globalIndex_ < MAX_DATA_REQUEST_LENGTH)
        {
            RequestData dataStored{};
            dataStored.type = getDataType(data);
            strncpy(dataStored.name, name.c_str(), STR_REQ_DATA_NAME_LEN);
            dataStored.value = data;
            requestBody_.data[globalIndex_] = dataStored;
            globalIndex_++;
            requestBody_.header.dataLength = globalIndex_;
        }
    }

    /*
        as identification
    */
    void asIdentification();

    /*
        as identification request
    */
    void asIdentificationResponse(identificationResult result);

    /*
        as echo request
    */
    void asEcho();

    /*
        as echo response request
    */
    void asEchoResponse();

    std::string toString();

    RequestBody<MAX_DATA_REQUEST_LENGTH> getRequestBody();

    RequestDataType getDataType(int data) { return RequestDataType::INT; }
    RequestDataType getDataType(float data) { return RequestDataType::FLOAT; }
    RequestDataType getDataType(bool data) { return RequestDataType::BOOL; }

    RequestType getType();
    Entity getReceiver();
    Entity getSender();
    char *getDeviceName();
    RequestData getDataAt(uint8_t index);

private:
    std::string entityToString_(Entity entity);
    std::string typeToString_(RequestType type);

    uint8_t globalIndex_{};
    RequestBody<MAX_DATA_REQUEST_LENGTH> requestBody_{};
};

#endif