#include "timer.h"
#include "LPC23xx.H"
#include "led.h"

//TIMER0�жϷ�����
void __irq IRQ_Timer0 (void)
{
    uint8_t LED = 0x01;
	static uint8_t count = 0;
    LED_Config(LED<<count);
    count++;
    if(count>7)count=0;
    
	T0IR = 0x01;			    //����жϱ�־
	VICVectAddr = 0x00;			//֪ͨVIC�жϴ������������VIC
}

//TIMER0��VIC��ʼ��
void Timer_Init(void)
{
    /* ��ʱ��0�趨 */
	T0TC   = 0;		    //��ʱ��0�ļ���������									
	T0PR   = 0;		    //ʱ�Ӳ�Ԥ��Ƶ													
	T0MCR  = 0x03;	    //����T0MR0ƥ���λT0TC���������жϱ�־									
	T0MR0  = 12000000 ; //TIM0��PCLK=CCLK/4=48/4=12M 					
                        //�趨Ϊ12000000����ÿ1s LED״̬�任һ��						
	T0TCR  = 0x01;	    //������ʱ��													
						
	/* ����IRQ TIM0�ж϶�Ӧ����VIC�ж�ͨ�����ж�����4*/
	VICIntSelect = VICIntSelect & (~(1<<4));	//��ʱ��0�ж�ͨ������ΪIRQ�ж�
    VICVectPriority4 = 0x00;                    //�����ж�����4�����ȼ�
	VICVectAddr4 = (unsigned int)IRQ_Timer0;    //�����ж�����4���жϳ����ַΪTIM0�жϳ���				
	VICIntEnable |= 1 << 0x04;			        //ʹ���ж�����4��������ʱ��0�ж�					
}




