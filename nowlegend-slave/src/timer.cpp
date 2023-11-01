#include "timer.h"

Timer::Timer() {
    stamp_ = millis();
}

void Timer::timer() {
    stamp_ = millis();
}

int Timer::getLast() {
    return stamp_;
}
bool Timer::isElapsed(int time) {
    int diff = millis() - stamp_;
    return diff  > time;
   
}
