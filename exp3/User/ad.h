#ifndef __AD_H__
#define __AD_H__

#include "stdint.h"

void AD_Init(void);
uint32_t AD_Get(void);
uint8_t  Get_Temp(uint32_t AD);

#endif


