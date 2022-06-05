#include "MAX17048.h" 

/**
 *  @file Voltameter_Port.c
 *
 *  @date 2021-03-04
 *
 *  @author aron566
 *
 *  @copyright Copyright (c) 2021 aron566 <aron566@163.com>.
 *
 *  @brief 电池电量监控接口
 *
 *  @details 1、SCL RISE MIN KEEP 20ns
 *           2、SCL FALL MIN KEEP 20ns
 *           3、写： S. SAddr W. A. MAddr. A. Data0. A. Data1. A. P
 *           4、读： 先写S. SAddr W. A. MAddr. A 再读 Sr. SAddr R. A. Data0. A. Data1. N. P
 *           5、使用Fastmode 最高速率400Khz
 *
 *  @version V1.0
 */
#ifdef __cplusplus ///<use C compiler
extern "C" {
#endif
/** Includes -----------------------------------------------------------------*/
/* Private includes ----------------------------------------------------------*/
#include "main.h"
// #include "Voltameter_Port.h"
/** Private typedef ----------------------------------------------------------*/
/** Private macros -----------------------------------------------------------*/
#define ENABLE_MAX17048_DEBUG   1/**< 启动打印调试*/
/*MAX17048设备I2C地址*/
#define DEV_ADDR                0x6C
/*MAX17048设备I2C写操作地址*/
#define DEV_ADDR_WRITE          (DEV_ADDR|0x00)
/*MAX17048设备I2C读操作地址*/
#define DEV_ADDR_READ           (DEV_ADDR|0x01)

/*MAX17048寄存器地址*/
#define REG_V_CELL              0x02
#define REG_SOC                 0x04
#define REG_MODE                0x06
#define REG_VERSION             0x08
#define REG_HIBRT               0x0A
#define REG_CONFIG              0x0C
#define REG_VALRT               0x14
#define REG_CRATE               0x16
#define REG_V_RESET             0x18
#define REG_STATUS              0x1A
        
#define REG_TABLE               0x40/**< REG RANGE:0x40 to 0x70*/
#define REG_TABLE_END           0x70
        
#define REG_CMD                 0xFE
        
/*16BIT位*/        
#define REG_BIT0                (1U<<0)
#define REG_BIT1                (1U<<1)
#define REG_BIT2                (1U<<2)
#define REG_BIT3                (1U<<3)
#define REG_BIT4                (1U<<4)
#define REG_BIT5                (1U<<5)
#define REG_BIT6                (1U<<6)
#define REG_BIT7                (1U<<7)
#define REG_BIT8                (1U<<8)
#define REG_BIT9                (1U<<9)
#define REG_BIT10               (1U<<10)
#define REG_BIT11               (1U<<11)
#define REG_BIT12               (1U<<12)
#define REG_BIT13               (1U<<13)
#define REG_BIT14               (1U<<14)
#define REG_BIT15               (1U<<15)
/** Private constants --------------------------------------------------------*/
/** Public variables ---------------------------------------------------------*/

/** Private variables --------------------------------------------------------*/
static uint16_t Battery_Soc = 0;/**< 电池电量百分比*/
static uint16_t Battery_Voltage = 0;/**< 电池电压*/
static uint8_t Send_Val_Buf[2];
static uint8_t Reg_Val_Buf[2];
/** Private function prototypes ----------------------------------------------*/
#if ENABLE_MAX17048_DEBUG
static void Display_Alarm_Info(uint8_t Alarm_Value);
#endif

static uint16_t Read_Vcell_Update(MAX17048_DEV* MAX17048,uint32_t Block_Time);
static uint16_t Read_Soc_Update(MAX17048_DEV* MAX17048,uint32_t Block_Time);
/** Private user code --------------------------------------------------------*/

MAX17048_DEV max17048;

/** Private application code -------------------------------------------------*/
/*******************************************************************************
*
*       Static code
*
********************************************************************************
*/


/**
  ******************************************************************
  * @brief   MAX17048 报警信息打印
  * @param   [in]None.
  * @return  None.
  * @author  aron566
  * @version V1.0
  * @date    2021-03-08
  ******************************************************************
  */
#if ENABLE_MAX17048_DEBUG
static void Display_Alarm_Info(uint8_t Alarm_Value)
{
  if(Alarm_Value & REG_BIT0)
  {
    Debug("POWER ON IC NO CONFIG.\r\n");
  }
  if(Alarm_Value & REG_BIT1)
  {
    Debug("VCELL HIGH THAN ALRT.VALRTMAX.\r\n");
  }
  if(Alarm_Value & REG_BIT2)
  {
    Debug("VCELL LOW THAN ALRT.VALRTMIN.\r\n");
  }
  if(Alarm_Value & REG_BIT3)
  {
    Debug("VOLTAGE RESET.\r\n");
  }
  if(Alarm_Value & REG_BIT4)
  {
    Debug("SOC LOW THAN CONFIG.ATHD.\r\n");
  }
  if(Alarm_Value & REG_BIT5)
  {
    Debug("SOC CHANGE VALUE ARRIVE %%1.\r\n");
  }
  if(Alarm_Value & REG_BIT6)
  {
    Debug("ENABLE VOLTAGE RESET ALARM.\r\n");
  }
}
#endif
/**
  ******************************************************************
  * @brief   MAX17048 上电复位
  * @param   [in]None.
  * @return  None.
  * @author  aron566
  * @version V1.0
  * @date    2021-03-08
  ******************************************************************
  */
void Power_On_Reset(MAX17048_DEV* MAX17048)
{
  /*复位上电*/
  uint8_t WriteData[3] = {REG_CMD, 0x54, 0x00};
  HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, WriteData, 3, 100);
  
  /*Wait*/
  HAL_Delay(100);
  
  /*快速启动*/
  WriteData[0] = REG_MODE;
  WriteData[1] = 0x00;
  WriteData[2] |= REG_BIT6;

  /*使能休眠模式*/
  WriteData[2] |= REG_BIT5;
  HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, WriteData, 3, 100);
}

/**
  ******************************************************************
  * @brief   清除MAX17048 报警状态
  * @param   [in]None.
  * @return  None.
  * @author  aron566
  * @version V1.0
  * @date    2021-03-04
  ******************************************************************
  */
static void Alarm_State_Reset(MAX17048_DEV* MAX17048)
{
  uint8_t RegData = 0;
  uint8_t RecData[2] = {0};
  uint8_t SendData[3] = {0};
  
  /*读取报警状态信息*/
  RegData = REG_STATUS;
  HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, &RegData, 1, 100);
  HAL_I2C_Master_Receive(MAX17048->IIC_Net, DEV_ADDR_READ, RecData, 2, 100);
#if ENABLE_MAX17048_DEBUG  
  Debug("Status REG:%02X:VAL:%02X%02X.\r\n", RegData, RecData[0], RecData[1]);
  Display_Alarm_Info(RecData[0]);
#endif
  /*清除报警信息*/
  SendData[0] = RegData;
  SendData[1] = (RecData[0]&(~0x7F));
  SendData[2] = RecData[1];
  HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, SendData, 3, 100);
#if ENABLE_MAX17048_DEBUG  
  Debug("Set Status REG:%02X:VAL:%02X%02X.\r\n", RegData, SendData[1], SendData[2]);
#endif


  HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, &RegData, 1, 100);
  HAL_I2C_Master_Receive(MAX17048->IIC_Net, DEV_ADDR_READ, RecData, 2, 100);
#if ENABLE_MAX17048_DEBUG    
  Debug("After Status REG:%02X:VAL:%02X%02X.\r\n", RegData, RecData[0], RecData[1]);
#endif

  MAX17048->Status = ((RecData[0]<<8)|RecData[1]);


  /*读取配置信息*/
  RegData = REG_CONFIG;
  HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, &RegData, 1, 100);
  HAL_I2C_Master_Receive(MAX17048->IIC_Net, DEV_ADDR_READ, RecData, 2, 100);
#if ENABLE_MAX17048_DEBUG  
  Debug("Config REG:%02X:VAL:%02X%02X.\r\n", RegData, RecData[0], RecData[1]);
#endif
  /*设置报警阈值 BIT0-4 可设范围1-32% 设置10%则32-10*/
  RecData[1] = ((RecData[1]&0xE0)|(32-10));
  /*清除报警状态位 BIT5*/
  RecData[1] &= (~REG_BIT5);
  SendData[0] = RegData;
  SendData[1] = RecData[0];
  SendData[2] = RecData[1];
  HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, SendData, 3, 100);
#if ENABLE_MAX17048_DEBUG  
  Debug("Set Config REG:%02X:VAL:%02X%02X.\r\n", RegData, SendData[1], SendData[2]);
#endif

  HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, &RegData, 1, 100);
  HAL_I2C_Master_Receive(MAX17048->IIC_Net, DEV_ADDR_READ, RecData, 2, 100);
#if ENABLE_MAX17048_DEBUG    
  Debug("After Config REG:%02X:VAL:%02X%02X.\r\n", RegData, RecData[0], RecData[1]);
#endif

  /*读取版本信息*/

  RegData = REG_VERSION;
  HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, &RegData, 1, 100);
  HAL_I2C_Master_Receive(MAX17048->IIC_Net, DEV_ADDR_READ, RecData, 2, 100);

#if ENABLE_MAX17048_DEBUG  
  Debug("Version REG:%02X:VAL:%02X%02X.\r\n", RegData, RecData[0], RecData[1]);
#endif
  MAX17048->version = ((RecData[0]<<8)|RecData[1]);

  if(MAX17048->version!=0 && MAX17048->Status!=0)
  {
    MAX17048->WorkState = MAX17048_Online;
  }
  else
  {
    MAX17048->WorkState = MAX17048_Offline;
  }

}

/**
  ******************************************************************
  * @brief   读取MAX17048 Vcell电压数值 78.125uV/Vcell
  * @param   [in]Block_Time 阻塞读取时间
  * @return  电量数据
  * @author  aron566
  * @version V1.0
  * @date    2021-03-04
  ******************************************************************
  */
static uint16_t Read_Vcell_Update(MAX17048_DEV* MAX17048,uint32_t Block_Time)
{
  Send_Val_Buf[0] = REG_V_CELL;

    if(HAL_OK != HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, Send_Val_Buf, 1, Block_Time))
    {
      return 333;
    }
    if(HAL_OK != HAL_I2C_Master_Receive(MAX17048->IIC_Net, DEV_ADDR_READ, Reg_Val_Buf, 2, Block_Time))
    {
      return 333;
    }
    
    Battery_Voltage = (Reg_Val_Buf[0]<<8)+Reg_Val_Buf[1];
    Battery_Voltage = (uint16_t)(((double)Battery_Voltage * 78.125)/1000);//mV
    return Battery_Voltage;

}

/**
  ******************************************************************
  * @brief   读取MAX17048 SOC(Battery state of charge)电量数值 1%/256
  * @param   [in]Block_Time 阻塞读取时间
  * @return  电量数据
  * @author  aron566
  * @version V1.0
  * @date    2021-03-04
  ******************************************************************
  */
static uint16_t Read_Soc_Update(MAX17048_DEV* MAX17048,uint32_t Block_Time)
{
  Send_Val_Buf[0] = REG_SOC;

    if(HAL_OK != HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, Send_Val_Buf, 1, Block_Time))
    {
      return 333;
    }
    if(HAL_OK != HAL_I2C_Master_Receive(MAX17048->IIC_Net, DEV_ADDR_READ, Reg_Val_Buf, 2, Block_Time))
    {
      return 333;
    }
    uint16_t Battery_Soc_Temp = (Reg_Val_Buf[0]<<8) + Reg_Val_Buf[1];
    Battery_Soc_Temp /= 256;
    Battery_Soc = Battery_Soc_Temp > 100?100:Battery_Soc_Temp;
    return Battery_Soc;

}

/** Public application code --------------------------------------------------*/
/*******************************************************************************
*
*       Public code
*
********************************************************************************
*/
// /**
//   ******************************************************************
//   * @brief   I2C发送完成回调
//   * @param   [in]None.
//   * @return  None.
//   * @author  aron566
//   * @version V1.0
//   * @date    2021-03-04
//   ******************************************************************
//   */


// /**
//   ******************************************************************
//   * @brief   I2C接收完成回调
//   * @param   [in]None.
//   * @return  None.
//   * @author  aron566
//   * @version V1.0
//   * @date    2021-03-04
//   ******************************************************************
//   */
// void Voltameter_Port_I2C_MasterRxCpltCallback(void)
// {
//   /*TODO:UPDATE VAL*/
//   if(Send_Val_Buf[0] == REG_V_CELL)
//   {
//     uint16_t Battery_Voltage_Temp = (Reg_Val_Buf[0]<<8)+Reg_Val_Buf[1];
//     Battery_Voltage_Temp = (uint16_t)(((double)Battery_Voltage_Temp * 78.125)/1000000);
//     Battery_Voltage = Battery_Voltage_Temp;
//   }
//   else if(Send_Val_Buf[0] == REG_SOC)
//   {
//     uint16_t Battery_Soc_Temp = (Reg_Val_Buf[0]<<8) + Reg_Val_Buf[1];
//     Battery_Soc_Temp /= 256;
//     Battery_Soc = Battery_Soc_Temp > 100?100:Battery_Soc_Temp;
//   }
// }

/**
  ******************************************************************
  * @brief   获取电池电量及电压信息
  * @param   [in]None
  * @return  电量数据
  * @author  aron566
  * @version V1.0
  * @date    2021-03-04
  ******************************************************************
  */
// uint16_t Voltameter_Port_Get_Battery_Electric_Quantity(void)
// {
//   Read_Soc_Update(100);
//   Read_Vcell_Update(100);
//   return Battery_Soc;
// }

/**
  ******************************************************************
  * @brief   获取电池充电状态
  * @param   [in]None
  * @return  1 为充电状态
  * @author  aron566
  * @version V1.0
  * @date    2021-03-04
  ******************************************************************
  */
// uint8_t Voltameter_Port_Get_Battery_Charge_State(void)
// {
//   // if(HAL_GPIO_ReadPin(BAT_STAT_GPIO_Port, BAT_STAT_Pin) == GPIO_PIN_SET)
//   // {
//      return 1;
//   // }
//   // else
//   // {
//   //   return 0;
//   // }
// }

/**
  ******************************************************************
  * @brief   MAX17048 休眠设置
  * @param   [in]Sleep_En 睡眠使能.
  * @return  None.
  * @author  aron566
  * @version V1.0
  * @date    2021-07-07
  ******************************************************************
  */
 #include "stdbool.h"
void Voltameter_Port_OnOff_Sleep(MAX17048_DEV* MAX17048 , bool Sleep_En)
{ 
  uint8_t RegData = 0;
  uint8_t RecData[2] = {0};
  uint8_t SendData[3] = {0};

  /*读取配置信息*/
  RegData = REG_CONFIG;
  HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, &RegData, 1, 100);
  HAL_I2C_Master_Receive(MAX17048->IIC_Net, DEV_ADDR_READ, RecData, 2, 100);
#if ENABLE_MAX17048_DEBUG  
  Debug("Config REG:%02X:VAL:%02X%02X.\r\n", RegData, RecData[0], RecData[1]);
#endif

  SendData[1] = RegData;
  SendData[1] = RecData[0];
  SendData[2] = RecData[1];

  if(Sleep_En == true)
  {
    /*进入休眠 config.sleep = 1*/
    SendData[1] |= REG_BIT7;
  }
  else
  {
    /*退出休眠 config.sleep = 0*/
    SendData[1] &= ~REG_BIT7;
  }

  HAL_I2C_Master_Transmit(MAX17048->IIC_Net, DEV_ADDR_WRITE, SendData, 3, 100);
}

/**
  ******************************************************************
  * @brief   电池监控接口初始化
  * @param   [in]None
  * @return  None.
  * @author  aron566
  * @version V1.0
  * @date    2021-03-04
  ******************************************************************
  */
void Voltameter_Port_Init(MAX17048_DEV* MAX17048)
{
  /*上电复位MAX17048*/
  // Power_On_Reset(MAX17048);
  
  /*报警复位*/
  Alarm_State_Reset(MAX17048);
}



void MAX17048_Device_Enroll(MAX17048_DEV* MAX17048,MAX17048_period Period,MAX17048_IIC_Handle*	IICNet)
{

	MAX17048->IIC_Net		=	IICNet;	

	MAX17048->bat_soc   =	0;
	MAX17048->bat_vol   =	0;
	MAX17048->WorkState	=	MAX17048_Init;		
	MAX17048->Status		=	0;
  MAX17048->version   = 0;
	MAX17048->Period 		=	Period; 
	MAX17048->Count		  =	Period;
	MAX17048->Step		  =	MAX_Init;


}


MAX17048_WorkState MAX17048_Run(MAX17048_DEV* MAX17048)
{

	if (MAX17048->Count<=0)
	{
		switch (MAX17048->Step)
		{
			/*初始化完成，查询设备是否在线*/
			case MAX_Init:
				Voltameter_Port_Init(MAX17048);
				if(MAX17048->WorkState==MAX17048_Online)//设备在线
				{
					MAX17048->Step = MAX_MeasureBatSoc;
          MAX17048->WorkState = MAX17048_Measure_ongoing;
				}
				else if (MAX17048->WorkState==MAX17048_Offline)
				{
					MAX17048->Step = MAX_Offline;
				}
			break;

			/*设备处于在线状态--*/
			case MAX_Online:
				MAX17048->Step = MAX_MeasureBatSoc;
			break;

			/*开始测量电池电量*/  
			case MAX_MeasureBatSoc:
        MAX17048->bat_soc = Read_Soc_Update(MAX17048,100);
        MAX17048->Step = MAX_MeasureBatVol;
			break;

			/*开始测量电池电压*/
			case MAX_MeasureBatVol:
        MAX17048->bat_vol = Read_Vcell_Update(MAX17048,100);
        MAX17048->Step = MAX_Idle;
        MAX17048->WorkState = MAX17048_Idle;
			break;


			/*设备处于空闲状态*/
			case MAX_Idle:
        Battery_Conversion();//电池电压赋值
				MAX17048->Step = MAX_MeasureBatSoc;
				MAX17048->WorkState = MAX17048_Measure_ongoing;
			break;	

			/*设备处于离线状态*/
			case MAX_Offline:
        MAX17048->Step = MAX_Init;
        Debug("error:MAX17048 不在线\r\n");
			break;

			default:
			break;
		}

		Set_Time(&MAX17048->Count,MAX17048->Period);	//重装载 闪烁周期计数变量
	}	

	return MAX17048->WorkState;
}







#ifdef __cplusplus ///<end extern c
}
#endif
/******************************** End of file *********************************/

