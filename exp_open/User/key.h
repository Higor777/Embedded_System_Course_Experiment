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



//连按等待时间
#define Key_KeepTime	30
//连按输出的时间间隔
#define Key_KeepStep	5

//是否在定时器中断里面扫描按键IO状态
//扫描按键IO状态应每10ms一次
//避免通过延时消抖
#define USE_SCHEDULED_KEYSCAN 1



void Key_Init(void);
void Key_Scan(void);
uint8_t Key_STA(void);

#endif
