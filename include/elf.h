
#define EI_NIDENT 16

#define ELF_MAG "\x7F""ELF"

typedef unsigned int * Elf32_Addr;      /* Program Address */
typedef unsigned short int Elf32_Half;  /* unsigned short number */
typedef unsigned int Elf32_Off;         /* Offset number */
typedef int Elf32_Sword;                /* signed 4 bit number */
typedef unsigned int Elf32_Word;        /* unsigned large integer */

typedef struct ElfHeader {
    unsigned char e_ident[EI_NIDENT];
    Elf32_Half    e_type;
    Elf32_Half    e_machine;
    Elf32_Word    e_version;
    Elf32_Addr    e_entry;
    Elf32_Off     e_phoff;
    Elf32_Off     e_shoff;
    Elf32_Word    e_flags;
    Elf32_Half    e_ehsize;
    Elf32_Half    e_phentsize;
    Elf32_Half    e_phnum;
    Elf32_Half    e_shentsize;
    Elf32_Half    e_shnum;
    Elf32_Half    e_shstrndx;
} Elf32_Ehdr;