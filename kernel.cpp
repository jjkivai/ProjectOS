#include "drivers/display.h"
#include "cpu/CPU.h"
void main()
{
    // Initialize Display drivers
    Display display = Display();
    display.clear_screen(); // Can be called by default
    display.print_screen("Welcome to Dig Bick OS\n");

    // Initialize Interrupt Service
    // CPU cpu = CPU();
    // cpu.install_isr();
    // cpu.enable_external_interrupts();

}