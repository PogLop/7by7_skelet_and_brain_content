#include "fudis.h"
#include "fudis.c"

int main(void)
{
    t_foodis *fud = FOODISprepstruct(8234, "127.0.0.1");

    FOODISmail(fud, "list 678 ggasd 88d;", "/blabla/cus");
    FOODISkonec(fud);
    
    return 0;
}