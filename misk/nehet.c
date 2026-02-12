#include "../komplex_budov_data.h"
#include "nehet.h"

#include <stdlib.h>
#include <stdarg.h>

char *FORMATMATRIX(int *matrix, int sizea, int sizeb)
{
    char *turin = malloc(sizea * sizeb * M_TRANSM_SIZE); 
    //dear, do not forget to call free later please
    


    return turin;
}

char *FORMATPNUKMATRIX(int *pmatrix, int sizea, int sizeb, int sizec)
{
    char *turin = malloc(sizea * sizeb * sizec * PM_TRANSM_SIZE);
    //dear, do not forget to call free later please


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