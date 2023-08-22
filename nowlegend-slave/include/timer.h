#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
    public:
        Timer();
        void timer() {};
        int getLast();
        bool isElapsed(int time);

    private:
        int stamp_ {};


};

#endif