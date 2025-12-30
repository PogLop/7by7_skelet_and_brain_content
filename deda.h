#pragma once

#include "komplex_budov_data.h"
#include <stdint.h>

#define RST_PIN 16
#define DC_PIN 26
#define CE_PIN 25

#define NOKIA_BANKS_Y 6
#define NOKIA_BANKS_X 84

int deda_nokia_init();

void set_display_x(uint8_t value);
void set_display_y(uint8_t value);

void mentalni_ocista();

void deda_nokia_buffer_flush(frame_buffer_t* frame_buffer);

void test_write();