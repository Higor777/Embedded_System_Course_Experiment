#include "led.h"
#include "LPC23xx.H"

//LED初始化
void LED_Init(void)
{
    PINSEL10 = 0;		        //禁止ETM
    PINSEL4 &= 0xFFFFFF00;      //选择P2.0-P2.7为GPIO
    FIO2DIR |= 0x000000FF;      //设置P2.0-P2.7为输出
    FIO2MASK &= 0xFFFFFF00;    
    FIO2SET  = 0x000000FF;      //熄灭所有LED  
}

//LED配置函数，相应位为1表示灯亮
void LED_Config(uint8_t led_status)
{
    uint32_t status = 0x00000000;
    status |= led_status;
    FIO2CLR = status;
    status = 0x00000000;
    status |= ~led_status;
    FIO2SET = status;
}



