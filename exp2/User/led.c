#include "led.h"
#include "LPC23xx.H"

//LED��ʼ��
void LED_Init(void)
{
    PINSEL10 = 0;		        //��ֹETM
    PINSEL4 &= 0xFFFFFF00;      //ѡ��P2.0-P2.7ΪGPIO
    FIO2DIR |= 0x000000FF;      //����P2.0-P2.7Ϊ���
    FIO2MASK &= 0xFFFFFF00;    
    FIO2SET  = 0x000000FF;      //Ϩ������LED  
}

//LED���ú�������ӦλΪ1��ʾ����
void LED_Config(uint8_t led_status)
{
    uint32_t status = 0x00000000;
    status |= led_status;
    FIO2CLR = status;
    status = 0x00000000;
    status |= ~led_status;
    FIO2SET = status;
}



