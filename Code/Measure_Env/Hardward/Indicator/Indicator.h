#ifndef _Indi_H
#define _Indi_H

#include "TIM_Management.h"


/*适配定义*/
#define Inid_Port       GPIO_TypeDef*
#define Inid_Pin        uint16_t
#define Inid_State      GPIO_PinState
#define Inid_Open       GPIO_PIN_RESET
#define Inid_Off        GPIO_PIN_SET
#define Inid_period     u_Time        
#define Inid_Call_T     (99)     //函数调用周期



/*功能定义*/

#define Inid_DEVNormal_Low  (Inid_DEVNormal_Fast*2)
#define Inid_DEVNormal_Fast (Inid_Call_T*10)        //1秒钟----正常工作状态反转周期
#define Inid_DEVError       (Inid_Call_T*2)         //200ms----异常工作反转周期
/*
指示灯设备结构体
*/
typedef struct Indicator_Device
{
    Inid_Port     Port;         
    Inid_Pin      Pin;          
    Inid_State    State;
    Inid_period   Period;               //指示灯闪烁周期
    Inid_period   Count;                //指示灯闪烁周期计数
}Indicator;



extern Indicator LED1;


void Indicator_amend_Period(Indicator* IndiDEV,Inid_period Period);
void Indicator_Device_Enroll(Indicator* IndiDEV,Inid_Port Port,Inid_Pin Pin,Inid_State state,Inid_period Period);
void Indicator_Run(Indicator* IndiDEV);


#endif

