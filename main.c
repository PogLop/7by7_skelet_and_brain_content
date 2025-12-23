#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "halohalo_5100.h"
#include "komplex_budov_data.h"
#include "pnuk.h"
#include "pnuk_driver.h"
#include "room.h"
#include "halohalo_buffer.h"


#define MINIOSC_IMPLEMENTATION
#include "miniosc/miniosc.h"


#define P_IN PI_INPUT
#define P_OUT PI_OUTPUT

#define PL_D PI_PUD_DOWN
#define PL_U PI_PUD_UP
#define PL_F PI_PUD_OFF


uint8_t *itb(uint8_t k, int size)
{
	uint8_t *output = malloc(size);

	if(!output) return NULL;

	memset(output, 0, size);
	
	if(k == 0) return output;
	if(k == 1) { output[0] = 1; return output; }

  for(int p = 0; p < size; p++)
  {
		output[p] = (k >> p) & 1;
  }

	return output;
}


void setup()
{
	//SETUP
	//COMM OUT/IN
	gpioSetMode(2, P_OUT); //ST MUX
	gpioSetMode(4, P_IN); //ND MUX
	gpioSetPullUpDown(4, PL_D);

	//MUX1 ADDR SELECT
	gpioSetMode(17, P_OUT);
	gpioSetMode(27, P_OUT);
	gpioSetMode(22, P_OUT);

	//MUX2 ADDR SELECT
	gpioSetMode(0, P_OUT);
	gpioSetMode(5, P_OUT);
	gpioSetMode(6, P_OUT);
	//SETUP END :(

	printf("77ready asi? :o)77\n");
	
	return;
}


void setMuxAddr(uint8_t st_mux, uint8_t nd_mux) //sets channel address on both MUXes
{
	uint8_t *mx_one = itb(st_mux, 3);
	uint8_t *mx_two = itb(nd_mux, 3);

	if(mx_one && mx_two)
	{
		gpioWrite(17, mx_one[0]);
		gpioWrite(27, mx_one[1]);
		gpioWrite(22, mx_one[2]);
		gpioWrite(0, mx_two[0]);
		gpioWrite(5, mx_two[1]);
		gpioWrite(6, mx_two[2]);

		free(mx_one);
		free(mx_two);
	}
}

int main(int argc, char **argv)
{
	if(gpioInitialise() < 0) return 1;

	setup();

	//matrix
	volatile int matrix_state[MATRIX_SIZE][MATRIX_SIZE];
	//

	//pnuky
	pnuk_data_t *data_z_pnuku;

	pnuk_config_t enkodery[PNUKU_JE_TOLIK] = {
		{.gpioA = 20, .gpioB = 21, .knoflPin = 16},		
		{.gpioA = 15, .gpioB = 14, .knoflPin = 18},		
		{.gpioA = 23, .gpioB = 24, .knoflPin = 25},
	};

	pnuk_init(enkodery);
	//

	//osc
	miniosc *osc = minioscInit(7000, 7777, "127.0.0.1", 0);
	//

	//nokia
	static buffer_render_nokia_t nokia = {
		.init = nokia_init,
		.draw_rectal = nokia_draw_rectal,
		.draw_line = nokia_draw_line,
		.circle = nokia_circle,
		.point = nokia_point,
		.clear = nokia_clear,
		.framebuffer_flush = nokia_framebuffer_flush
	};
	//

	//ctx
	room_ctx_t ctx = {
		.nokia_render = &nokia,
		.matrix_state = &matrix_state,
		.pane_osc = osc,
		.pnuky = data_z_pnuku
	};
	//

	// matrix status read
	while(1)
	{
		for(int a = 0; a < 7; a++)
		{
			for(int b = 0; b < 7; b++)
			{
				gpioWrite(2, 1);
				
				setMuxAddr(b, a);

				gpioDelay(5);
				
				matrix_state[a][b] = gpioRead(4);

				gpioWrite(2, 0);
			}
		}
		
		data_z_pnuku = get_data();
	}
	
	pnuk_driver_de_init();
	gpioTerminate();
	return 0;
}