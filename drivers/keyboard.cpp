#include "keyboard.h"
#include "../cpu/ISR.h"
#include "../helpers.h"


char Keyboard::key_buffer[256];
const char Keyboard::sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6','7', '8', '9', '0', '-', '=', '\b', 
                                   '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '?',
                                   '?', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', '?', 
                                   '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};

const char Keyboard::shifted_sc_ascii[] = {'?', '?', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', 
                                   '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '?',
                                   '?', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', '?', 
                                   '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', '?', '?', '?', ' '};

bool Keyboard::shift_pressed = false;

// char *Keyboard::sc_names[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
//                          "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
//                          "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
//                          "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
//                          "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
//                          "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

Display *Keyboard::display = nullptr;

Keyboard::Keyboard(ISR *isr, Display *display)
{
    this->isr = isr;
    this->display = display;
}


void Keyboard::init_keyboard() {
    isr->register_interrupt_handler(IRQ1, Keyboard::keyboad_handler);
}

void Keyboard::keyboad_handler(InterruptRegister *reg) {
    uint8_t scancode = port_byte_in(0x60); // Read from the keyboard's data buffer
    if (scancode > SC_MAX) {
        if(scancode == (LSHIFT | 0x80) || scancode == (RSHIFT | 0x80)) {
            shift_pressed = false;
        }
        return;
    }
    if (scancode == BACKSPACE) {
        if(backspace(key_buffer)) {
            display->print_backspace();
        }
    } else if (scancode == ENTER) {
        display->print_newline();
        /* execute command */
        execute_command(key_buffer);
        clear(key_buffer);
    } else if (scancode == LSHIFT || scancode == RSHIFT) {
        shift_pressed = true;
    }
    
    else {
        char letter;
        if (shift_pressed) {
            letter = shifted_sc_ascii[(int)scancode];
        } else {
            letter = sc_ascii[(int)scancode];
        }
        char s[2] = {letter, '\0'};
        display->print_screen(s);
        append(key_buffer, letter);
    }

}

void Keyboard::execute_command(char *command) {
    // if (compare_strings(command, "clear") == 0) {
    //     display->print_screen("K");
    // } else if (compare_strings(command, "help") == 0) {
    //     display->print_screen("Available commands: clear, help, echo, shutdown");
    // } else if (compare_strings(command, "echo") == 0) {
    //     display->print_screen("echo: echo [string] - prints the string");
    // } else if (compare_strings(command, "shutdown") == 0) {
    //     display->print_screen("shutdown: shutdown - shuts down the computer");
    // } else if (compare_strings(command, "echo ", 5) == 0) {
    //     display->print_screen(command + 5);
    // } else if (compare_strings(command, "shutdown") == 0) {
    //     display->print_screen("Shutting down...");
    //     asm volatile("hlt");
    // } else {
    //     display->print_screen("Command not found");
    // }
    if(string_length(command) > 0) {

        if(compare_strings(command, "clear") == 0) {
            display->clear_screen();
        }
        else if(compare_strings(command,"help") == 0) {
            display->print_screen("Available commands: clear, help, echo, shutdown\n");
        }
        else if(starts_with(command, "echo") == 1) {
            if(string_length(command) > 5) {
                display->print_screen(command + 5);
                display->print_screen("\n");
            }
            else{
                display->print_screen("usage: echo [string] - prints the string\n");
            }

        }
        else {
            display->print_screen("Command not found\n");
        }
    }

    display->print_screen("> ");
}

void Keyboard::clear(char *buffer) {
        for(int i = 0; i < 256; i++) {
            buffer[i] = '\0';
        }
}
