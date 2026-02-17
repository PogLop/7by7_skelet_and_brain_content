#include "nehet.h"
#include "nehet.c"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    char *buffer;
    int16_t arr[7][7];
    int16_t rarr[7][7];

    memset(arr, 0, sizeof(arr));
    memset(rarr, 0, sizeof(rarr)); //zero your arrays kids

    //arr[3][5] = 1;
    arr[0][0] = 1;
    //rarr[0][1] = 1;
    rarr[0][0] = 1;

    buffer = FORMATRIX((int16_t *)arr, 7, 7);
    
    printf("%s\n", buffer);

    free(buffer);

    if(MATRIXCMP((int16_t *)arr, (int16_t *)rarr, 7, 7))
    {
        printf("mathiiiing\n");
    }

    return 0;
}