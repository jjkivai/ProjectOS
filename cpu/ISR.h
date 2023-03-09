// HEADER FILE DEFINING INTERRUPT SERVICES AND DESCRIPTORS
#pragma once
#include "IDT.h"
#include "../drivers/display.h"

/* ISRs reserved for ISR exceptions */
extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

/* Interrupt requests*/
extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();


/* Interrupt requests for hardware exceptions*/
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47
/* Exception Messages defined by x86 processors*/
extern const char* Exception_Messages[];

struct __attribute__((packed)) InterruptRegister {
    uint32_t ds; // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
    uint32_t int_no, err_code; /* Interrupt number and error code (if applicable) */
    uint32_t eip, cs, eflags, useresp, ss; /* Pushed by the processor automatically */
};
extern "C" void interrupt_handler(InterruptRegister *reg);
extern "C" void interrupt_request_handler(InterruptRegister *reg);

class ISR {
    private:
        IDT Idt;
        Display &disp;
        /* It matches how 'pusha' would push data to stack */

        typedef void (*InterruptHandler)(InterruptRegister *reg); //Defining type of interrupt handler
        
        InterruptHandler handlers[ENTRIES];

    public:
        ISR(Display& display) : disp(display) {
            Idt = IDT();
        }
        void install_isr(); // Install ISR onto OS
        void __interrupt_handler(InterruptRegister *reg); // Handle ISR
        void __interrupt_request_handler(InterruptRegister *reg); // Handle IRQ
        void register_interrupt_handler(uint8_t n, InterruptHandler handler); // Function that adds a handler to interrupt
        
        /* Functions to quickly enable or disable interrupts*/
        void enable_interrupts();
        void disable_interrupts();
        

};