#include "da.h"
#include "LPC23xx.H"

//DA初始化
void DA_Init(void)
{
    PINSEL10 = 0;		                        //禁止ETM
    PINSEL1 = (PINSEL1&0xFFCFFFFF)|0x00200000;  //P0.26功能引脚设定为DA
}


