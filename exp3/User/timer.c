#include "timer.h"
#include "LPC23xx.H"

extern volatile uint8_t time_500ms_flag;

//TIMER0中断服务函数
void __irq IRQ_Timer0 (void)
{
	time_500ms_flag = 1;

	T0IR = 0x01;			    //清除中断标志
	VICVectAddr = 0x00;			//通知VIC中断处理结束，更新VIC
}

//TIMER0与VIC初始化
void Timer_Init(uint32_t time_ms)
{
    /* 定时器0设定 */
	T0TC   = 0;		    //定时器0的计数器清零									
	T0PR   = 0;		    //时钟不预分频													
	T0MCR  = 0x03;	    //设置T0MR0匹配后复位T0TC，并产生中断标志									
	T0MR0  = (Fpclk/1000)*time_ms ;  //TIM0的PCLK=CCLK/4=48/4=12M 					
                        //设定为500，则每0.5s 中断一次						
	T0TCR  = 0x01;	    //启动定时器													
						
	/* 设置IRQ TIM0中断对应的是VIC中断通道的中断向量4*/
	VICIntSelect = VICIntSelect & (~(1<<4));	//定时器0中断通道设置为IRQ中断
    VICVectPriority4 = 0x00;                    //设置中断向量4的优先级
	VICVectAddr4 = (unsigned int)IRQ_Timer0;    //设置中断向量4的中断程序地址为TIM0中断程序				
	VICIntEnable |= 1 << 0x04;			        //使能中断向量4，即允许定时器0中断					
}




