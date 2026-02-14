#include "../komplex_budov_data.h"
#include "nehet.h"

#include <stdlib.h>
#include <stdarg.h>

//data se prenasi tak jak jsou, je treba znat strukturu aby se to dalo dekodovat. asi ok?
//pointless copying of ints into chars and wasting memory, what a day

char *FORMATMATRIX(int *matrix, int sizea, int sizeb)
{
    char *turin = malloc(sizea * sizeb); 
    //dear, do not forget to call free later please

    for(int a = 0; a < sizea; a++)
    {
        for(int b = 0; b < sizeb; b++)
        {
            turin[a * sizeb + b] = *(matrix + a * sizeb + b) - '0';
        }
    }
    
    return turin;
}

char *FORMATPNUKMATRIX(int *pmatrix, int sizea, int sizeb, int sizec)
{
    char *turin = malloc(sizea * sizeb * sizec);
    int inde; //x
    //dear, do not forget to call free later please

    for(int a = 0; a < sizea; a++)
    {
        for(int b = 0; b < sizeb; b++)
        {
            for(int c = 0; c < sizec; c++)
            {
                inde = a + (b * sizea) + (c * sizea * sizeb);
                turin[inde] = *(pmatrix + inde) - '0';
            }
        }
    }

    return turin;
}

int DIDTHEMATRIXCHANGE(int *matrix, int c, ...) //dimensions
{
    int did;
    
    va_list argsuments;
    va_start(argsuments, c);

    
    
    va_end(argsuments);

    return did;
}