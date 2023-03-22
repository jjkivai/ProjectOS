#pragma once
#include <stdint.h>
#include <stdbool.h>
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
/* Returns the length of specific string*/
int string_length(char s[]);
/* Reverses order of string */
void reverse(char s[]);
/* Convert integer to string, and store in str*/
void int_to_string(int n, char str[]);
/* Backspace */
bool backspace(char s[]);
/* append strings*/
void append(char s[], char n);
/* Compare strings */
int compare_strings(char s1[], char s2[]);
/* Starts with*/
bool starts_with(char s1[], char s2[]);
