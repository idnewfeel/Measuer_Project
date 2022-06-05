#ifndef _SHT31_H
#define _SHT31_H

#include "TIM_Management.h"
#include "i2c.h"

/*-------------------------------以下内容来自盛思锐官方GitHub---------------------------------------------*/
/* all measurement commands return T (CRC) RH (CRC) */
//带时钟拉伸
// #if /*USE_SENSIRION_CLOCK_STRETCHING*/
#define SHT3X_CMD_MEASURE_HPM 0x2C06
#define SHT3X_CMD_MEASURE_MPM 0x2C0D
#define SHT3X_CMD_MEASURE_LPM 0x2C10
// #else  USE_SENSIRION_CLOCK_STRETCHING 
//不带时钟拉伸
// #define SHT3X_CMD_MEASURE_HPM 0x2400
// #define SHT3X_CMD_MEASURE_MPM 0x240B
// #define SHT3X_CMD_MEASURE_LPM 0x2416
// #endif /* USE_SENSIRION_CLOCK_STRETCHING */

#define SHT3X_HUMIDITY_LIMIT_MSK 0xFE00U
#define SHT3X_TEMPERATURE_LIMIT_MSK 0x01FFU

static const uint16_t SHT3X_CMD_READ_STATUS_REG = 0xF32D;
static const uint16_t SHT3X_CMD_CLR_STATUS_REG = 0x3041;
static const uint16_t SHT3X_CMD_READ_SERIAL_ID = 0x3780;
static const uint16_t SHT3X_CMD_DURATION_USEC = 1;           //1ms
/* read commands for the alert settings */
static const uint16_t SHT3X_CMD_READ_HIALRT_LIM_SET = 0xE11F;
static const uint16_t SHT3X_CMD_READ_HIALRT_LIM_CLR = 0xE114;
static const uint16_t SHT3X_CMD_READ_LOALRT_LIM_CLR = 0xE109;
static const uint16_t SHT3X_CMD_READ_LOALRT_LIM_SET = 0xE102;
/* write commands for the alert settings */
static const uint16_t SHT3X_CMD_WRITE_HIALRT_LIM_SET = 0x611D;
static const uint16_t SHT3X_CMD_WRITE_HIALRT_LIM_CLR = 0x6116;
static const uint16_t SHT3X_CMD_WRITE_LOALRT_LIM_CLR = 0x610B;
static const uint16_t SHT3X_CMD_WRITE_LOALRT_LIM_SET = 0x6100;


#define STATUS_OK 0
#define STATUS_ERR_BAD_DATA (-1)
#define STATUS_CRC_FAIL (-2)
#define STATUS_UNKNOWN_DEVICE (-3)
#define STATUS_ERR_INVALID_PARAMS (-4)
#define SHT3X_MEASUREMENT_DURATION_USEC 15           //15ms

/* status word macros */
#define SHT3X_IS_ALRT_PENDING(status) (((status)&0x8000U) != 0U)
#define SHT3X_IS_ALRT_RH_TRACK(status) (((status)&0x0800) != 0U)
#define SHT3X_IS_ALRT_T_TRACK(status) (((status)&0x0400U) != 0U)
#define SHT3X_IS_SYSTEM_RST_DETECT(status) (((status)&0x0010U) != 0U)
#define SHT3X_IS_LAST_CRC_FAIL(status) (((status)&0x0001U) != 0U)


/*-------------------------------以上内容来自盛思锐官方GitHub---------------------------------------------*/



/*适配定义*/
#define SHT31_IIC_Address       (0x44)<<1               //SHT31设备地址
#define SHT31_Port              GPIO_TypeDef*
#define SHT31_Pin               uint16_t
#define SHT31_IIC_Handle        I2C_HandleTypeDef       //SHT31的IIC句柄
#define SHT31_T_RAW             uint16_t
#define SHT31_RH_RAW            uint16_t     
#define SHT31_Status            uint16_t
#define SHT31_Temperature       int32_t
#define SHT31_RH                int32_t
#define SHT31_period            u_Time          //周期
#define SHT31_Call_T            (97)           //调用周期


typedef enum {
	SHT31_Init=(0),                 //SHT31初始化
    SHT31_Online,                   //SHT31在线
    SHT31_Offline,                  //SHT31离线
	SHT31_Measure_ongoing,          //SHT31正在进行测量
	SHT31_Measure_completed,        //SHT31测量完成
	SHT31_Idle,          	        //SHT31空闲

}SHT31_WorkState;


typedef enum {
	SHT_Init=(SHT31_Idle+1),
    SHT_Online,
    SHT_Offline,
    SHT_MeasureCmdSend,
    SHT_MeasureOngoing,
    SHT_MeasureCompleted,
    SHT_Idle,


}SHT31_Run_Step;


/*
SHT31设备结构体
*/
typedef struct SHT3x_Device
{
    // SHT31_Port          SDA_Port;               //SDA引脚
    // SHT31_Pin           SDA_P;                //SDA引脚
    // SHT31_Port          SCL_Port;               //SCL引脚
    // SHT31_Pin           SCL_P;                //SCL引脚
    SHT31_IIC_Handle*   IIC_Net;                //IIC总线句柄
    SHT31_T_RAW         T_RAW;                  //温度原始值
    SHT31_RH_RAW        RH_RAW;                 //湿度原始值
    SHT31_Temperature   T;                      //转换后的温度值
    SHT31_RH            RH;                     //转换后的湿度值
    SHT31_WorkState     WorkState;              //SHT31工作状态
    SHT31_Status        Status;                 //SHT31的现状寄存器
    SHT31_period        Period;                 //SHT31调用周期重装载值
    SHT31_period        Count;                  //SHT31调用周期计数
    SHT31_Run_Step      Step;                   //SHT31运行步骤
}SHT31_DEV;



extern SHT31_DEV SHT31;


unsigned char  CheckCrc(uint8_t *dat, uint8_t Num);
void SHT_Device_Enroll(SHT31_DEV* SHTDEV,SHT31_Port SDAPort,SHT31_Pin SDAPin,SHT31_Port SCLPort,SHT31_Pin SCLPin,SHT31_period Period,
						SHT31_IIC_Handle*	IICNet);
SHT31_WorkState SHT31_Run(SHT31_DEV* SHTDEV);





#endif

