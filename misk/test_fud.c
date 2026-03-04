//nejvetsie binarny súbor pod sirym sluncom, priaťelě
//[DEBUG]

#include <stdint.h>
#include "fudis.h"
#include "nehet.h"
#include "nehet.c"
#include "fudis.c"
#include <string.h>



#define MSIZE 7

int main(void)
{
    int16_t matrix[MSIZE][MSIZE];
    memset(matrix, 0, sizeof(matrix));
    
    char _send_m[128];


    t_foodis *fud = FOODISprepstruct(7777, "127.0.0.1");

    //FOODISmail(fud, "list 678 ggasd 88d;", "/blabla/cus");

    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[3][4] = 1;

    char *_tmp = FORMATRIX((int16_t *)matrix, MSIZE, MSIZE);

    snprintf(_send_m, sizeof(_send_m), "list %s;", _tmp);
    
    FOODISmail(fud, _send_m, "/matrix");
    
    FOODISkonec(fud);
    free(_tmp);
    
    return 0;
}