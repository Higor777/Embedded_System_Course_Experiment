#ifndef __UI_H_
#define	__UI_H_

#include "LPC23xx.H"
#include "stdint.h"

#define ParameterName_Size 15

typedef struct tagParameterNode_Type
{
	float *exterdata;
	float step;
    float datamin;
    float datamax;
    float stepmin;
    float stepmax;
	char name[ParameterName_Size];
	struct tagParameterNode_Type *prepara;
	struct tagParameterNode_Type *nextpara;
}ParameterNode_Type, *ParameterList_Type;


static void Show_Parameter(ParameterNode_Type *para, uint8_t config);
static void Insert_ParameterNode(ParameterNode_Type *insert_node, ParameterList_Type *insert_place, ParameterNode_Type *blank_node);

void ParameterList_Init(void);
void Parameter_Change(void);

#endif
