#include "uart.h"
#include "timer.h"
#include "stdio.h"
#include "LPC23xx.H"


//UART��ʼ����ֻ������
void UART_Init(uint32_t baudrate)
{
    uint32_t Fdiv;

    PINSEL10 = 0;		 //��ֹETM

    PINSEL0 = (PINSEL0&0xFFFFFF0F)|0x00000050;               //RxD0 and TxD0 
    U0LCR = 0x83;		                //8 bits, no Parity, 1 Stop bit ������ʳ�������
    Fdiv = ( Fpclk / 16 ) / baudrate ;	/*baud rate */
    U0DLM = Fdiv / 256;	                //������8λ						
    U0DLL = Fdiv % 256;                 //������8λ
    U0LCR = 0x03;		                /* ��ֹ���ʳ�������*/
    U0FCR = 0x07;		                //FIFOʹ�ܣ���ն�д����
}


//�������´���,֧��printf����	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((U0LSR&LSR_THRE)==0);//ѭ������,ֱ���������   
    U0THR = (uint8_t) ch;      
	return ch;
}
#endif 

