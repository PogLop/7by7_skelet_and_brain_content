//nejvetsie binarny súbor pod sirym sluncom, priaťelě
//[DEBUG]

#include <stdint.h>
#include "fudis.h"
#include "nehet.h"
#include "nehet.c"
#include "fudis.c"
#include <string.h>


#define MSIZE 7


void PRINTmatrix(int16_t *m, int lena, int lenb)
{
    int a,b;
    for(a = 0; a < lena; a++)
    {
        for(b = 0; b < lenb; b++)
        {
            printf("%d", *(m + (a * lenb + b)));
        }
        printf("\n");
    }
}



int main(void)
{
    uint8_t a;
    
    int16_t matrix[MSIZE][MSIZE];
    memset(matrix, 0, sizeof(matrix));
    
    char _send_m[128];


    t_foodis *fud = FOODISprepstruct(7777, "127.0.0.1");

    //FOODISmail(fud, "list 678 ggasd 88d;", "/blabla/cus");
    //matrix[y][x];

    for(a = 0; a < MSIZE; a++) { matrix[a][a] = 1; }
    for(a = 0; a < MSIZE; a++) { matrix[a][0] = 1; }

    matrix[0][6] = 1;

    char *_tmp = FORMATRIX((int16_t *)matrix, MSIZE, MSIZE);

    snprintf(_send_m, sizeof(_send_m), "list %s;", _tmp);
    
    FOODISmail(fud, _send_m, "/matrix");

    PRINTmatrix(*matrix, MSIZE, MSIZE);
    
    FOODISkonec(fud);
    free(_tmp);
    
    return 0;
}