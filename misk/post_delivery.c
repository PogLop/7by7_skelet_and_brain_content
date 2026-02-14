#include <stdlib.h>
#include <stdio.h>
#include "nehet.h"

#define MINIOSC_IMPLEMENTATION
#include "../miniosc/miniosc.h"


#define say printf


int main(int argc, char *argv[])
{
    int port = atoi(argv[2]); say("living on port %d!!", port);
    
    int stat_me[MATRIX_SIZE][MATRIX_SIZE];

    char path[] = "/matrix/data";
    char metrix[MATRIX_SIZE * MATRIX_SIZE];

    miniosc *osc = minioscInit(0, port, "127.0.0.0", 0);

    while(1)
    {
        
    }
}