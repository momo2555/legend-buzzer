#ifndef TYPE_H
#define TYPE_H

#include <array>

#define STR_MAC_LEN 6

using MacAddress = std::array<uint8_t, STR_MAC_LEN>;

#endif