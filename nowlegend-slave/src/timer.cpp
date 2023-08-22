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
        return millis() - stamp_  > time;
   
}