#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <map>
#include <ArduinoJson.hpp>

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
    std::string mac;
    std::string device;
};

struct RequestData {
    RequestDataType type {};
    int intValue {};
    float floatValue {};
    bool boolValue {};
    std::string stringValue {}; 
};


class Request {
    public:
        Request();
        void setReceiver(Entity receiver);
        void setSender(Entity sender);
        void setDeviceName(std::string name);
        void setMacAddress(std::string macAddress);

        /*
            A request of type event
        */
        void asEvent(std::string eventName);

        /*
            request of type data
        */
        void asData();
        void setData(std::string name, std::string data);
        void setData(std::string name, int data);
        void setData(std::string name, bool data);
        void setData(std::string name, float data);

        std::string toString();
        
    private:
        std::string entityToString_(Entity entity);
        std::string typeToString_(RequestType type);

        
        RequestHeader header_ {};
        std::string event_ {""};
        std::map<std::string, RequestData> data_ {};

};

#endif