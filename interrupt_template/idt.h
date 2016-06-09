/* Defines an IDT entry */
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        /* Our kernel segment goes here! */
    unsigned char always0;     /* This will ALWAYS be set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
struct idt_entry idt[256];
struct idt_ptr idtp;

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

/* This exists in 'start.asm', and is used to load our IDT */
extern void idt_load();

/* Use this function to set an entry in the IDT. */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
   idt[num].base_lo = base & 0xFFFF;
   idt[num].base_hi = (base >> 16) & 0xFFFF;

   idt[num].sel     = sel;
   idt[num].always0 = 0;
   // We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   idt[num].flags   = flags /* | 0x60 */;
}

