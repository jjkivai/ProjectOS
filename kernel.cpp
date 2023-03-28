#include "drivers/display.h"
#include "cpu/ISR.h"
#include "drivers/keyboard.h"
#include "drivers/timer.h"
#include "memory/memory.h"

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
    ISR isr(display);
    isr.install_isr();
    register_handlers(&isr);
    display.print_screen("ISR installed\n");
    display.print_screen("Enabling interrupts...\n");
    isr.enable_interrupts();
    display.print_screen("Interrupts enabled\n");

    // Initialize Keyboard
    Keyboard keyboard(&isr, &display);
    keyboard.init_keyboard();
    display.print_screen("Keyboard initialized\n");

    int a = 0;
    int b = 5;
    int c = b/a;

    // // Test timer
    // Timer timer1(&isr, 1000);

    // timer1.init_timer();
    // // timer2.init_timer();

    // // Wait for some time to ensure that the timers have started counting
    // timer1.sleep_s(1);


    // uint32_t t1_start = timer1.get_tick();

    // timer1.sleep_s(5);
    // uint32_t t1_end = timer1.get_tick();

    // display.print_screen("Timer 1 ticks: ");
    // display.print_screen(t1_end - t1_start);
    // display.print_screen("\n");

    // Initialize Memory
    memory::init_memory();
    display.print_screen("Memory initialized\n");
    memory::print_memory(display);

    int *ptr = (int*)memory::malloc(4);
    int *ptr2 = (int*)memory::malloc(4);

    *ptr = 10;
    *ptr2 = 6945;

    display.print_screen("ptr: ");
    display.print_screen(*ptr);
    display.print_screen("\n");

    memory::free(ptr2);


    memory::print_dynamic_memory(display);





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

