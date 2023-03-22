#include "timer.h"

Timer *Timer::timer_pointer = nullptr;


Timer::Timer(ISR *isr,uint32_t frequency) {
    this->isr = isr;
    this->frequency = frequency;
    divisor = 1193180 / frequency;
    low = (uint8_t)(divisor & 0xFF);
    high = (uint8_t)((divisor >> 8) & 0xFF);
    tick = 0;
    Timer::timer_pointer = this;

}


void Timer::init_timer() {
    // Send the command byte.
    port_byte_out(0x43, 0x36); // Command port
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
    isr->register_interrupt_handler(IRQ0, Timer::timer_handler);
}

uint32_t Timer::get_tick() {
    return tick;
}

void Timer::sleep(uint32_t ticks) {
    uint32_t eticks;
    eticks = tick + ticks;
    while(tick < eticks);
}

void Timer::sleep_ms(uint32_t ms) {
    sleep(ms * frequency / 1000);
}

void Timer::sleep_s(uint32_t s) {
    sleep(s * frequency);
}


void Timer::timer_handler(InterruptRegister *reg) {
    timer_pointer->tick++;
}