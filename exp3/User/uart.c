#include "uart.h"
#include "timer.h"
#include "stdio.h"
#include "LPC23xx.H"


//UART初始化、只发不收
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

