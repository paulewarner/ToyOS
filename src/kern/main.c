#include "tty.h"
#include "vm.h"
#include "util.h"

int main()
{
    tty_init();
    panic("testing panic...");
}
