#include "legend.h"

Legend::Legend() {
    this->client_ = std::make_unique<websockets::WebsocketsClient>();
}
void Legend::enableConfiguration() {

}
void Legend::disableConfiguration() {

}
void Legend::setDefaultPassword(std::string& password) {
    this->password_ = password;
}
void Legend::setDefaultSSID(std::string& ssid) {
    this->ssid_ = ssid;
}
void Legend::run() {

}