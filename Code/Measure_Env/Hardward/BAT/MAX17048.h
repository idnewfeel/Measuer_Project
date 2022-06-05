#ifndef  _MAX17048_H_
#define  _MAX17048_H_

#include "TIM_Management.h"
#include "adc.h"
#include "DEBUG.h"
#include "battery.h"

/*适配定义*/
#define MAX17048_IIC_Address       DEV_ADDR             //MAX17048设备地址
#define MAX17048_IIC_Handle        I2C_HandleTypeDef    //MAX17048的IIC句柄
#define MAX17048_Status            uint16_t             //MAX17048的状态寄存器
#define MAX17048_Bat_Soc           uint16_t             //电池电量百分比    
#define MAX17048_Bat_Voltage       uint16_t             //电池电压
#define MAX17048_period            u_Time          //周期
#define MAX17048_Call_T            (96)           //调用周期
#define MAX17048_Version           uint16_t             //MAX17048版本寄存器 

typedef enum {
	MAX17048_Init=(0),                 //MAX17048初始化
    MAX17048_Online,                   //MAX17048在线
    MAX17048_Offline,                  //MAX17048离线
	MAX17048_Measure_ongoing,          //MAX17048正在进行测量
	MAX17048_Measure_completed,        //MAX17048测量完成
	MAX17048_Idle,          	        //MAX17048空闲
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
    MAX17048_IIC_Handle*   IIC_Net;                //IIC总线句柄
    MAX17048_Bat_Soc       bat_soc;                //转换后的温度值
    MAX17048_Bat_Voltage   bat_vol;                //转换后的湿度值
    MAX17048_WorkState     WorkState;              //MAX17048工作状态
    MAX17048_Version       version;
    MAX17048_Status        Status;                 //MAX17048的现状寄存器
    MAX17048_period        Period;                 //MAX17048调用周期重装载值
    MAX17048_period        Count;                  //MAX17048调用周期计数
    MAX17048_Run_Step      Step;                   //MAX17048运行步骤
}MAX17048_DEV;

extern MAX17048_DEV max17048;

void Power_On_Reset(MAX17048_DEV* MAX17048);
void MAX17048_Device_Enroll(MAX17048_DEV* MAX17048,MAX17048_period Period,MAX17048_IIC_Handle*	IICNet);
MAX17048_WorkState MAX17048_Run(MAX17048_DEV* MAX17048);


#endif

