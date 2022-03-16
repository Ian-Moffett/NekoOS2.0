#ifndef IDT_H
#define IDT_H

#define TRAP_GATE_FLAGS 0x8F
#define INT_GATE_FLAGS 0x8E

#include <stdint.h>


/*
 *  This file will hold the IDT or 
 *  interrupt descriptor table.
 *  The CPU will look for an entry in this
 *  table when an interrupt occurs and start
 *  executing an ISR (Interrupt Service Routine).
 */


/*
 *  This is a interrupt descriptor table 
 *  entry. This is how the CPU will find 
 *  an ISR.
 *
 *  It is used by the processor to determine 
 *  the correct response to interrupts and exceptions.
 *
 *  @ isr_low: Low bits of interrupt service routine.
 *  @ cs: Code segment to load into CS before calling ISR.
 *  @ ist: The Stack Pointers used to load the stack when an entry in the IDT has an IST value other than 0.  
 *  @ attr: ISR attributes.
 *  @ dpl: Desribes to priv level.
 *  @ p: If it is being used.
 *  @ isr_middle: Middle bits of ISR.
 *  @ isr_high: High bits of ISR.
 *
 *  The packed attribute tells the compiler
 *  not to "optimize" the struct by adding
 *  padding.
 *
 */

typedef struct {
    uint16_t isr_low;
    uint16_t cs;
    uint8_t ist : 3;
    uint8_t reserved : 5;
    uint8_t attr : 4;
    uint8_t reserved1 : 1;
    uint8_t dpl : 2;
    uint8_t p : 1;
    uint16_t isr_middle;
    uint32_t isr_high;
    uint32_t reserved2;
 } __attribute__((packed)) idt_entry_t;

// This will tell the CPU where the IDT is located.
typedef struct {
    uint16_t limit;         // Limit address for IDT.
    uint64_t base;          // Base address of IDT.
} __attribute__((packed)) idtr_t;


/*
 *  The CPU will push some information on the stack
 *  before calling the interrupt, we can define that
 *  information as a struct called int_frame_t
 *  which can hold some useful information!
 *
 *  @RIP: Intruction pointer. 
 *  @CS: Code segment.
 *  @RFLAGS: Register flags. 
 *  @RSP: Points to top of the stack.
 *  @SS: Segment in which the stack is in.
 */

typedef struct {
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} __attribute__((packed)) int_frame_t;
#endif
