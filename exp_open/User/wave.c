#include "wave.h"
#include "math.h"


#define V_REF           3.3         //芯片的DA参考电压
#define DA_MAX_OUT      1023.0      //DA最大的输出值
#define CALL_FREQUENCY  10000.0     ///波形生成函数被调用的频率

//方波
uint32_t wave_square(float frequency,float amplitude,float offset,float duty)
{
    static float step = 1;
    static float x = 0;
    static uint32_t curdata;
    duty = duty/100.0;
    if(x <= CALL_FREQUENCY*duty)curdata = offset/V_REF*DA_MAX_OUT+amplitude/V_REF*DA_MAX_OUT;
    else if(x >= CALL_FREQUENCY) x = 0;
    else curdata = offset/V_REF*DA_MAX_OUT;
    x += step*frequency;
    if(curdata>DA_MAX_OUT)curdata = DA_MAX_OUT;
    return curdata;
}


//正弦波
#define PI              3.1415926
uint32_t wave_sin(float frequency,float amplitude,float offset)
{
    static float step = 2.0*PI;
    static float x = 0;
    static uint32_t curdata;
    curdata = offset/V_REF*DA_MAX_OUT + amplitude/V_REF*(((sin(x)+1.0)/2.0)*DA_MAX_OUT);
    x += (step*frequency)/(CALL_FREQUENCY);
    if(curdata>DA_MAX_OUT)curdata = DA_MAX_OUT;
    return curdata;
}

//三角波
uint32_t wave_triangle(float frequency,float amplitude,float offset)
{
    static float step = 1;
    static float x = 0;
    static uint32_t curdata;
    if(x <= CALL_FREQUENCY/2.0)curdata = offset/V_REF*DA_MAX_OUT+amplitude/V_REF*(x/(CALL_FREQUENCY/2))*DA_MAX_OUT;
    else if(x >= CALL_FREQUENCY) x = 0;
    else curdata = offset/V_REF*DA_MAX_OUT + amplitude/V_REF*DA_MAX_OUT - amplitude/V_REF*(x/(CALL_FREQUENCY/2)-1.0)*DA_MAX_OUT;
    x += step*frequency;
    if(curdata>DA_MAX_OUT)curdata = DA_MAX_OUT;
    return curdata;
}


//锯齿波
uint32_t wave_sawtooth(float frequency,float amplitude,float offset)
{
    static float step = 1;
    static float x = 0;
    static uint32_t curdata;
    if(x >= CALL_FREQUENCY) x = 0;
    else curdata = offset/V_REF*DA_MAX_OUT + amplitude/V_REF*(x/CALL_FREQUENCY)*DA_MAX_OUT;
    x += step*frequency;
    if(curdata>DA_MAX_OUT)curdata = DA_MAX_OUT;
    return curdata;
}

