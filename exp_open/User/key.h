#ifndef __KEY_H_
#define	__KEY_H_

#include "LPC23xx.H"
#include "stdint.h"


#define Key_1 ((~IOPIN1>>27)&0x01)
#define Key_2 ((~IOPIN1>>26)&0x01)
#define Key_3 ((~IOPIN1>>25)&0x01)
#define Key_4 ((~IOPIN1>>24)&0x01)
#define Key_5 ((~FIO2PIN>>10)&0x01)


#define Key_1_MASK	    0x01U
#define Key_1_SHIFT     0
#define Key_2_MASK 	    0x02U
#define Key_2_SHIFT     1
#define Key_3_MASK      0x04U
#define Key_3_SHIFT     2
#define Key_4_MASK 	    0x08U
#define Key_4_SHIFT     3
#define Key_5_MASK 	    0x10U
#define Key_5_SHIFT     4


#define KEY_Scan_STA_Update_MASK	0x80U



//�����ȴ�ʱ��
#define Key_KeepTime	30
//���������ʱ����
#define Key_KeepStep	5

//�Ƿ��ڶ�ʱ���ж�����ɨ�谴��IO״̬
//ɨ�谴��IO״̬Ӧÿ10msһ��
//����ͨ����ʱ����
#define USE_SCHEDULED_KEYSCAN 1



void Key_Init(void);
void Key_Scan(void);
uint8_t Key_STA(void);

#endif
