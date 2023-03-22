#include "drivers/display.h"
#include "cpu/ISR.h"
#include "drivers/keyboard.h"

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

    // Initialize Keyboard
    Keyboard keyboard = Keyboard(&isr, &display);
    keyboard.init_keyboard();
    display.print_screen("Keyboard initialized\n");

    // Kernel ready
    display.print_screen("Kernel ready\n");
    display.print_screen("Type 'help' for a list of commands\n");
    display.print_screen("> ");

    return 0;

}
void register_handlers(ISR *isr) {
    isr_pointer = isr;
}

extern "C" void interrupt_handler(InterruptRegister *reg) {
    isr_pointer->__interrupt_handler(reg);
    /* Increment eip*/
    reg->eip += 2;
}
extern "C" void interrupt_request_handler(InterruptRegister *reg) {
        isr_pointer->__interrupt_request_handler(reg);
}

