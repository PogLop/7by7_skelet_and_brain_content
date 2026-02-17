#include "nehet.h"
#include "nehet.c"
#include <string.h>
#include <stdio.h>

int main(void)
{
    char *buffer;
    int16_t arr[7][7];

    memset(arr, 0x0, sizeof(arr));

    arr[3][5] = 1;

    buffer = FORMATRIX((int16_t *)arr, 7, 7, 0);

    for(int g = 0; g < 100; g++)
    {
        printf("%c", buffer[g]);
    }
    
    printf("%s\n", buffer);

    free(buffer);
    return 0;
}