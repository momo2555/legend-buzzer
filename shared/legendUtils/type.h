#ifndef TYPE_H
#define TYPE_H

#include <Arduino.h>
#include <iostream>
#include <array>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iomanip>

#define STR_MAC_LEN 

using BasicMacAddress = std::array<std::uint8_t, 6>;
class MacAddress {
public:
    MacAddress(std::string mac) {
        std::uint8_t i = 0, j = 0, value = 0;
        for(char s: mac) {
            if(s!=':') {
                value+=(s>='A'?(s - 'A' + 10):(s - '0'))*(1 + 15*(!i));
                i++;
                if (i==2) {
                    mac_[j] = value;
                    value = 0;
                    i = 0;
                    j++;
                }
            }
        }
    }
    MacAddress(BasicMacAddress& mac) : mac_ {mac} {}
    MacAddress(std::initializer_list<std::uint8_t> mac) : mac_ {0,0,0,0,0,0}  {
        std::size_t isize = mac.size();
        isize = isize <=6 ? isize : 6;
        std::copy_n(mac.begin(), isize, mac_.begin());
    }
    std::string toString() {
        std::string result = "";
        for(uint8_t i = 0;i<6;i++) {
            //std::cout << "debug : (" << (int)i <<"; "<< (int)mac_[i] << ")\n";
            std::string value = intToHexStr(mac_[i]);
            if(value.length()==1)value="0"+value;
            if(i<5)value = value + ":";
            result=result+value;
        }
        return result;
    }
    BasicMacAddress toArray() {
        return mac_;
    }
    
    MacAddress operator=(BasicMacAddress mac) {
        return MacAddress(mac);
    }
    MacAddress operator=(std::string mac) {
        return MacAddress(mac);
    }
    MacAddress operator=(std::initializer_list<std::uint8_t> mac) {
        return MacAddress(mac);
    }
    inline bool operator==(MacAddress& a) {
        return toArray() == a.toArray();
    }
    constexpr std::uint8_t* data() {
        return mac_.data();
    }
private:
    std::string str_toupper(std::string s)
    {
        
        std::transform(s.begin(), s.end(), s.begin(), 
            [](unsigned char c){ return std::toupper(c); } // correct
        );
        
        return s;
    }
    std::string intToHexStr(std::uint8_t value) {
        std::uint8_t dig1 = value / 16;
        std::uint8_t dig2 = value % 16;

        char tab[17] = "0123456789ABCDEF";
        char res[3] {tab[dig1], tab[dig2], '\0'};
        
        return std::string(res);
    }
    BasicMacAddress mac_ {};
};



#endif