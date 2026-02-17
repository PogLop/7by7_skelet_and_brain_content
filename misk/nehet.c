#include "nehet.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

//data se prenasi tak jak jsou, je treba znat strukturu aby se to dalo dekodovat. asi ok?
//pointless copying of ints into chars and wasting memory, what a day

//...1 023

//to be precise, this profoundly random collection of functions turns internal
//representation of hardware matrix to format, that can be easily transoprtable 
//óver údp network protocol to pure data (implemented by fudis.c and fudis.h),
//where it will be parsed as FUDI and then consumed by objects as "simple_matrix~" 
//or "pnukget". all this to simplify sounding patch creationalism.

//whatever, shoudl kept it simple duuh

//list 0 0 A 342;

char *FORMATRIX(int16_t *matrix, int8_t sizea, int8_t sizeb, int8_t offs) 
{
    char *turin = (char *)malloc(sizea * sizeb * sizeof(char) * 2 + offs);
    int8_t a,b,num,ind;
    //dear, do not forget to call free later please

    for(a = 0; a < sizea; a++)
    {
        for(b = 0; b < sizeb*2; b+=2)
        {
            //printf("%d", b);
            ind = (a * sizeb) + b/2;
            num = *(matrix + ind) + '0';

            ind = (a * sizeb * 2) + b;

            turin[ind] = num;
            turin[ind+1] = '\x20';
        }
    }
    
    return turin;
}


/* unused :O)

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

*/