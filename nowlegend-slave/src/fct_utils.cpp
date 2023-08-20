#include "fct_utils.h"

std::string str_toupper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), 
                // static_cast<int(*)(int)>(std::toupper)         // wrong
                // [](int c){ return std::toupper(c); }           // wrong
                // [](char c){ return std::toupper(c); }          // wrong
                   [](unsigned char c){ return std::toupper(c); } // correct
                  );
    return s;
}

std::string intToHexStr(uint8_t value) {
    std::stringstream stream;
    stream << std::hex << value;
    return str_toupper(stream.str());
}

/**
 * Transform a String mac address to a int array
 */
void macAddressToIntArray(char addr[], uint8_t output[]) {
  //copy the str address in a temp var
  char tmp[20];
  strcpy(tmp, addr);
  int init_size = strlen(tmp);
  //the delimiter coz the mc address is like xx:xx:xx:xx:xx:xx
  char delim[] = ":";
  char *ptr = strtok(tmp, delim);
  uint8_t i = 0;
  while(ptr != NULL)
  {
    //add in the tab the converted hexa code
    int value = 0;
    if(ptr[0] >= 'A') {
      value+=(ptr[0]- 'A' + 10)*16;
    } else {
      value+=(ptr[0] - '0')*16;
    }
    if(ptr[1] >= 'A') {
      value+=(ptr[1]- 'A' + 10);
    } else {
      value+=(ptr[1] - '0');
    }
    output[i] = value;
    //next delimiter
    ptr = strtok(NULL, delim);
    i++;
  }

}
void macAddressToIntArray(std::string addr, uint8_t output[]) {
    uint8_t i = 0, j = 0, value = 0;
    for(char s: addr) {
        if(s!=':') {
            value+=(s>='A'?(s - 'A' + 10):(s - '0'))*(1 + 15*(!i));
            i++;
            if (i==2) {
                output[j]=value;
                value = 0;
                i=0;
                j++;
            }
        }
    }

}
std::string IntArrayToMacAddress(uint8_t input[]) {
    std::string result = "";
    for(uint8_t i = 0;i<6;i++) {
        std::string value = intToHexStr(input[i]);
        if(value.length()==1)value="0"+value;
        if(i<5)value = value + ":";
        result=result+value;
    }
    return result;
    
}
bool compareAddresses(uint8_t addr1[], uint8_t addr2[]) {
  bool result = true;
  for(uint8_t i = 0;i<6;i++) {
    if(addr1[i]!=addr2[i]) {
      result = false;
    }
  }
  return result;
}


