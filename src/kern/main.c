#include "tty.h"

void MemInit()
{

}

int main()
{
    TTYInit();
    MemInit();
    Printk("Hello, Kernel!\n");
}
