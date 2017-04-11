#include "tty.h"
#include "vm.h"
#include "util.h"

int main()
{
    TTYInit();
    Panic("testing panic...");
}
