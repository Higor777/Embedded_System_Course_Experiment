#include <stdlib.h>
#include <stdio.h>
#include "LPC23xx.H"
#define NUM 100

unsigned int data[NUM];
unsigned int sorted[NUM];
unsigned int index[NUM];

int main (void) {
 	
	unsigned int n;
	int i,j,swaped;
    //生成100位0-100的随机数
	for(n=0;n<NUM;n++)
	{
		data[n]=rand()%(NUM+1);	
		sorted[n] = data[n];
		index[n] = n;
	}
	//对随机数进行排序，同时记录排序后数据在原数据中的位置
	for(i=NUM;i>1;i--)
	{
		swaped = 0;
		for(j=0;j<i-1;j++)
		{
			if(sorted[j]>sorted[j+1])
			{
				sorted[j] += sorted[j+1];
				sorted[j+1] = sorted[j]-sorted[j+1];
				sorted[j] -= sorted[j+1];
				index[j] += index[j+1];
				index[j+1] = index[j]-index[j+1];
				index[j] -= index[j+1];
				swaped = 1;
			}
		}
		if(swaped==0)break;
	}
	while (1);	
}
