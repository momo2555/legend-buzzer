#ifndef LEGEND_H
#define LEGEND_H

#include <iostream>
#include <string>

class Legend {
    public:
        Legend();
        void enableConfiguration();
        void disableConfiguration();
        void setDefaultPassword(std::string& password);
        void setDefaultSSID(std::string& ssid);


    private:
        std::string ssid {""};
        std::string password {""};


};
#endif