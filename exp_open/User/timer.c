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

//TIMER0中断服务函数
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
    
	T0IR = 0x01;			    //清除中断标志
	VICVectAddr = 0x00;			//通知VIC中断处理结束，更新VIC
}

//TIMER0与VIC初始化
void Timer_Init(uint32_t time_us)
{
    /* 定时器0设定 */
	T0TC   = 0;		    //定时器0的计数器清零									
	T0PR   = 0;		    //时钟不预分频													
	T0MCR  = 0x03;	    //设置T0MR0匹配后复位T0TC，并产生中断标志									
	T0MR0  = (PCLK_TIMER0/1000000)*time_us ;  //TIM0的PCLK			
                        //设定为100，则每100us 中断一次						
	T0TCR  = 0x01;	    //启动定时器													
						
	/* 设置IRQ TIM0中断对应的是VIC中断通道的中断向量4*/
	VICIntSelect = VICIntSelect & (~(1<<4));	//定时器0中断通道设置为IRQ中断
    VICVectPriority4 = 0x00;                    //设置中断向量4的优先级
	VICVectAddr4 = (unsigned int)IRQ_Timer0;    //设置中断向量4的中断程序地址为TIM0中断程序				
	VICIntEnable |= 1 << 0x04;			        //使能中断向量4，即允许定时器0中断					
}




