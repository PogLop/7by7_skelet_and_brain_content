#pragma once
#include "../komplex_budov_data.h"

char *FORMATRIX(int *matrix, int sizea, int sizeb);
int **UNFORMATRIX(char *matrix, int sizea, int sizeb);

char *FORMATPNUKTRIX(int *matrix, int sizea, int sizeb, int sizec);
int *UNFORMATPNUKTRIX(char *matrix, int sizea, int sizeb, int sizec);

int DIDTHEMATRIXCHANGE(int *matrix, int count, ...);