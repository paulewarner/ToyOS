#include "tty.h"
#include "vm.h"

int main()
{
    TTYInit();
    KAllocInit();
    Printk("Hello, Kernel!\n");
}
