#include "timer.h"
#include "LPC23xx.H"
#include "wave.h"
extern volatile uint8_t time_10ms_flag;
extern float system_time;

extern uint8_t wave_type;
extern float amplitude;
extern float frequency;
extern float offset;
extern float duty;

//TIMER0�жϷ�����
void __irq IRQ_Timer0 (void)
{
    static uint8_t  count=0;
    static uint32_t da_out;
    count++;
	if(count>100)
    {
        time_10ms_flag = 1;
        count = 0;
    }
    
    
    if(wave_type==0)da_out = wave_square( frequency, amplitude, offset,duty);
    else if(wave_type==1)da_out = wave_sin( frequency, amplitude, offset);
    else if(wave_type==2)da_out = wave_triangle( frequency, amplitude, offset);
    else if(wave_type==3)da_out = wave_sawtooth( frequency, amplitude, offset);
    
    DACR = da_out<<6;
    
    system_time += 0.0001;
    
	T0IR = 0x01;			    //����жϱ�־
	VICVectAddr = 0x00;			//֪ͨVIC�жϴ������������VIC
}

//TIMER0��VIC��ʼ��
void Timer_Init(uint32_t time_us)
{
    /* ��ʱ��0�趨 */
	T0TC   = 0;		    //��ʱ��0�ļ���������									
	T0PR   = 0;		    //ʱ�Ӳ�Ԥ��Ƶ													
	T0MCR  = 0x03;	    //����T0MR0ƥ���λT0TC���������жϱ�־									
	T0MR0  = (PCLK_TIMER0/1000000)*time_us ;  //TIM0��PCLK			
                        //�趨Ϊ100����ÿ100us �ж�һ��						
	T0TCR  = 0x01;	    //������ʱ��													
						
	/* ����IRQ TIM0�ж϶�Ӧ����VIC�ж�ͨ�����ж�����4*/
	VICIntSelect = VICIntSelect & (~(1<<4));	//��ʱ��0�ж�ͨ������ΪIRQ�ж�
    VICVectPriority4 = 0x00;                    //�����ж�����4�����ȼ�
	VICVectAddr4 = (unsigned int)IRQ_Timer0;    //�����ж�����4���жϳ����ַΪTIM0�жϳ���				
	VICIntEnable |= 1 << 0x04;			        //ʹ���ж�����4��������ʱ��0�ж�					
}




