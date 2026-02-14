#pragma once
#include "../komplex_budov_data.h"

char *FORMATMATRIX(int *matrix, int sizea, int sizeb);
char *FORMATPNUKMATRIX(int *pmatrixguy, int sizea, int sizeb, int sizec);

int DIDTHEMATRIXCHANGE(int *matrix, int count, ...);