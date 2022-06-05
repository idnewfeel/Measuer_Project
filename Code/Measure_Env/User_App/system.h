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
    uint16_t    SGP40MeasureInterval;    //SGP40�������ʱ��
    uint8_t     IIC_Device;              //��ǰռ��IIC���ߵ��豸

}PARA;

//�豸UI��Ҫ��ʾ�Ĳ���
typedef struct Device_PARA
{
    uint8_t                 IIC_State;              //IIC����״̬

    SHT31_Temperature       Temperature;            //�¶�ֵ
    SHT31_RH                RH;
    SGP40_VOC               TVocIndex;
    SGP40_VOC_RAW           VocRaw;

    int16_t                 Chart_T[144];           //�¶����߻���
    int16_t                 Chart_RH[144];
    int16_t                 Chart_TVOC[144];
    uint8_t                 Chart_Num;              //���ߵ�ǰ��¼���� ���߼�¼���120����
    
    int16_t                 T_MinRange;             //Y���¶�������Сֵ
    int16_t                 RH_MinRange;
    int16_t                 TVOC_MinRange;
    int16_t                 T_MaxRange;             //Y���¶��������ֵ
    int16_t                 RH_MaxRange;
    int16_t                 TVOC_MaxRange;

    uint8_t                 ChartUpdataFlag;        //���߱��
    uint8_t                 X_hour;                 //
    uint16_t                Rollernum;              //����ѡ��ֵ

    uint32_t                Bat_Minute;            //��������      ���ʱ������������������ľ�ȷ����

    u_Time                  Open_T;                 //������ʱ      
    u_Time                  Open_Minute;
    uint16_t                Open_Sec;               //����������
    uint8_t                 Hour;                   //����Сʱ      
    uint8_t                 minute;                 //��������

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

