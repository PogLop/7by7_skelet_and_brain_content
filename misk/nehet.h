#pragma once

#include <stdint.h>

char *FORMATRIX(int16_t *matrix, int8_t sizea, int8_t sizeb, int8_t offs);
//int **UNFORMATRIX(char *matrix, int sizea, int sizeb);

//ver specific function, that turns 3 dimensional array into single dimension
//array formatted as partial standart fudi list (the list keyword is missing),
//thats the cause of "offset" variable and ";" is absent, so you will need
//to add it manualy
//char *FORMATPNUKTRIX(int16_t *matrix, int sizea, int sizeb, int sizec, int offset);

//int *UNFORMATPNUKTRIX(char *matrix, int sizea, int sizeb, int sizec);

//int DIDTHEMATRIXCHANGE(int *matrix, int count, ...);