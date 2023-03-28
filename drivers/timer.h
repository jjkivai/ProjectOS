#pragma once

#include <stdint.h>
#include "../cpu/ISR.h"
#define MAX_TIMERS 5
class Timer {
private:
    uint32_t tick;
    uint32_t frequency;
    uint32_t divisor;
    uint8_t low;
    uint8_t high;

    ISR *isr;
public:
    Timer(ISR *isr, uint32_t frequency);
    void init_timer(int);
    uint32_t get_tick();
    void sleep(uint32_t ticks);
    void sleep_ms(uint32_t ms);
    void sleep_s(uint32_t s);

    static Timer *timer_pointer;
    static Timer *timer_pointers[MAX_TIMERS];
    static void timer_handler(InterruptRegister*, int);
};