#include "deviceManager.h"

DeviceManager::DeviceManager()
{
}

AddDeviceError DeviceManager::addNewDevice(MacAddress address)
{
    if(!this->isDeviceExist(address)) {
        this->addDevice_({
            address,
            ConnectionState::PEERED,
            Entity::DEVICE,
            Timer()
        });
        return AddDeviceError::INSERT_SUCCESS;
    }else {
        return AddDeviceError::ALREADY_EXIST;
    }
}

AddDeviceError DeviceManager::addMaster(MacAddress address)
{
    if(!this->isDeviceExist(address)) {
        if(!this->containMaster()) {
            this->addDevice_({
                address,
                ConnectionState::PEERED,
                Entity::MASTER,
                Timer()
            });
            return AddDeviceError::INSERT_SUCCESS;
        }else {
            return AddDeviceError::MASTER_LIMIT_REACHED;
        }
    }else {
        return AddDeviceError::ALREADY_EXIST;
    }
}

Device DeviceManager::getMaster()
{
    Device master {};
    for (Device device : this->devices_) {
        if (device.type == Entity::MASTER) {
            master = device;
        }
    }
    return master;
}

Device DeviceManager::getDevice(MacAddress address)
{
    Device returnDevice {};
    for (Device device : this->devices_) {
        if (device.address == address) {
            returnDevice = device;
        }
    }
    return returnDevice;
}

DeviceList DeviceManager::getAll()
{
    return this->devices_;
}

void DeviceManager::updateDevice(MacAddress address, Device newDeviceValue)
{
    auto iter = this->devices_.begin();
    for(iter; iter < this->devices_.end();iter++) {
        if((*iter).address == address) {
            (*iter) = newDeviceValue;
        }
    } 
}

bool DeviceManager::isDeviceExist(MacAddress address)
{
    bool exist = false;
    for (Device device : this->devices_) {
        if (device.address == address) {
            exist = true;
        }
    }
    return exist;
}

bool DeviceManager::containMaster()
{
    bool containMaster = false;
    for (Device device : this->devices_) {
        if (device.type == Entity::MASTER) {
            containMaster = true;
        }
    }
    return containMaster;
}

void DeviceManager::disconnectDevice(MacAddress address)
{
    Device device = getDevice(address);
    device.state = ConnectionState::PEERED;
    updateDevice(address, device);
}

void DeviceManager::reset()
{
    // remove all devices
    this->devices_.clear();
}

void DeviceManager::addDevice_(Device device)
{
    this->devices_.push_back(device);
}
