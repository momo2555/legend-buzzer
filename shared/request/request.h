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
#define MAX_DATA_REQUEST_LENGTH 15

typedef std::array<uint8_t, STR_MAC_LEN> MacAddress;

enum Entity : std::uint8_t {
    MONITOR = 0,
    CONTROLLER,
    DEVICE

};
enum RequestType : std::uint8_t {
    DEVICE_EVENT = 0,     //send an event
    DEVICE_DATA,          //Send data
    ECHO,                 //send an echo to the master
    ECHO_RESPONSE,        //the master respond with a echo
    IDENTIFICATION,       //send an isentification
    CONFIRM_IDENTITY,     //confirm the identification
    ALIVE,                //Say to master that the device is alive to not trigger the watchdog
};
enum RequestDataType : std::uint8_t {
    INT = 0,
    FLOAT,
    BOOL,
    STRING
};
struct RequestHeader {
    RequestType type {};
    Entity from {};
    Entity to {};
    std::array<uint8_t, STR_MAC_LEN> mac {};
    char device[STR_DEVICE_LEN] {""};
};

struct RequestData {
    RequestDataType type {};
    std::variant<int, float, bool> value;
};

typedef std::map<std::string, RequestData> DataList;

//template <std::size_t t>
struct RequestBody {
    //typedef t dataMaxSize;
    RequestHeader header {};
    char event[STR_EVENT_LEN] {""};
    DataList data {};
    //std::array<RequestData, dataMaxSize> data_ {};
};


class Request {
    public:
        Request();
        ~Request() {};
        void setReceiver(Entity receiver);
        void setSender(Entity sender);
        void setDeviceName(const char* name);
        void setMacAddress(std::array<uint8_t, STR_MAC_LEN> macAddress);

        /*
            A request of type event
        */
        void asEvent(const char* eventName);

        /*
            request of type data
        */
        void asData();

        template <typename T>
        void setData(std::string name, T data) {
            RequestData dataStored {};
            dataStored.type = getDataType(data);
            dataStored.value = data;
            requestBody_.data[name] = dataStored;
        }
       

        std::string toString();

        RequestBody getRequestBody();

        RequestDataType getDataType(int data) {return RequestDataType::INT;}
        RequestDataType getDataType(float data) {return RequestDataType::FLOAT;}
        RequestDataType getDataType(bool data) {return RequestDataType::BOOL;}
        
    private:
        std::string entityToString_(Entity entity);
        std::string typeToString_(RequestType type);

        
        RequestBody requestBody_ {};
    
};

#endif