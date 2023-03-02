/*
HEADER FILE FOR VGA DISPLAY DRIVER USED TO DISPLAY KERNEL
*/
#pragma once
#include <stdint.h>
#ifndef DISPLAY_H
#define DISPLAY_H

#define VIDEO_ADDRESS 0xB8000 // VGA BUS ADDRESS
#define MAX_ROWS 25 // Maximum size of printable rows
#define MAX_COLS 80 // Maximum size of printable cols
#define PRINT_COLOR 0x07 // Print color (white on black)

// VGA IO PORTS
#define VGA_CONTROL 0x3D4   // VGA control port used to send commands to VGA hardware
#define VGA_DATA 0x3D5      // VGA data port used to send data to VGA hardware

class Display
{
    private:
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
            asm("out %%ax, %%dx" : : "a" (data), "d" (port));
        }
        /* Get the location of the cursor*/
        int get_cursor() 
        {
            port_byte_out(VGA_CONTROL, 14);
            int offset = port_byte_in(VGA_DATA) << 8; /* High byte: << 8 */
            port_byte_out(VGA_CONTROL, 15);
            offset += port_byte_in(VGA_DATA);
            return offset * 2;
        }
        /* Set cursor location*/
        void set_cursor(int offset) 
        {
            offset /= 2; // Divide by two, since each pos contains letter and color
            port_byte_out(VGA_CONTROL, 14);
            port_byte_out(VGA_DATA, (unsigned char) (offset >> 8));
            port_byte_out(VGA_CONTROL, 15);
            port_byte_out(VGA_DATA, (unsigned char) (offset & 0xff));
        }
        /* Print character to VGA*/
        void set_char_at_video_memory(char character, int offset)
        {
            unsigned char *video_memory = (unsigned char *)VIDEO_ADDRESS;
            video_memory[offset] = character;
            video_memory[offset + 1] = PRINT_COLOR;
        }
        /*
        The purpose of this function is to copy nbytes bytes 
        of data from the memory location pointed to by source 
        to the memory location pointed to by dest.
        */
        void memory_copy(char *source, char *dest, int nbytes)
        {
            int i;
            for (i = 0; i < nbytes; i++)
            {
                *(dest + i) = *(source + i);
            }
        }
        
        /*
        This function returns the offset of the video memory buffer 
        corresponding to a given row and column in the text mode VGA 
        buffer
        */
        int get_offset(int col, int row)
        {
            return 2 * (row * MAX_COLS + col);
        }
        /*
        Takes an offset value and returns the row number 
        corresponding to that offset in the VGA text buffer
        */
        int get_row_from_offset(int offset)
        {
            return offset / (2 * MAX_COLS);
        }
        /* If newline character, move offset up by one line*/
        int move_offset_to_new_line(int offset)
        {
            return get_offset(0, get_row_from_offset(offset) + 1);
        }

        /* Copies all the text up one line*/
        int scroll_ln(int offset)
        {
            memory_copy(
                (char *)(get_offset(0, 1) + VIDEO_ADDRESS),
                (char *)(get_offset(0, 0) + VIDEO_ADDRESS),
                MAX_COLS * (MAX_ROWS - 1) * 2);

            for (int col = 0; col < MAX_COLS; col++)
            {
                set_char_at_video_memory(' ', get_offset(col, MAX_ROWS - 1));
            }

            return offset - 2 * MAX_COLS;
        }

    public:
        void print_screen(char *string);
        void print_newline();
        void clear_screen();
        void print_backspace();
};



#endif