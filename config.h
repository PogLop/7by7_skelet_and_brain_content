#pragma once

//simlper pin reassignment
//kjabdkbaskdbkabss

#define PIN_A_PNUK_A 16
#define PIN_B_PNUK_A 20
#define PIN_KNOFL_PNUK_A 21

#define PIN_A_PNUK_B 14
#define PIN_B_PNUK_B 15
#define PIN_KNOFL_PNUK_B 18

#define PIN_A_PNUK_C 0
#define PIN_B_PNUK_C 5
#define PIN_KNOFL_PNUK_C 22

#define PIN_NOKIA_DC 4
#define PIN_NOKIA_RST 27
//#define PIN_NOKIA_CE 17
//rest of the pins is handled by pigpio spi implementation

#define MUX_A_COM 17 //do not use gpio 2 :)
#define MUX_A_ADDR_1 23
#define MUX_A_ADDR_2 24
#define MUX_A_ADDR_3 25

#define MUX_B_COM 6
#define MUX_B_ADDR_1 19
#define MUX_B_ADDR_2 26
#define MUX_B_ADDR_3 1

#define SPI_SPEED 4000000