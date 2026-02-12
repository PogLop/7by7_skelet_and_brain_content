#pragma once
#include "../komplex_budov_data.h"

#define M_TRANSM_SIZE 3 //val x y
#define PM_TRANSM_SIZE 5 //id val val val x y

char *FORMATMATRIX(int *matrix, int sizea, int sizeb);
char *FORMATPNUKMATRIX(int *pmatrixguy, int sizea, int sizeb, int sizec);

int DIDTHEMATRIXCHANGE(int *matrix, int count, ...);