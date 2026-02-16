#pragma once

typedef struct _foodis
{
    int port;
    const char *ip;
}t_foodis;

t_foodis *FOODISprepstruct(const int fport, const char fip[]);
void FOODISmail(t_foodis *f, char fdata[], const char route[]);

char *FOODISgetmail(); //mozna

void FOODISkonec(t_foodis *f);
void FOODISerrr(const char *err);