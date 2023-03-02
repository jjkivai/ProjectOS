#pragma once
#include <stdint.h>
/**
 * Read a byte from the specified port
 */
unsigned char port_byte_in(uint16_t port);
/**
 * Write a byte from the specified port
 */
void port_byte_out(uint16_t port, uint8_t data);

/**
 * Read a word from the specified port
 */
unsigned short port_word_in(uint16_t port);
/**
 * Write a word from the specified port
 */
void port_word_out(uint16_t port, uint16_t data);