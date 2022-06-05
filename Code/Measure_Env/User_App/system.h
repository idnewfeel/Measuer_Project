#ifndef _Sys_H
#define _Sys_H

#include "TIM_Management.h"
#include "tim.h"
#include "main.h"
#include "Indicator.h"
//#include "EnCoder.h"
#include "User_UI.h"
#include "Thumbwheel.h"
#include "beep.h"
#include "battery.h"
#include "i2c.h"
#include "SHT31.h"
#include "SGP40.h"
#include "string.h"
#include "MAX17048.h"


#define IIC_SHT     0
#define IIC_SGP     1
typedef struct SYSTEM_PARA
{
    uint16_t    SGP40MeasureInterval;    //SGP40测量间隔时间
    uint8_t     IIC_Device;              //当前占用IIC总线的设备

}PARA;

//设备UI需要显示的参数
typedef struct Device_PARA
{
    uint8_t                 IIC_State;              //IIC总线状态

    SHT31_Temperature       Temperature;            //温度值
    SHT31_RH                RH;
    SGP40_VOC               TVocIndex;
    SGP40_VOC_RAW           VocRaw;

    int16_t                 Chart_T[144];           //温度曲线缓存
    int16_t                 Chart_RH[144];
    int16_t                 Chart_TVOC[144];
    uint8_t                 Chart_Num;              //曲线当前记录点数 曲线记录最多120个点
    
    int16_t                 T_MinRange;             //Y轴温度曲线最小值
    int16_t                 RH_MinRange;
    int16_t                 TVOC_MinRange;
    int16_t                 T_MaxRange;             //Y轴温度曲线最大值
    int16_t                 RH_MaxRange;
    int16_t                 TVOC_MaxRange;

    uint8_t                 ChartUpdataFlag;        //曲线标记
    uint8_t                 X_hour;                 //
    uint16_t                Rollernum;              //滚轮选中值

    uint32_t                Bat_Minute;            //开机分钟      这个时间可用作后期做电量的精确评估

    u_Time                  Open_T;                 //开机计时      
    u_Time                  Open_Minute;
    uint16_t                Open_Sec;               //开机多少秒
    uint8_t                 Hour;                   //开机小时      
    uint8_t                 minute;                 //开机分钟

    uint32_t                SD_size;
    u_Time                  Count;

    uint32_t                BackLight;


}DEVICE_UI_PARA;

extern DEVICE_UI_PARA UI_Para;

#define POWER_ON    HAL_GPIO_WritePin(VCC_ON_GPIO_Port,VCC_ON_Pin,GPIO_PIN_SET)
#define POWER_OFF   HAL_GPIO_WritePin(VCC_ON_GPIO_Port,VCC_ON_Pin,GPIO_PIN_RESET)


void System_Init(void);
void System_Run(void);

#endif

