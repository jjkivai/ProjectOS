#include "helpers.h"
/**
 * Read a byte from the specified port
 */
unsigned char port_byte_in(uint16_t port)
{
    /* Inline assembler syntax
    * !! Notice how the source and destination registers are switched from NASM !!
    *
    * '"=a" (result)'; set '=' the C variable '(result)' to the value of register e'a'x
    * '"d" (port)': map the C variable '(port)' into e'd'x register
    *
    * Inputs and outputs are separated by colons
    */
    unsigned char result;
    __asm__("in %%dx, %%al": "=a"(result): "d"(port));
    return result;
}
/**
 * Write a byte from the specified port
 */
void port_byte_out(uint16_t port, uint8_t data)
{
    __asm__("out %%al, %%dx": : "a" (data), "d"(port));
}

/**
 * Read a word from the specified port
 */
unsigned short port_word_in(uint16_t port)
{
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}
/**
 * Write a word from the specified port
 */
void port_word_out(uint16_t port, uint16_t data)
{
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
