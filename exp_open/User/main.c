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

//��ʱ��10ms��־�����ڰ���ɨ������ʾ����
volatile uint8_t time_10ms_flag = 0;

uint8_t wave_type=0;    //�������ͣ�0��������1�����Ҳ���2�����ǲ���4����ݲ�
float amplitude=3.3;    //���η�ֵ
float frequency=100;    //����Ƶ��
float offset=0;         //����ƫ��
float duty=50;          //����ռ�ձ�
float system_time=0.0;  //ϵͳʱ��
int main (void) {
    char str[50];
    //OLED��ʾ����ʼ��
    OLED_Init();
    //���ƿ�������
    Draw_BootPage();
    //���Ʋ�����
    Draw_WaveType(0);
    //���������ʼ��
    ParameterList_Init();
    //������ʼ��
    Key_Init();
    //��ʼ��DA
    DA_Init();
    //��ʼ��TIMER0������100us��ʱ�ж�
    Timer_Init(100);
    
	while (1){
        if(time_10ms_flag){
            time_10ms_flag = 0;
            sprintf(str,"Time: %.1fS",system_time);
            OLED_Print(0,6,(uint8_t *)str);
            Key_Scan();         //����ɨ��
            Parameter_Change(); //���²���
        }
    }
}


