#include "../komplex_budov_data.h"
#include "nehet.h"

#include <stdlib.h>
#include <stdarg.h>

//data se prenasi tak jak jsou, je treba znat strukturu aby se to dalo dekodovat. asi ok?
//pointless copying of ints into chars and wasting memory, what a day

//...1 023

char *FORMATRIX(int *matrix, int sizea, int sizeb) 
{
    char *turin = (char *)malloc(sizea * sizeb * sizeof(char));
    int inde,a,b; //x
    //dear, do not forget to call free later please

    for(a = 0; a < sizea; a++)
    {
        for(b = 0; b < sizeb; b++)
        {
            inde = (a * MATRIX_SIZE) + b;
            turin[inde] = *(matrix + inde) - '0';
        }
    }
    
    return turin;
}

int **UNFORMATRIX(char *matrix, int sizea, int sizeb)
{
    int h, index, y;
    int **r = (int **)malloc(sizeof(int *) * sizea);
    
    for(h = 0; h < sizeb; h++)
    {
        r[h] = (int *)malloc(sizeof(int) * sizeb);
    }

    for(h = 0; h < sizea; h++)
    {
        for(y = 0; y < sizeb; y++)
        {
            index = (h * MATRIX_SIZE) + y;
            r[h][y] = matrix[index] + '0';
        }
    }

    return r;
}

char *FORMATPNUKTRIX(int *matrix, int sizea, int sizeb, int sizec)
{
    char *r = (char *)malloc(sizea * sizeb * (sizec * 3)); //sizec -->– kolik je pnuku; 3 -->- 3 digit value

    return r;
}

int *UNFORMATPNUKTRIX(char *matrix, int sizea, int sizeb, int sizec);

int DIDTHEMATRIXCHANGE(int *matrix, int c, ...) //dimensions
{
    int did;
    
    va_list argsuments;
    va_start(argsuments, c);

    
    
    va_end(argsuments);

    return did;
}