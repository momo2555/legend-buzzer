#ifndef DEVICE_MANAGEER_H
#define DEVICE_MANAGEER_H

#include "request.h"
#include "timer.h"

enum ConnectionState {
    PEERED,
    CONNECTED
};

enum AddDeviceError {
    INSERT_SUCCESS,
    ALREADY_EXIST,
    DEVICE_LIMIT_REACHED,
    MASTER_LIMIT_REACHED,
};

struct Device {
    MacAddress address {};
    ConnectionState state {};
    Entity type {};
    Timer aliveTimer {};
    
};
using DeviceList = std::vector<Device>;

class DeviceManager {
public:    
    DeviceManager();
    AddDeviceError addNewDevice(MacAddress address);
    AddDeviceError addMaster(MacAddress address);
    Device getMaster();
    Device getDevice(MacAddress address);
    DeviceList getAll();
    void updateDevice(MacAddress address, Device newDeviceValue);
    bool isDeviceExist(MacAddress address);
    bool containMaster();
    void disconnectDevice(MacAddress address);
    void reset();
private:
    void addDevice_(Device device);
    DeviceList devices_ {};
};


#endif