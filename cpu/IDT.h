#pragma once
#include <stdint.h>

/*
Segment Selector

It is used to access code in the kernel space, 
which is the privileged part of the operating system 
that executes at a higher privilege level than user space code
*/
#define KERNEL_SELECTOR 0x08
/* Number of IDT entries in table*/
#define ENTRIES 256



class IDT {
    private:
        /* Structure of every interrupt gate*/
        struct __attribute__((packed)) Entry // Packed to ensure no padding at all
        {
            uint16_t lower_offset; // lower 16 bits of function address
            uint16_t selector; // Segment selector in the IDT
            uint8_t zero; // 8 bits of 0
            uint8_t types;
            /*
            Bits 0-3: interrupt gate type
                0b0101: 32-bit task gate
                0b0110: 16-bit interrupt gate
                0b0111: 16-bit trap gate
                0b1110: 32-bit interrupt gate

            bit 4: Specifies trap or interrupt gate
                0: interrupt gate
                1: trap gate
            
            bit 6-5: Descriptor Privilege Level
                0: most privileged (kernel level)
                3: least privileged (user level)
            
            bit 7: Present flag
                1: handler is present
                0: handler not present. 
            */
        uint16_t higher_offset; // Higher 16 bits of handler function adress
        }; 

        /* IDT actual table of entries*/
        Entry Table[ENTRIES];

        /* 
        A pointer to the array of interrupt handlers.
        Assembly instruction 'lidt' will read it 
        */
        struct __attribute__((packed)) Register {
            uint16_t limit; // size of the IDT table
            uint32_t base; // base address of the IDT table

        };

        
        /* Returns the lower 16 bits of that address*/
        uint16_t low_16(uint32_t address) {
            return (uint16_t)(address & 0xFFFF);
        }
        
        /*  Returns the upper 16 bits of the address */
        uint16_t high_16(uint32_t address) {
            return (uint16_t)(((address) >> 16) & 0xFFFF);
        }

        
        Register Reg;

        
        /* 
        A pointer to the array of interrupt handlers.
        Assembly instruction 'lidt' will read it 
        */
        struct __attribute__((packed)) Register_2 {
            uint16_t limit; // size of the IDT table
            Entry* entries; // a pointer to an Entry, which represents an individual entry in the IDT table
        };

        Register_2 *Reg_2;
    public:
        /* Sets each IDT entry */
        void set_entry(int n, uint32_t handler, uint8_t types);
        /* Loads IDT to OS using IDT address*/
        void load_idt();
        /* Sets each entry using a pointer*/
        void set_entry2(Entry* entry, uint32_t handler, uint8_t types);
        /* Load IDT using IDT pointer*/
        void load_idt2();


};