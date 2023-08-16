#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <cstring>
#include <map>
#include <memory>
#include <ArduinoJson.hpp>

#define STR_MAC_LEN 18
#define STR_DEVICE_LEN 13
#define STR_EVENT_LEN 20

enum Entity {
    MONITOR = 0,
    CONTROLLER,
    DEVICE

};
enum RequestType {
    DEVICE_EVENT,
    DEVICE_DATA
};
enum RequestDataType {
    INT = 0,
    FLOAT,
    BOOL,
    STRING
};
struct RequestHeader {
    Entity from {};
    Entity to {};
    RequestType type {};
    char mac[STR_MAC_LEN] {"00:00:00:00:00:00"};
    char device[STR_DEVICE_LEN] {""};
};

struct RequestData {
    RequestDataType type {};
    int intValue {};
    float floatValue {};
    bool boolValue {};
    #ifdef STRING_DATA
        std::string stringValue {}; 
    #endif
};
typedef std::map<std::string, RequestData> DataList;
struct RequestBody {
    RequestHeader header {};
    char event[STR_EVENT_LEN] {""};
    DataList data {};
};


class Request {
    public:
        Request();
        void setReceiver(Entity receiver);
        void setSender(Entity sender);
        void setDeviceName(const char* name);
        void setMacAddress(const char* macAddress);

        /*
            A request of type event
        */
        void asEvent(const char* eventName);

        /*
            request of type data
        */
        void asData();
        void setData(std::string name, std::string data);
        void setData(std::string name, int data);
        void setData(std::string name, bool data);
        void setData(std::string name, float data);

        std::string toString();

        RequestBody getRequestBody();
        
    private:
        std::string entityToString_(Entity entity);
        std::string typeToString_(RequestType type);

        
        RequestBody requestBody_ {};

};

#endif