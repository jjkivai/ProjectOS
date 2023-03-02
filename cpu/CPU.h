// HEADER FILE DEFINING INTERRUPT SERVICES AND DESCRIPTORS
#pragma once
#include "IDT.h"

/* ISRs reserved for CPU exceptions */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/* Interrupt requests*/
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

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


class CPU {
    private:
        IDT Idt = IDT();
        /* It matches how 'pusha' would push data to stack */
        struct __attribute__((packed)) InterruptRegister {
            uint32_t ds; // Data segment selector
            uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
            uint32_t int_no, err_code; /* Interrupt number and error code (if applicable) */
            uint32_t eip, cs, eflags, useresp, ss; /* Pushed by the processor automatically */
        };

        typedef void (*InterruptHandler)(InterruptRegister *reg); //Defining type of interrupt handler
        /* Exception Messages defined by x86 processors*/
        char* Exception_Messages[] = {
            "DivisionByZero",
            "SingleStepInterrupt",//used for debugging
            "NonMaskableInterrupt",
            "BreakPoint",
            "Overflow",
            "OutOfBounds",
            "InvalidOpcode",
            "NoCoprocessor",
            "DoubleFault",
            "SegmentOverrun",
            "InvalidTaskStateSegment",
            "SegmentNotPresent",
            "StackSegmentError",
            "GeneralProtectionFault",
            "PageFault",
            "Reserved",
            "FloatingPointException",
            "AlignmentCheck",
            "MachineCheck",
            "Floating"

        };
    public:
        void install_isr(); // Install ISR onto OS
        void __interrupt_handler(InterruptRegister *reg); // Handle ISR
        void __interrupt_request_handler(InterruptRegister *reg);
        void register_interrupt_handler(uint8_t n, InterruptHandler handler); // Function that adds a handler to interrupt
        
        /* Functions to quickly enable or disable interrupts*/
        void enable_interrupts();
        void disable_interrupts();



};