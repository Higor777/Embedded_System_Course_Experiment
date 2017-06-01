#include "uart.h"
#include "timer.h"
#include "stdio.h"
#include "LPC23xx.H"

volatile unsigned char redata=0; //接收数据

volatile unsigned long UART0Status;
volatile unsigned char UART0TxEmpty = 1;

void __irq IRQ_Uart0 (void)
{
    uint8_t IIRValue, LSRValue;
    uint8_t Dummy;
	uint8_t cdata;
   
    IIRValue = U0IIR;
    
    IIRValue >>= 1;			/* skip pending bit in IIR */
    IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
    if ( IIRValue == IIR_RLS )		/* Receive Line Status */
    {
			LSRValue = U0LSR;
			/* Receive Line Status */
			if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
			{
					/* There are errors or break interrupt *///如果线上有错误
					/* Read LSR will clear the interrupt */
					UART0Status = LSRValue; //保留故障代码
					Dummy = U0RBR;		/* Dummy read on RX to clear 
									interrupt, then bail out */ //取走无效数据
                    Dummy=Dummy;//remove warning
					//IDISABLE;
					VICVectAddr = 0;		/* Acknowledge Interrupt */
					return;
			}
			if ( LSRValue & LSR_RDR )	/* Receive Data Ready */			
			{
					/* If no error on RLS, normal ready, save into the data buffer. */
					/* Note: read RBR will clear the interrupt */
					cdata = U0RBR; //取走有效数据
					//if(cdata!=redata)
					{
							redata=cdata;
					}
			}
    }else if ( IIRValue == IIR_RDA )	/* Receive Data Available */
    {
    /* Receive Data Available *///接收数据可用
            cdata = U0RBR; //取走有效数据
            //if(cdata!=redata)
            {
                    redata=cdata;
            }
    }else if ( IIRValue == IIR_CTI )	/* Character timeout indicator */
    {
        /* Character Time-out indicator */
        UART0Status |= 0x100;		/* Bit 9 as the CTI error */
    }else if ( IIRValue == IIR_THRE )	/* THRE, transmit holding register empty */
    {
        /* THRE interrupt */
        LSRValue = U0LSR;		/* Check status in the LSR to see if
                                valid data in U0THR or not */
        if ( LSRValue & LSR_THRE )
        {
                UART0TxEmpty = 1;
        }
        else
        {
                UART0TxEmpty = 0;
        }
    }
		
	VICVectAddr = 0x00;			//通知VIC中断处理结束，更新VIC
}


//UART初始化
void UART_Init(uint32_t baudrate)
{
    uint32_t Fdiv;

    PINSEL10 = 0;		 //禁止ETM

    PINSEL0 = (PINSEL0&0xFFFFFF0F)|0x00000050;               //RxD0 and TxD0 
    U0LCR = 0x83;		                //8 bits, no Parity, 1 Stop bit 允许访问除数锁存
    Fdiv = ( Fpclk / 16 ) / baudrate ;	/*baud rate */
    U0DLM = Fdiv / 256;	                //除数高8位						
    U0DLL = Fdiv % 256;                 //除数低8位
    U0LCR = 0x03;		                /* 禁止访问除数锁存*/
    U0FCR = 0x07;		                //FIFO使能，清空读写缓存

    /* 设置IRQ UART0中断对应的是VIC中断通道的中断向量6*/
    VICIntSelect = 0x00;				//所有中断通道都设置为IRQ中断
    VICVectPriority6 = 00;			    //设置中断向量4的优先级为0级	
    VICVectAddr6 = (unsigned int)IRQ_Uart0;	//设置中断向量6的中断程序地址为UART0中断程序				
    VICIntEnable = 1 << 0x06;			    //使能中断向量6，即允许串口0中断		

    U0IER = 0x07;	/* Enable UART0 interrupt */
    
}


//加入以下代码,支持printf函数	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((U0LSR&LSR_THRE)==0);//循环发送,直到发送完毕   
    U0THR = (uint8_t) ch;      
	return ch;
}
#endif 

