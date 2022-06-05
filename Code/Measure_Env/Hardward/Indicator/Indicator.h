#ifndef _Indi_H
#define _Indi_H

#include "TIM_Management.h"


/*���䶨��*/
#define Inid_Port       GPIO_TypeDef*
#define Inid_Pin        uint16_t
#define Inid_State      GPIO_PinState
#define Inid_Open       GPIO_PIN_RESET
#define Inid_Off        GPIO_PIN_SET
#define Inid_period     u_Time        
#define Inid_Call_T     (99)     //������������



/*���ܶ���*/

#define Inid_DEVNormal_Low  (Inid_DEVNormal_Fast*2)
#define Inid_DEVNormal_Fast (Inid_Call_T*10)        //1����----��������״̬��ת����
#define Inid_DEVError       (Inid_Call_T*2)         //200ms----�쳣������ת����
/*
ָʾ���豸�ṹ��
*/
typedef struct Indicator_Device
{
    Inid_Port     Port;         
    Inid_Pin      Pin;          
    Inid_State    State;
    Inid_period   Period;               //ָʾ����˸����
    Inid_period   Count;                //ָʾ����˸���ڼ���
}Indicator;



extern Indicator LED1;


void Indicator_amend_Period(Indicator* IndiDEV,Inid_period Period);
void Indicator_Device_Enroll(Indicator* IndiDEV,Inid_Port Port,Inid_Pin Pin,Inid_State state,Inid_period Period);
void Indicator_Run(Indicator* IndiDEV);


#endif

