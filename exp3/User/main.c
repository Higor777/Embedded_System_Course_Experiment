#include <stdlib.h>
#include <stdio.h>
#include "LPC23xx.H"
#include "ad.h"
#include "timer.h"
#include "uart.h"

volatile uint8_t time_500ms_flag = 0;
int main (void) {
    uint32_t temperatureAD;
    uint8_t temperature;
    //��ʼ��AD
    AD_Init();
    //UART��ʼ����������57600
    UART_Init(57600);
    //��ʼ��TIMER0������0.5s��ʱ�ж�
    Timer_Init(500);
    
	while (1){
        if(time_500ms_flag){
            time_500ms_flag = 0;
            temperatureAD = AD_Get();
            printf("AD����ֵ: %d\n",temperatureAD);
            temperature = Get_Temp(temperatureAD);
            printf("�¶�: %d��\n",temperature);
        }
    }
}
