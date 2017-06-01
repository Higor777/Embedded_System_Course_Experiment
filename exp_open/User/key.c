#include "key.h"
#include "oled.h"

volatile uint8_t KEY_Scan_STA=0;
//KEY_Scan_STA���壺
//Bit		  7		  6	  	5		  4		  3		  2	  	1		  0
//Key		���±�ʶ	NC		NC		KEY5	KEY4	KEY3	KEY2	KEY1
//1��ʾ��Ч��0��ʾ��Ч


/*********************************************
* ����IOɨ��
*********************************************/
void Key_Scan(void)
{
	static uint8_t keysta_old=0;
	uint8_t keysta_new=0x00;


	keysta_new|=Key_5;
	keysta_new=keysta_new<<1;
	keysta_new|=Key_4;
	keysta_new=keysta_new<<1;
	keysta_new|=Key_3;
	keysta_new=keysta_new<<1;
	keysta_new|=Key_2;
	keysta_new=keysta_new<<1;
	keysta_new|=Key_1;
	
#if USE_SCHEDULED_KEYSCAN==0
	
	keysta_old=keysta_new;
	keysta_new=0x00;
	
	Delay_ms(10);	//��������
    
	keysta_new|=Key_5;
	keysta_new=keysta_new<<1;
	keysta_new|=Key_4;
	keysta_new=keysta_new<<1;
	keysta_new|=Key_3;
	keysta_new=keysta_new<<1;
	keysta_new|=Key_2;
	keysta_new=keysta_new<<1;
	keysta_new|=Key_1;
#endif
	

	KEY_Scan_STA=keysta_new&keysta_old;
	
	KEY_Scan_STA|=KEY_Scan_STA_Update_MASK;		//��ӱ�ʶλ
	
	keysta_old=keysta_new;
}


/*********************************************
* ����IO��ʼ��
*********************************************/
void Key_Init(void)
{
    PINSEL10 = 0;	        //��ֹETM	 
    PINSEL3 &= 0xFF00FFFF;  //ѡ��P1.24~P1.27ΪGPIO
    IODIR1 &= 0xF0FFFFFF;   //P1.24~P1.27����
    
    PINSEL4 &= 0xFFCFFFFF;  //ѡ��P2.10ΪGPIO
    FIO2DIR &= 0xFFFFFBFF;  //P2.10����
    FIO2MASK &= 0xFFFFFBFF;
    
    
	Key_Scan();	//��ʼ��KeyUp_old,KeyDown_old
	
#if USE_SCHEDULED_KEYSCAN!=0
	Delay_ms(10);
	Key_Scan();
#endif
}




/******************************************************
*����״̬
*�����������ʵ�ֶఴ���������
******************************************************/
uint8_t Key_STA(void)
{
	static uint8_t keysta_mask=0xFF;
	static uint8_t keysta_mask_old=0xFF;
	static uint8_t keysta_cnt=0;
	
	uint8_t keysta;
//	uint8_t keysta_out;
	
#if USE_SCHEDULED_KEYSCAN==0
	
	Key_Scan();
	
#endif
	
	if(KEY_Scan_STA&0x80)
	{
		keysta=KEY_Scan_STA&0x3F;
		KEY_Scan_STA=0;
	}
	else 
		return 0;
	
	
	//���MASK
	keysta_mask|=~keysta;
	keysta_mask_old|=~keysta;
	
	//cnt����
 	if(keysta_mask&keysta)
	{
		keysta_cnt=0;
		keysta_mask_old=keysta_mask;
	}
	
	//���keysta
	if(keysta_cnt>=Key_KeepTime)
	{
		keysta&=keysta_mask_old;
		keysta_cnt-=Key_KeepStep;
	}
	else
	{
		keysta&=keysta_mask;
		keysta_cnt++;
	}
	
	//�趨MASK
	keysta_mask&=~keysta;
	
	return keysta;
}
