#include <stdlib.h>
#include <stdio.h>
#include "LPC23xx.H"
#include "da.h"
#include "timer.h"
#include "uart.h"
#include "math.h"
#include "oled.h"
#include "ui.h"
#include "key.h"
#include "wave.h"

//定时器10ms标志，用于按键扫描与显示更新
volatile uint8_t time_10ms_flag = 0;

uint8_t wave_type=0;    //波形类型，0：方波、1：正弦波、2：三角波、4：锯齿波
float amplitude=3.3;    //波形幅值
float frequency=100;    //波形频率
float offset=0;         //波形偏置
float duty=50;          //方波占空比
float system_time=0.0;  //系统时间
int main (void) {
    char str[50];
    //OLED显示屏初始化
    OLED_Init();
    //绘制开机画面
    Draw_BootPage();
    //绘制波形栏
    Draw_WaveType(0);
    //参数链表初始化
    ParameterList_Init();
    //按键初始化
    Key_Init();
    //初始化DA
    DA_Init();
    //初始化TIMER0，产生100us定时中断
    Timer_Init(100);
    
	while (1){
        if(time_10ms_flag){
            time_10ms_flag = 0;
            sprintf(str,"Time: %.1fS",system_time);
            OLED_Print(0,6,(uint8_t *)str);
            Key_Scan();         //按键扫描
            Parameter_Change(); //更新参数
        }
    }
}


