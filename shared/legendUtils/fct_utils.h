#ifndef FCT_UTILS_H
#define FCT_UTILS_H 


#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include "type.h"


std::string str_toupper(std::string s);

std::string intToHexStr(uint8_t value);

/**
 * Transform a String mac address to a int array
 */
void macAddressToIntArray(char addr[], uint8_t output[]);


void macAddressToIntArray(std::string addr, uint8_t output[]);
std::string IntArrayToMacAddress(uint8_t input[]);
bool compareAddresses(uint8_t addr1[], uint8_t addr2[]);

#endif