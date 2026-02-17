#include <pigpio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//hlavy
#include "halohalo_buffer.h"
#include "komplex_budov_data.h"
#include "pnuk.h"
#include "pnuk_driver.h"
#include "deda.h"
#include "misk/fudis.h"
#include "misk/nehet.h"


//menu includerationoles
#include "room.h"
#include "gridlock_room.h"


//implementationoies
#include "halohalo_buffer.c"
#include "pnuk.c"
#include "pnuk_driver.c"
#include "room.c"
#include "gridlock_room.c"
#include "deda.c"
#include "misk/fudis.c"
#include "misk/nehet.c"


#define P_IN PI_INPUT
#define P_OUT PI_OUTPUT

#define PL_D PI_PUD_DOWN
#define PL_U PI_PUD_UP
#define PL_F PI_PUD_OFF


/*

stack based menu system anti-thesis


*/
#define KOMPLEX_SIZE_X 10 
#define KOMPLEX_SIZE_Y 10


//integer to array of 0 and 1
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


//setup general purpose input/output pins for device operation
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

	//nokia
	gpioSetMode(26, P_OUT); //data/command
	gpioSetMode(16, P_OUT); //rst
	//gpioSetPullUpDown(16, PL_D);
	gpioSetMode(25, P_OUT); //ce
	//SETUP END :(

	printf("77ready asi? :o)77\n");
	
	return;
}


//sets channel address on both MUXes
void setMuxAddr(uint8_t st_mux, uint8_t nd_mux)
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
	int16_t matrix_state[MATRIX_SIZE][MATRIX_SIZE];
	memset(matrix_state, 0, sizeof(matrix_state));

	//pnuktrix
	int16_t matrix_value_array[MATRIX_SIZE][MATRIX_SIZE][PNUKU_JE_TOLIK];
    memset(matrix_value_array, 0, sizeof(matrix_value_array));


	//místonoosti
	int mi_x = 0;
	int mi_y = 0;
	
	static updte_slave_fn_make_him_better mistnosti[KOMPLEX_SIZE_X][KOMPLEX_SIZE_Y];

	//memset nestacil :)
	for(int a = 0; a < KOMPLEX_SIZE_X; a++)
	{
		for(int b = 0; b < KOMPLEX_SIZE_Y; b++)
		{
			mistnosti[a][b] = entrance_update;
		}		
	}

	//set room map
	mistnosti[0][0] = gridlock_update;


	//pnuky
	pnuk_data_t *data_z_pnuku;

	pnuk_config_t enkodery[PNUKU_JE_TOLIK] = {
		{.gpioA = 20, .gpioB = 21, .knoflPin = 1},		
		{.gpioA = 15, .gpioB = 14, .knoflPin = 18},		
		{.gpioA = 23, .gpioB = 24, .knoflPin = 19},
	};
	pnuk_init(enkodery);


	//osc vyslo z mody
	//miniosc *osc = minioscInit(7000, 7777, "127.0.0.1", 0);
	//foodis
	t_foodis *foo = FOODISprepstruct(7777, "127.0.0.1");


	//nokia
	static buffer_render_nokia_t nokia = {
		.init = nokia_init,
		.draw_rectal = nokia_draw_rectal,
		.draw_line = nokia_draw_line,
		.circle = nokia_circle,
		.point = nokia_point,
		.clear = nokia_clear,
		.framebuffer_flush = nokia_framebuffer_flush,
		.draw_misc_buffer = nokia_draw_misc_buffer
	};


	if(nokia_init() < 0)
	{
		printf("spi failed :) [nokia deda]");
		return -1;
	};


	//framebuunkr oj7783
	frame_buffer_t bff;
	memset(bff.buffer, 0x0, sizeof(bff.buffer));
	memset(bff.o_buffer, 0x0, sizeof(bff.o_buffer));


	//main event going round n round
	while(1)
	{
		for(int a = 0; a < 7; a++)
		{
			//read datat from like the matrix thinf
			for(int b = 0; b < 7; b++)
			{
				gpioWrite(2, 1);
				setMuxAddr(b, a);
				gpioDelay(5);
				matrix_state[a][b] = gpioRead(4); //write to matrix
				gpioWrite(2, 0);
			}
		}
		

		data_z_pnuku = pnuk_get_data();


		//bundle for room update!!! renovation!!
		room_ctx_t ctx = {
			.nokia_render = &nokia,
			.matrix_state = &matrix_state,
			.pnuky = data_z_pnuku,
			.food = foo,
			.menu_x = mi_x,
			.menu_y = mi_y,
			.fb = &bff,
			.matrix_pnuk_state = &matrix_value_array
		};


		//update room
		//...
		if(mi_x < KOMPLEX_SIZE_X && mi_y < KOMPLEX_SIZE_Y)
		{
			updte_slave_fn_make_him_better curr = mistnosti[mi_x][mi_y];
	
			if(curr != NULL)
			{
				goto_room_t dalsi = curr(&ctx);
				mi_x = dalsi.x;
				mi_y = dalsi.y;
			}
		}
	}
	
	FOODISkonec(foo);
	pnuk_driver_de_init();
	gpioTerminate();

	return 0; //mirumilovny konec, ktereho nebude nikdá dosazeno.
}