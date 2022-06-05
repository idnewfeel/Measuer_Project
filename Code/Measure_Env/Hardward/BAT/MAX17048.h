#ifndef  _MAX17048_H_
#define  _MAX17048_H_

#include "TIM_Management.h"
#include "adc.h"
#include "DEBUG.h"
#include "battery.h"

/*���䶨��*/
#define MAX17048_IIC_Address       DEV_ADDR             //MAX17048�豸��ַ
#define MAX17048_IIC_Handle        I2C_HandleTypeDef    //MAX17048��IIC���
#define MAX17048_Status            uint16_t             //MAX17048��״̬�Ĵ���
#define MAX17048_Bat_Soc           uint16_t             //��ص����ٷֱ�    
#define MAX17048_Bat_Voltage       uint16_t             //��ص�ѹ
#define MAX17048_period            u_Time          //����
#define MAX17048_Call_T            (96)           //��������
#define MAX17048_Version           uint16_t             //MAX17048�汾�Ĵ��� 

typedef enum {
	MAX17048_Init=(0),                 //MAX17048��ʼ��
    MAX17048_Online,                   //MAX17048����
    MAX17048_Offline,                  //MAX17048����
	MAX17048_Measure_ongoing,          //MAX17048���ڽ��в���
	MAX17048_Measure_completed,        //MAX17048�������
	MAX17048_Idle,          	        //MAX17048����
}MAX17048_WorkState;

typedef enum {
    MAX_Init=(MAX17048_Idle+1),
    MAX_Online,
    MAX_Offline,
    MAX_MeasureBatSoc,
    MAX_MeasureBatVol,
    MAX_MeasureCompleted,
    MAX_Idle,


}MAX17048_Run_Step;


typedef struct MAX17048x_Device
{
    MAX17048_IIC_Handle*   IIC_Net;                //IIC���߾��
    MAX17048_Bat_Soc       bat_soc;                //ת������¶�ֵ
    MAX17048_Bat_Voltage   bat_vol;                //ת�����ʪ��ֵ
    MAX17048_WorkState     WorkState;              //MAX17048����״̬
    MAX17048_Version       version;
    MAX17048_Status        Status;                 //MAX17048����״�Ĵ���
    MAX17048_period        Period;                 //MAX17048����������װ��ֵ
    MAX17048_period        Count;                  //MAX17048�������ڼ���
    MAX17048_Run_Step      Step;                   //MAX17048���в���
}MAX17048_DEV;

extern MAX17048_DEV max17048;

void Power_On_Reset(MAX17048_DEV* MAX17048);
void MAX17048_Device_Enroll(MAX17048_DEV* MAX17048,MAX17048_period Period,MAX17048_IIC_Handle*	IICNet);
MAX17048_WorkState MAX17048_Run(MAX17048_DEV* MAX17048);


#endif

