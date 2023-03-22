#include "ISR.h"
#include "../helpers.h"

/* Exception Messages defined by x86 processors*/






void ISR::install_isr() {
    /* Setup the ISR's*/
    Idt.set_entry(0, (uint32_t)isr0, 0x8E);
    Idt.set_entry(1, (uint32_t)isr1, 0x8E);
    Idt.set_entry(2, (uint32_t)isr2, 0x8E);
    Idt.set_entry(3, (uint32_t)isr3, 0x8E);
    Idt.set_entry(4, (uint32_t)isr4, 0x8E);
    Idt.set_entry(5, (uint32_t)isr5, 0x8E);
    Idt.set_entry(6, (uint32_t)isr6, 0x8E);
    Idt.set_entry(7, (uint32_t)isr7, 0x8E);
    Idt.set_entry(8, (uint32_t)isr8, 0x8E);
    Idt.set_entry(9, (uint32_t)isr9, 0x8E);
    Idt.set_entry(10, (uint32_t)isr10, 0x8E);
    Idt.set_entry(11, (uint32_t)isr11, 0x8E);
    Idt.set_entry(12, (uint32_t)isr12, 0x8E);
    Idt.set_entry(13, (uint32_t)isr13, 0x8E);
    Idt.set_entry(14, (uint32_t)isr14, 0x8E);
    Idt.set_entry(15, (uint32_t)isr15, 0x8E);
    Idt.set_entry(16, (uint32_t)isr16, 0x8E);
    Idt.set_entry(17, (uint32_t)isr17, 0x8E);
    Idt.set_entry(18, (uint32_t)isr18, 0x8E);
    Idt.set_entry(19, (uint32_t)isr19, 0x8E);
    Idt.set_entry(20, (uint32_t)isr20, 0x8E);
    Idt.set_entry(21, (uint32_t)isr21, 0x8E);
    Idt.set_entry(22, (uint32_t)isr22, 0x8E);
    Idt.set_entry(23, (uint32_t)isr23, 0x8E);
    Idt.set_entry(24, (uint32_t)isr24, 0x8E);
    Idt.set_entry(25, (uint32_t)isr25, 0x8E);
    Idt.set_entry(26, (uint32_t)isr26, 0x8E);
    Idt.set_entry(27, (uint32_t)isr27, 0x8E);
    Idt.set_entry(28, (uint32_t)isr28, 0x8E);
    Idt.set_entry(29, (uint32_t)isr29, 0x8E);
    Idt.set_entry(30, (uint32_t)isr30, 0x8E);
    Idt.set_entry(31, (uint32_t)isr31, 0x8E);


    // Idt.set_entry2(&Idt.Table[0], (uint32_t)isr0, 0x8E);
    // Idt.set_entry2(&Idt.Table[1], (uint32_t)isr1, 0x8E);
    // Idt.set_entry2(&Idt.Table[2], (uint32_t)isr2, 0x8E);
    // Idt.set_entry2(&Idt.Table[3], (uint32_t)isr3, 0x8E);
    // Idt.set_entry2(&Idt.Table[4], (uint32_t)isr4, 0x8E);
    // Idt.set_entry2(&Idt.Table[5], (uint32_t)isr5, 0x8E);
    // Idt.set_entry2(&Idt.Table[6], (uint32_t)isr6, 0x8E);
    // Idt.set_entry2(&Idt.Table[7], (uint32_t)isr7, 0x8E);
    // Idt.set_entry2(&Idt.Table[8], (uint32_t)isr8, 0x8E);
    // Idt.set_entry2(&Idt.Table[9], (uint32_t)isr9, 0x8E);
    // Idt.set_entry2(&Idt.Table[10], (uint32_t)isr10, 0x8E);
    // Idt.set_entry2(&Idt.Table[11], (uint32_t)isr11, 0x8E);
    // Idt.set_entry2(&Idt.Table[12], (uint32_t)isr12, 0x8E);
    // Idt.set_entry2(&Idt.Table[13], (uint32_t)isr13, 0x8E);
    // Idt.set_entry2(&Idt.Table[14], (uint32_t)isr14, 0x8E);
    // Idt.set_entry2(&Idt.Table[15], (uint32_t)isr15, 0x8E);
    // Idt.set_entry2(&Idt.Table[16], (uint32_t)isr16, 0x8E);
    // Idt.set_entry2(&Idt.Table[17], (uint32_t)isr17, 0x8E);
    // Idt.set_entry2(&Idt.Table[18], (uint32_t)isr18, 0x8E);
    // Idt.set_entry2(&Idt.Table[19], (uint32_t)isr19, 0x8E);
    // Idt.set_entry2(&Idt.Table[20], (uint32_t)isr20, 0x8E);
    // Idt.set_entry2(&Idt.Table[21], (uint32_t)isr21, 0x8E);
    // Idt.set_entry2(&Idt.Table[22], (uint32_t)isr22, 0x8E);
    // Idt.set_entry2(&Idt.Table[23], (uint32_t)isr23, 0x8E);
    // Idt.set_entry2(&Idt.Table[24], (uint32_t)isr24, 0x8E);
    // Idt.set_entry2(&Idt.Table[25], (uint32_t)isr25, 0x8E);
    // Idt.set_entry2(&Idt.Table[26], (uint32_t)isr26, 0x8E);
    // Idt.set_entry2(&Idt.Table[27], (uint32_t)isr27, 0x8E);
    // Idt.set_entry2(&Idt.Table[28], (uint32_t)isr28, 0x8E);
    // Idt.set_entry2(&Idt.Table[29], (uint32_t)isr29, 0x8E);
    // Idt.set_entry2(&Idt.Table[30], (uint32_t)isr30, 0x8E);
    // Idt.set_entry2(&Idt.Table[31], (uint32_t)isr31, 0x8E);


    /* Program the Programmable Interrupt Controller (PIC)*/
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);

    /* Setup the IRQ's*/
    Idt.set_entry(32, (uint32_t)irq0, 0x8E);
    Idt.set_entry(33, (uint32_t)irq1, 0x8E);
    Idt.set_entry(34, (uint32_t)irq2, 0x8E);
    Idt.set_entry(35, (uint32_t)irq3, 0x8E);
    Idt.set_entry(36, (uint32_t)irq4, 0x8E);
    Idt.set_entry(37, (uint32_t)irq5, 0x8E);
    Idt.set_entry(38, (uint32_t)irq6, 0x8E);
    Idt.set_entry(39, (uint32_t)irq7, 0x8E);
    Idt.set_entry(40, (uint32_t)irq8, 0x8E);
    Idt.set_entry(41, (uint32_t)irq9, 0x8E);
    Idt.set_entry(42, (uint32_t)irq10, 0x8E);
    Idt.set_entry(43, (uint32_t)irq11, 0x8E);
    Idt.set_entry(44, (uint32_t)irq12, 0x8E);
    Idt.set_entry(45, (uint32_t)irq13, 0x8E);
    Idt.set_entry(46, (uint32_t)irq14, 0x8E);
    Idt.set_entry(47, (uint32_t)irq15, 0x8E);

    // Idt.set_entry2(&Idt.Table[32], (uint32_t)irq0, 0x8E);
    // Idt.set_entry2(&Idt.Table[33], (uint32_t)irq1, 0x8E);
    // Idt.set_entry2(&Idt.Table[35], (uint32_t)irq2, 0x8E);
    // Idt.set_entry2(&Idt.Table[35], (uint32_t)irq3, 0x8E);
    // Idt.set_entry2(&Idt.Table[36], (uint32_t)irq4, 0x8E);
    // Idt.set_entry2(&Idt.Table[37], (uint32_t)irq5, 0x8E);
    // Idt.set_entry2(&Idt.Table[38], (uint32_t)irq6, 0x8E); 
    // Idt.set_entry2(&Idt.Table[39], (uint32_t)irq7, 0x8E);
    // Idt.set_entry2(&Idt.Table[40], (uint32_t)irq8, 0x8E);
    // Idt.set_entry2(&Idt.Table[41], (uint32_t)irq9, 0x8E);
    // Idt.set_entry2(&Idt.Table[42], (uint32_t)irq10, 0x8E);
    // Idt.set_entry2(&Idt.Table[43], (uint32_t)irq11, 0x8E);
    // Idt.set_entry2(&Idt.Table[44], (uint32_t)irq12, 0x8E);
    // Idt.set_entry2(&Idt.Table[45], (uint32_t)irq13, 0x8E);
    // Idt.set_entry2(&Idt.Table[46], (uint32_t)irq14, 0x8E);
    // Idt.set_entry2(&Idt.Table[47], (uint32_t)irq15, 0x8E);

    /* Load the current configuration to OS*/
    Idt.load_idt();
    // Idt.load_idt2();
}
/* handler for interrupts that are generated by the ISR */
void ISR::__interrupt_handler(InterruptRegister *reg) {

    const char* Exception_Messages[] = {
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
        "FloatingPointException",
        "VirtualizationException",
        "ControlProtectionException",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",

        "Reserved",
        "Reserved",
        "Reserved",
        "HypervisorInjectionException",
        "VMMCommunicationException"
        "SecurityException",
        "Reserved"
    };


    /* Print the interrupt number and the message*/
    disp.print_screen("Recieved interrupt: ");
    char s[3];
    int_to_string(reg->int_no, s);
    disp.print_screen(s);
    disp.print_newline();
    disp.print_screen(Exception_Messages[reg->int_no]);
    disp.print_newline();
    disp.print_newline();



}

void ISR::register_interrupt_handler(uint8_t n, InterruptHandler handler) {
    handlers[n] = handler;
}
/*
This is the implementation of the interrupt request handler for 
the ISR. When an interrupt occurs, this function is called and it 
first checks if there is a registered handler for that specific
interrupt. If there is, it retrieves the handler from the handlers 
array and calls it with the InterruptRegister structure as its argument.*/
void ISR::__interrupt_request_handler(InterruptRegister *reg) {
    /* Handle the interrupt*/
    if(handlers[reg->int_no] != 0) {
        InterruptHandler handler = handlers[reg->int_no];
        handler(reg);
    }
    /* End of Interrupt */
    // send an end of interrupt (EOI) signal to the 
    // Programmable Interrupt Controller (PIC)
    if(reg->int_no >= 40) {
        port_byte_out(0xA0, 0x20); /* follower */
    }
    port_byte_out(0x20, 0x20); /* leader */
}
/* FUnction to enable interrupts*/
void ISR::enable_interrupts() {
    __asm__ volatile("sti");
}
/* Function to disable interrupts*/
void ISR::disable_interrupts() {
    __asm__ volatile("cli");
}