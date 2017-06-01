#ifndef __WAVE_H__
#define __WAVE_H__

#include "LPC23xx.H"
#include "stdint.h"

uint32_t wave_square(float frequency,float amplitude,float offset,float duty);
uint32_t wave_sin(float frequency,float amplitude,float offset);
uint32_t wave_triangle(float frequency,float amplitude,float offset);
uint32_t wave_sawtooth(float frequency,float amplitude,float offset);

#endif


