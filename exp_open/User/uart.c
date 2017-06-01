#include "uart.h"
#include "timer.h"
#include "stdio.h"
#include "LPC23xx.H"

volatile unsigned char redata=0; //��������

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
					/* There are errors or break interrupt *///��������д���
					/* Read LSR will clear the interrupt */
					UART0Status = LSRValue; //�������ϴ���
					Dummy = U0RBR;		/* Dummy read on RX to clear 
									interrupt, then bail out */ //ȡ����Ч����
                    Dummy=Dummy;//remove warning
					//IDISABLE;
					VICVectAddr = 0;		/* Acknowledge Interrupt */
					return;
			}
			if ( LSRValue & LSR_RDR )	/* Receive Data Ready */			
			{
					/* If no error on RLS, normal ready, save into the data buffer. */
					/* Note: read RBR will clear the interrupt */
					cdata = U0RBR; //ȡ����Ч����
					//if(cdata!=redata)
					{
							redata=cdata;
					}
			}
    }else if ( IIRValue == IIR_RDA )	/* Receive Data Available */
    {
    /* Receive Data Available *///�������ݿ���
            cdata = U0RBR; //ȡ����Ч����
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
		
	VICVectAddr = 0x00;			//֪ͨVIC�жϴ������������VIC
}


//UART��ʼ��
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

    /* ����IRQ UART0�ж϶�Ӧ����VIC�ж�ͨ�����ж�����6*/
    VICIntSelect = 0x00;				//�����ж�ͨ��������ΪIRQ�ж�
    VICVectPriority6 = 00;			    //�����ж�����4�����ȼ�Ϊ0��	
    VICVectAddr6 = (unsigned int)IRQ_Uart0;	//�����ж�����6���жϳ����ַΪUART0�жϳ���				
    VICIntEnable = 1 << 0x06;			    //ʹ���ж�����6����������0�ж�		

    U0IER = 0x07;	/* Enable UART0 interrupt */
    
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

