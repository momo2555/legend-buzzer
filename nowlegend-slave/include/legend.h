#ifndef LEGEND_H
#define LEGEND_H

#include <iostream>
#include <string>
#include <memory>

class Legend {
    public:
        Legend();
        void enableConfiguration();
        void disableConfiguration();
        void setDefaultPassword(std::string& password);
        void setDefaultSSID(std::string& ssid);
        void run();


    private:
        std::string ssid_ {""};
        std::string password_ {""};
       



};
#endif