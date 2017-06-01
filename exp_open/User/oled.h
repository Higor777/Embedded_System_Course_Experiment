#ifndef __OELD_H
#define __OELD_H

#include "LPC23xx.H"
#include "stdint.h"




//OLED_CLK_D0  		P2.7
//OLED_MISO_D1   	P2.6
//OLED_RST       	P2.5
//OLED_MOSI_DS   	P2.4
//OLED_CS       	P2.3


#define OLED_CLK_D0(x)      do{if(x)FIO2SET=1<<7;else FIO2CLR=1<<7;}while(0);
#define OLED_MISO_D1(x)     do{if(x)FIO2SET=1<<6;else FIO2CLR=1<<6;}while(0);
#define OLED_RST(x)         do{if(x)FIO2SET=1<<5;else FIO2CLR=1<<5;}while(0);
#define OLED_MOSI_DS(x)     do{if(x)FIO2SET=1<<4;else FIO2CLR=1<<4;}while(0);
#define OLED_CS(x)          do{if(x)FIO2SET=1<<3;else FIO2CLR=1<<3;}while(0);


#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xCF

#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý

#define uint8_t uint8_t
#define uint16_t uint16_t

 
void OLED_Init(void);
void OLED_CLS(void);
void OLED_P6x8Str(uint8_t x,uint8_t y,uint8_t ch[]);
void OLED_P8x16Str(uint8_t x,uint8_t y,uint8_t ch[]);
void OLED_P14x16Str(uint8_t x,uint8_t y,uint8_t ch[]);
void OLED_Print(uint8_t x, uint8_t y, uint8_t ch[]);
void OLED_PutPixel(uint8_t x,uint8_t y);
void OLED_Rectangle(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t gif);
void OLED_Set_Pos(uint8_t x, uint8_t y);
void OLED_WrDat(uint8_t data);
void Draw_BMP(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t bmp[],uint8_t reverse);
void OLED_Fill(uint8_t dat);
void Delay_ms(uint16_t ms);

void Draw_BootPage(void);
void Draw_WaveType(uint8_t selected);
#endif
