#pragma once
#include "../cpu/ISR.h"
#include <stdint.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LSHIFT 0x2A
#define RSHIFT 0x36
#define CAPSLOCK 0x3A


class Keyboard
{
private:
    /* data */
    static char key_buffer[256];
    static const char sc_ascii[];
    static const char shifted_sc_ascii[];

    static bool shift_pressed;
    
    // static char *sc_names[];

    static const int SC_MAX = 57;

    ISR *isr;
    static Display *display;

public:
    Keyboard(ISR *isr, Display *display);

    static void keyboad_handler(InterruptRegister *reg);

    void init_keyboard();

    static void execute_command(char *command);

    static void clear(char *buffer);
};

