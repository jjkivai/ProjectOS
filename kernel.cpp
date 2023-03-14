#include "drivers/display.h"
#include "cpu/ISR.h"

// class Kernel {
// public:
//     Kernel();
//     void run();
// };

// Kernel::Kernel() {
//     // Initialize Display drivers
//     Display display = Display();
//     display.clear_screen(); // Can be called by default
//     display.print_screen("Welcome to The OS\n");

//     // Initialize Interrupt Service
//     ISR isr = ISR(display);
//     isr.install_isr();
//     display.print_screen("ISR installed\n");
//     display.print_screen("Enabling interrupts...\n");
//     isr.enable_interrupts();
//     display.print_screen("Interrupts enabled\n");
// }

// void Kernel::run() {

// }


void register_handlers(ISR *isr);

ISR *isr_pointer = nullptr;

int main()
{
    // Initialize Display drivers
    Display display = Display();
    display.clear_screen(); // Can be called by default
    display.print_screen("Welcome to The OS\n");

    // Initialize Interrupt Service
    ISR isr = ISR(display);
    isr.install_isr();
    register_handlers(&isr);
    display.print_screen("ISR installed\n");
    display.print_screen("Enabling interrupts...\n");
    isr.enable_interrupts();
    display.print_screen("Interrupts enabled\n");
    /* trigger divide by 0 exception */
    __asm__ __volatile__("int $0");
    /* This causes error -> loops indefinetely*/
    int a = 5;
    int b = 0;
    int c = a / b;
    /* trigger overflow exception */
    __asm__ __volatile__("int $4");
    /* TODO: Setup keyboard*/
    /* TODO: Setup timers*/
    /* TODO: Setup dynamic memory*/

    return 0;

}
void register_handlers(ISR *isr) {
    isr_pointer = isr;
}

extern "C" void interrupt_handler(InterruptRegister *reg) {
    isr_pointer->__interrupt_handler(reg);
}
extern "C" void interrupt_request_handler(InterruptRegister *reg) {
        isr_pointer->__interrupt_request_handler(reg);
}
