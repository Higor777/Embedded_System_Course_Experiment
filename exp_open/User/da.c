#include "da.h"
#include "LPC23xx.H"

//DA��ʼ��
void DA_Init(void)
{
    PINSEL10 = 0;		                        //��ֹETM
    PINSEL1 = (PINSEL1&0xFFCFFFFF)|0x00200000;  //P0.26���������趨ΪDA
}


