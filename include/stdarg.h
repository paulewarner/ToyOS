#ifndef STDARG_H
#define STDARG_H

/* very limited stdarg implementation
    Some caveats:
    va_start must be before any other function call
    all declared parameters to the function must be 8 bytes
*/

#define NREG_ARGS 6

typedef struct va_list {
    long unsigned int reg_args[NREG_ARGS];
    char *overflow_args;
    long int current;
} va_list;

/* If you're here becuase something with varargs is broken, try checking
   the current part. */
#define va_start(va_list, lastarg) do {                                    \
    asm("\t movq %%rbp, %0" : "=r"(va_list.current));                      \
    va_list.current = (va_list.current-(long int)&lastarg)/sizeof(char *); \
    va_list.overflow_args = (void *)&lastarg;                              \
    asm("\t movq %%rdi, %0" : "=r"(va_list.reg_args[0]));                  \
    asm("\t movq %%rsi, %0" : "=r"(va_list.reg_args[1]));                  \
    asm("\t movq %%rdx, %0" : "=r"(va_list.reg_args[2]));                  \
    asm("\t movq %%rcx, %0" : "=r"(va_list.reg_args[3]));                  \
    asm("\t movq %%r8, %0" : "=r"(va_list.reg_args[4]));                   \
    asm("\t movq %%r9, %0" : "=r"(va_list.reg_args[5]));                   \
} while (0)

#define va_end(va_list) do {} while (0);

#define va_arg(va_list, type)  \
    va_list.current < NREG_ARGS ? \
    (type)va_list.reg_args[va_list.current++] : \
    *(type *)((va_list.overflow_args += sizeof(type)) - sizeof(type))

#endif /* STDARG_H */