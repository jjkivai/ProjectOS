#include "drivers/display.h"
#include "cpu/ISR.h"

void register_isr_handler(void (ISR::*)(InterruptRegister *reg));
// void register_irq_handler(void (*)(InterruptRegister *reg));

void (*isr_handler)(InterruptRegister *reg);
// void (*irq_handler)(InterruptRegister *reg);

void main()
{
    // Initialize Display drivers
    Display display = Display();
    display.clear_screen(); // Can be called by default
    display.print_screen("Welcome to The OS\n");

    // Initialize Interrupt Service
    ISR isr = ISR(display);
    isr.install_isr();
    register_isr_handler(&isr.__interrupt_handler);
    // register_irq_handler(&isr.__interrupt_request_handler);
    // cpu.install_isr();
    // cpu.enable_external_interrupts();

}
void register_isr_handler(void (*func)(InterruptRegister *reg)) {
    isr_handler = func;
}
// void register_irq_handler(void (*func)(InterruptRegister *reg)) {
//     irq_handler = func;
// }

extern "C" void interrupt_handler(InterruptRegister *reg) {
    isr_handler(reg);
}
// extern "C" void interrupt_request_handler(InterruptRegister *reg) {
//         irq_handler(reg);
// }
