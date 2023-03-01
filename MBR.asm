# Master Boot Record
; This is where the kernel will go to when OS starts
[BITS 16] ; Operate in 16 biy
[ORG 0x7C00] ;specifies the location in memory where the code should be loaded and executed

; Location of kernerl from start of program
; Memory address of kernel
KERNEL_OFFSET equ 0x1000

; call start
jmp start
; BIOS Entry point
start:
    mov si, welcome_message ; Load welcome message
    call print_string ; Print welcome message
    call print_newline ; Print newline

    mov [BOOT_DRIVE], dl ;Set boot drive
    ; Set the stack pointer
    mov bp, 0x9000
    mov sp, bp

    call load_kernel ; read kernel from disk
    ; Temporarily disable interrupts
    ; Set up descriptor table(GDT)
    call switch_to_32bit ; eventually calls kernel

    jmp $ ; Should never be called (error will ensure)

print_string:
    pusha ;store context
    mov ah, 0x0E ; Begin print
    .next_char:
        ; Load data in si
        lodsb ; mov al, [si]
        cmp al, 0 ; check if string end
        je .print_done ; return context if done
        int 0x10 ; call to print char
        jmp .next_char ; loop
    .print_done:
        popa ;return context
        ret ; return to print caller


print_newline:
    pusha ;store context
    mov ah, 0x0E
    mov al, 0x0A ; Newline character
    int 0x10 ; Call to print char
    mov al, 0x0D ;carriage return
    int 0x10

    popa ;return context
    ret

; Constants
welcome_message db 'This is the Project Boot Loader', 0
BOOT_DRIVE db 0