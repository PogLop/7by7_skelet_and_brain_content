#include "nehet.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

//data se prenasi tak jak jsou, je treba znat strukturu aby se to dalo dekodovat. asi ok?
//pointless copying of ints into chars and wasting memory, what a day

//...1 023

//to be precise, this profoundly random collection of functions turns internal
//representation of hardware matrix to format, that can be easily transoprtable 
//óver údp network protocol to pure data, where it will be parsed as FUDI implemeted
//by fudis.c fudis.h and then finally consumed by objects as "simple_matrix~" or 
//"pnukget" to simplify sounding patch creationalism.

char *FORMATRIX(int *matrix, int sizea, int sizeb) 
{
    char *turin = (char *)malloc(sizea * sizeb * sizeof(char));
    int inde,a,b; //x
    //dear, do not forget to call free later please

    for(a = 0; a < sizea; a++)
    {
        for(b = 0; b < sizeb; b++)
        {
            inde = (a * sizeb) + b;
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
            index = (h * sizeb) + y;
            r[h][y] = matrix[index] + '0';
        }
    }

    return r;
}

char *FORMATPNUKTRIX(int16_t *matrix, int sizea, int sizeb, int sizec, int offset)
{
    char *r = malloc(sizea * sizeb * sizec * sizeof(int16_t) + offset); //predikce (7 * 7 * 3 * 2) + 6
    int16_t a, b, c, i, num;
    char sp = '\x20'; 
    unsigned char byts[2];

    //snprintf(r, 5, "list%c", sp); manualne

    for(a = 0; a < sizea; a++)
    {  
        for(b = 0; b < sizeb; b++)
        {
            for(c = 0; c < (sizec * sizeof(int16_t)); c++)
            {
                i = (a + sizea * (b + sizec * c)) + offset; //5 -->- list offset napriklad
                num = *(matrix + i);
                
                byts[0] = num >> 8;
                byts[1] = num & 0x00FF; //lower part

                r[i] = byts[0];
                r[i + 1] = byts[1];
                
                c++;
            }
        }
    }

    return r;
}


//////////
int *UNFORMATPNUKTRIX(char *matrix, int sizea, int sizeb, int sizec); 
//neni treba, diky tomu, ze FUDI pd dostane list 
//a s tim uz se da pracovat 
/////////////

int DIDTHEMATRIXCHANGE(int *matrix, int c, ...) //dimensions
{
    int did;
    
    va_list argsuments;
    va_start(argsuments, c);

    
    
    va_end(argsuments);

    return did;
}