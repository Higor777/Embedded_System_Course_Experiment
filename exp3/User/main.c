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
    //初始化AD
    AD_Init();
    //UART初始化，波特率57600
    UART_Init(57600);
    //初始化TIMER0，产生0.5s定时中断
    Timer_Init(500);
    
	while (1){
        if(time_500ms_flag){
            time_500ms_flag = 0;
            temperatureAD = AD_Get();
            printf("AD采样值: %d\n",temperatureAD);
            temperature = Get_Temp(temperatureAD);
            printf("温度: %d℃\n",temperature);
        }
    }
}
