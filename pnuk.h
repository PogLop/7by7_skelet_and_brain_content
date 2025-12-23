#ifndef PNUK_H
#define PNUK_H


typedef void (*pnukCallMeBackT)(int, int);
//hodnota, id
//id = gpio přiřazené knoflíku

typedef struct pnukS pnukT;


pnukT * pnukPnuk(int id, int gpioA, int gpioB, int knoflPin, pnukCallMeBackT callback, pnukCallMeBackT knoflCallback); 
//aktivuje dekódování enkodéru na gpio pinech A a B
//funkce callback je zavolána pokaždé, když enkodér zaznamená pohyb
//vrací pnukT (hodí se k použití funkce "pnukOver")

void pnukOver(pnukT *pnuk); //uvolní zdroje používané enkodérem


#endif