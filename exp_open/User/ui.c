#include "ui.h"
#include "key.h"
#include "oled.h"
#include <stdio.h>

float Temp_Para=450;

float Template_para = 0;
ParameterNode_Type P_Ctrl[20];

extern uint8_t wave_type;
extern float amplitude;
extern float frequency;
extern float offset;
extern float duty;
void ParameterList_Init(void)
{
	ParameterNode_Type node;
	ParameterNode_Type *blank_node;
	ParameterList_Type insert_place=0;
	blank_node=P_Ctrl;
	
	
	node.exterdata=&(frequency);
	node.step=1;
    node.datamin = 0.1;
    node.datamax = 8000;
    node.stepmin = 0.1;
    node.stepmax = 1000;
	sprintf(node.name,"frequency"); 
	Insert_ParameterNode(&node,&insert_place,blank_node++);
    
    node.exterdata=&(amplitude);
	node.step=1;
    node.datamin = 0.0;
    node.datamax = 3.3;
    node.stepmin = 0.1;
    node.stepmax = 1;
	sprintf(node.name,"amplitude"); 
	Insert_ParameterNode(&node,&insert_place,blank_node++);

    node.exterdata=&(offset);
	node.step=1;
    node.datamin = 0.0;
    node.datamax = 3.3;
    node.stepmin = 0.1;
    node.stepmax = 1;
	sprintf(node.name,"offset"); 
	Insert_ParameterNode(&node,&insert_place,blank_node++);
    
    node.exterdata=&(duty);
	node.step=1;
    node.datamin = 0;
    node.datamax = 100;
    node.stepmin = 0.1;
    node.stepmax = 10;
	sprintf(node.name,"duty"); 
	Insert_ParameterNode(&node,&insert_place,blank_node++);
	Show_Parameter(P_Ctrl,0x01|0x02|0x04);
}


void Parameter_Change(void)
{
	static ParameterNode_Type* para=P_Ctrl;
    static uint8_t Para_type = 0,cnt_flag=0;
    static char str[15];
	uint8_t keysta;
	keysta=Key_STA();

	if(keysta&Key_1_MASK)
	{
        wave_type = (wave_type+1)%4;
        Draw_WaveType(wave_type);
	}
	
	if(keysta&Key_2_MASK)
	{
        para=para->nextpara;
        Show_Parameter(para,0x01|0x02|0x04);
	}
	
	if(keysta&Key_3_MASK)
	{
        if(Para_type==0)
        {
            *(para->exterdata)-=para->step;
            if(*(para->exterdata)<para->datamin)*(para->exterdata)=para->datamin;
        }else
        {
            para->step/=10.0;
            if(para->step<para->stepmin)para->step=para->stepmin;
        }
		Show_Parameter(para,0x02|0x04);
	}
	
	if(keysta&Key_4_MASK)
	{
		if(Para_type==0)
        {
            *(para->exterdata)+=para->step;
            if(*(para->exterdata)>para->datamax)*(para->exterdata)=para->datamax;
        }else
        {
            para->step*=10.0;
            if(para->step>para->stepmax)para->step=para->stepmax;
        }
		Show_Parameter(para,0x02|0x04);
	}
    
    if(keysta&Key_5_MASK)
	{
        if(Para_type==0)
        {
            Para_type = 1;
        }else
        {
            Para_type = 0;
        }
	}
    
    
    if(Para_type==0)
    {
        if(cnt_flag>10)
        {
            cnt_flag = 0;
            OLED_Print(0,3,(uint8_t *)"          "); 
        }else
        {
            cnt_flag++;
            sprintf(str,"%-9.1f",*(para->exterdata));
            OLED_Print(0,3,(uint8_t *)str); 
        } 
    }else
    {
        if(cnt_flag>10)
        {
            cnt_flag = 0;
            OLED_Print(80,3,(uint8_t *)"      "); 
        }else
        {
            cnt_flag++;
            sprintf(str,"%-6.1f",para->step);
            OLED_Print(80,3,(uint8_t *)str); 
        } 
    }
}

//config
//bit0:	显示参数名
//bit1:	显示参数
//bit2:	显示步进值
void Show_Parameter(ParameterNode_Type *para, uint8_t config)
{
	char str[10];
	
	//显示参数名
	if(config&0x01)
	{
		sprintf(str,"%-9s",para->name);
        OLED_Print(0,1,(uint8_t *)str); 
        sprintf(str,"step");
		OLED_Print(80,1,(uint8_t *)str); 
	}
	//显示参数
	if(config&0x02)
	{
		sprintf(str,"%-9.1f",*(para->exterdata));
		OLED_Print(0,3,(uint8_t *)str);  
	}
	//显示步进值
	if(config&0x04)
	{
		sprintf(str,"%-6.1f",para->step);
		OLED_Print(80,3,(uint8_t *)str);  
	}
}


//在insert_place节点后插入新节点,并使insert_place指向新插入的节点
static void Insert_ParameterNode(ParameterNode_Type *insert_node, ParameterList_Type *insert_place, ParameterNode_Type *blank_node)
{
    uint8_t i = 0;
	//复制数据
	blank_node->exterdata=insert_node->exterdata;
	for(i=0;i<ParameterName_Size;i++)
	{
		blank_node->name[i]=insert_node->name[i];
	}
	blank_node->step=insert_node->step;
    blank_node->datamin=insert_node->datamin;
    blank_node->datamax=insert_node->datamax;
    blank_node->stepmin=insert_node->stepmin;
    blank_node->stepmax=insert_node->stepmax;
	
	//插入节点
	if((*insert_place)!=0)
	{
		blank_node->nextpara=(*insert_place)->nextpara;
		((*insert_place)->nextpara)->prepara=blank_node;
		(*insert_place)->nextpara=blank_node;
		blank_node->prepara=(*insert_place);
	}
	else
	{
		blank_node->nextpara=blank_node;
		blank_node->prepara=blank_node;
	}
	(*insert_place)=blank_node;
}
