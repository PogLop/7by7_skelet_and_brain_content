#include <stdint.h>
#include <stdio.h>
#include <pigpio.h>
#include <stdlib.h>
#include "pnuk.h"


#define P_IN PI_INPUT
#define P_OUT PI_OUTPUT

#define PL_D PI_PUD_DOWN
#define PL_U PI_PUD_UP
#define PL_F PI_PUD_OFF


typedef struct pnukS
{
	pnukCallMeBackT callback;
	pnukCallMeBackT knoflCallback;
	int gpioA;
	int gpioB;
	int stateA;
	int stateB;
	int lastGpio;
	int knoflPin;
	int knoflState;
	int id;
} pnukT;


static void _knofl_callback(int gpio, int level, uint32_t tick, void *user)
{
	pnukT *pnuk;

	pnuk = user;

	/*
	static int state = 0;

	state = (state << 1) | level | 0xfe00;

	if(pnuk -> knoflState == 0xff00) pnuk -> knoflCallback(1);

	printf("%d\n", pnuk -> knoflState);
	*/

	if(!level) { pnuk->knoflCallback(1, pnuk -> id); }
}

static void _callback(int gpio, int level, uint32_t tick, void *user)
{
	pnukT *pnuk;

	pnuk = user;

	if(gpio == pnuk -> gpioA) pnuk -> stateA = level; else pnuk -> stateB = level;

	if(gpio != pnuk -> lastGpio)
	{
		pnuk -> lastGpio = gpio;

		if((gpio == pnuk -> gpioA) && (level == 1))
		{
			if(pnuk -> stateB) (pnuk -> callback)(1, pnuk -> id);
		}
		else if((gpio == pnuk -> gpioB) && (level == 1))
		{
			if(pnuk -> stateA) (pnuk -> callback)(-1, pnuk -> id);
		}
	}
}

pnukT * pnukPnuk(int id, int gpioA, int gpioB, int knoflPin, pnukCallMeBackT callback, pnukCallMeBackT knoflCallback)
{
	pnukT *pnuk;

	pnuk = malloc(sizeof(pnukT));

	pnuk -> gpioA = gpioA;
	pnuk -> gpioB = gpioB;
	pnuk -> callback = callback;
	pnuk -> knoflCallback = knoflCallback; 
	pnuk -> stateA = 0;
	pnuk -> stateB = 0;
	pnuk -> lastGpio = -1;
	pnuk -> knoflPin = knoflPin;
	pnuk -> knoflState = 0;
	pnuk -> id = id;

	
	gpioSetMode(gpioA, P_IN);
	gpioSetMode(gpioB, P_IN);
	gpioSetMode(knoflPin, P_IN);
	
	gpioSetPullUpDown(gpioA, PL_U);
	gpioSetPullUpDown(gpioB, PL_U);
	gpioSetPullUpDown(knoflPin, PL_U);

	gpioSetAlertFuncEx(gpioA, _callback, pnuk);
	gpioSetAlertFuncEx(gpioB, _callback, pnuk);
	gpioSetAlertFuncEx(knoflPin, _knofl_callback, pnuk);

	gpioGlitchFilter(knoflPin, 300);
	
	return pnuk;
}

void pnukOver(pnukT *pnuk)
{
	if(pnuk) 
	{
		gpioSetAlertFunc(pnuk->gpioA, 0);
		gpioSetAlertFunc(pnuk->gpioB, 0);
		gpioSetAlertFunc(pnuk->knoflPin, 0);
		free(pnuk);
	}
}
