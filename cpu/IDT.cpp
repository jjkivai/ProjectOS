#include "IDT.h"
/* Sets each IDT entry */
void IDT::set_entry(int n, uint32_t handler, uint8_t types)
{
    Table[n].lower_offset = low_16(handler);
    Table[n].selector = KERNEL_SELECTOR;
    Table[n].zero = 0;
    /*
    Can be 0x8E
    Bit 7 (Present) is set to 1, indicating that the IDT entry is present.
    Bits 6-5 (Privilege level) are set to 0b00, indicating that the interrupt gate can be accessed from kernel mode only.
    Bit 4 (Descriptor type) is set to 0, indicating that this is an interrupt gate.
    Bits 3-0 (Gate type) are set to 0b1110, indicating that this is a 32-bit interrupt gate.*/
    Table[n].types = types; 
    Table[n].higher_offset = high_16(handler);
}
/* Load Pointer to absolute address of IDT*/
void IDT::load_idt()
{
    Reg.base = (uint32_t) &Table;
    Reg.limit = ENTRIES * sizeof(Entry) - 1;
    /* Don't make the mistake of loading &idt -- always load &reg */
    __asm__ volatile("lidt (%0)" : : "r" (&Reg));
}
/* Set IDT entry using pointers instead*/
void IDT::set_entry2(Entry* entry, uint32_t handler, uint8_t types) 
{
    entry->higher_offset = low_16(handler);
    entry->selector = KERNEL_SELECTOR; // For now since it's all kernel
    entry->zero = 0;
    entry->types = types;
    entry->higher_offset = high_16(handler);
}
/* Load IDT using pointer opposed to address*/
void IDT::load_idt2() 
{
    Reg_2->limit = ENTRIES * sizeof(Entry) - 1;
    Reg_2->entries = Table;
    __asm__ volatile("lidt %0" : : "m"(*Reg_2));
}