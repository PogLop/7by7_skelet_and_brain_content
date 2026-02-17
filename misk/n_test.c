#include "nehet.h"
#include "nehet.c"
#include <string.h>
#include <stdio.h>

int main(void)
{
    char *buffer;
    int16_t arr[7][7];

    memset(arr, 0, sizeof(arr));

    //arr[3][5] = 1;
    arr[0][0] = 1;

    buffer = FORMATRIX((int16_t *)arr, 7, 7);
    
    printf("%s\n", buffer);

    free(buffer);
    return 0;
}