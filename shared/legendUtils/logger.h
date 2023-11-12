#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <Arduino.h>

enum class LogLevel {
    DEBUG, 
    INFO,
    WARRNING,
    ERROR
};

class Logger {
public:
    static void log(std::string log, LogLevel level = LogLevel::DEBUG) {
        Serial.print("L ");
        Serial.print(millis());
        Serial.print(" [DEBUG] >> ");
        Serial.println(log.c_str());

    }
};

#endif