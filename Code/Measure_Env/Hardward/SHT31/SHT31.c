


#include "SHT31.h"

SHT31_DEV SHT31;

 /*******************************************************************************
* @FunctionName   : CheckCrc
* @Description    : CRC数据校验
* @Input          : uint8_t *dat---数据地址, uint8_t Num---校验数据数量
* @Output         : 
* @Return         : CRC值
*******************************************************************************/
unsigned char  CheckCrc(uint8_t *dat, uint8_t Num)
{
uint8_t i,byte,crc=0xFF;
  for(byte=0; byte<Num; byte++)
  {
    crc^=(dat[byte]);
    for(i=0;i<8;i++)
    {
      if(crc & 0x80) crc=(crc<<1)^0x31;
      else crc=(crc<<1);
    }
  }
	return crc;
}




 /*******************************************************************************
* @Function Name  : MYI2C_READ_FUNC
* @Description    : 硬件IIC写入 数据
* @Input          : DEVICE_T*	Dev_Obj---IIC设备句柄,unsigned char device_addr---设备地址,char register_addr---寄存器地址
										unsigned char *pDATA---数据缓存地址, unsigned char len---数据长度
* @Output         : 
* @Return         :sucess=0 ,fail=1
*******************************************************************************/
unsigned char MYI2C_WRITE_FUNC(SHT31_DEV* SHTDEV,unsigned char device_addr,uint16_t register_addr,unsigned char* write_data,unsigned char Writelen)
{	
	uint8_t i = 0;
	uint8_t	reg[10] =	{0};
	uint8_t writeLEN	=	0;
		reg[0]	=	(uint8_t)((register_addr&0xFF00)>>8);
		reg[1]	=	(uint8_t)(register_addr&0x00FF);	
		if (Writelen!=0)
		{
			for(i=0;i<Writelen;i++)
			{
				reg[2+i] = write_data[i];
			}
		}
		writeLEN = Writelen+2;
	if(HAL_I2C_Master_Transmit(SHTDEV->IIC_Net,device_addr, reg, Writelen,1000) != HAL_OK)	
	{
		return 1;
	}
	return 0 ;
}

 /*******************************************************************************
* @Function Name  : MYI2C_READ_FUNC
* @Description    : 硬件IIC读取数据，不需要等待的
* @Input          : DEVICE_T*	Dev_Obj---IIC设备句柄,unsigned char device_addr---设备地址,char register_addr---寄存器地址
										unsigned char *pDATA---数据缓存地址, unsigned char len---数据长度
* @Output         : 
* @Return         :sucess=0 ,fail=1
*******************************************************************************/
unsigned char MYI2C_READ_FUNC(SHT31_DEV* SHTDEV,unsigned char device_addr,uint16_t register_addr,unsigned char *pDATA, unsigned char len)
{
	uint8_t	reg[10] =	{0};
	
		reg[0]	=	(uint8_t)((register_addr&0xFF00)>>8);
		reg[1]	=	(uint8_t)(register_addr&0x00FF);

		if(HAL_I2C_Master_Transmit(SHTDEV->IIC_Net,device_addr, reg, 2,1000)!=HAL_OK)
		{
			return 1;
		}
		
		if(HAL_I2C_Master_Receive(SHTDEV->IIC_Net,device_addr,pDATA,len,1000) != HAL_OK)
		{
			return 1;
		}
		return 0;

		
}

/*******************************************************************************
* @FunctionName   : SHT_Check_Online
* @Description    : SHT31检查是否在线
* @Input          : SHTDEV----设备结构体 
* @Output         : 
* @Return         : None
*******************************************************************************/
static void SHT_Check_Online(SHT31_DEV* SHTDEV )
{
	
	uint8_t data[3] = {0};
	if(MYI2C_READ_FUNC(SHTDEV,SHT31_IIC_Address,SHT3X_CMD_READ_STATUS_REG,data, 3)==0)
	{
		/*通讯成功*/
		if((CheckCrc(data,2)	==	data[2]))	//数据校验正确
		{
			SHTDEV->Status = ((data[0]<<8)|data[1]);
			SHTDEV->WorkState = SHT31_Online;
		}
		else SHTDEV->WorkState = SHT31_Offline;
	}
	else SHTDEV->WorkState = SHT31_Offline;
}

 /*******************************************************************************
* @FunctionName   : SHT_Device_Enroll
* @Description    : 将SHT31属性注册到设备结构体z中
* @Input          : SHTDEV----设备结构体  	SDAPort----设备IIC接口引脚		SDAPin -----设备IIC接口引脚
*					status------设备状态	Period----调用周期				IICNet-----设备的IIC总线句柄
* @Output         : 
* @Return         : None
*******************************************************************************/
void SHT_Device_Enroll(SHT31_DEV* SHTDEV,SHT31_Port SDAPort,SHT31_Pin SDAPin,SHT31_Port SCLPort,SHT31_Pin SCLPin,SHT31_period Period,
						SHT31_IIC_Handle*	IICNet)
{
	// SHTDEV->SDA_Port 	= 	SDAPort;
	// SHTDEV->SDA_P		=	SDAPin;
	// SHTDEV->SCL_Port 	= 	SCLPort;
	// SHTDEV->SCL_P		=	SCLPin;
	SHTDEV->IIC_Net		=	IICNet;	
	SHTDEV->T_RAW		=	0;
	SHTDEV->RH_RAW		=	0;
	SHTDEV->T			=	0;
	SHTDEV->RH			=	0;
	SHTDEV->WorkState	=	SHT31_Init;		//SHT31初始化
	SHTDEV->Status		=	0;
	SHTDEV->Period 		=	Period; 
	SHTDEV->Count		=	Period;
	SHTDEV->Step		=	SHT_Init;


}

 /*******************************************************************************
* @FunctionName   : tick_to_temperature
* @Description    : 原始值和温度值的互转函数
* @Input          : tick---AD原始值  
* @Output         : temperature---转换后的温度值 humidity---转换后的湿度值
* @Return         : 
*******************************************************************************/
void tick_to_temperature(uint16_t tick, int32_t* temperature) {
    *temperature = ((21875 * (int32_t)tick) >> 13) - 45000;
}

void tick_to_humidity(uint16_t tick, int32_t* humidity) {
    *humidity = ((12500 * (int32_t)tick) >> 13);
}

void temperature_to_tick(int32_t temperature, uint16_t* tick) {
    *tick = (uint16_t)((temperature * 12271 + 552195000) >> 15);
}

void humidity_to_tick(int32_t humidity, uint16_t* tick) {
    *tick = (uint16_t)((humidity * 21474) >> 15);
}


 /*******************************************************************************
* @FunctionName   : SHT31_Run
* @Description    : SHT31传感器运行设备运行函数
* @Input          : SHTDEV----设备结构体
* @Output         : 
* @Return         : SHT31_WorkState   传感器的工作状态
*******************************************************************************/

SHT31_WorkState SHT31_Run(SHT31_DEV* SHTDEV)
{
uint8_t temp[6] = {0};	
	if (SHTDEV->Count<=0)
	{
		switch (SHTDEV->Step)
		{
			/*初始化完成，查询设备是否在线*/
			case SHT_Init:
				SHT_Check_Online(SHTDEV);
				if(SHTDEV->WorkState==SHT31_Online)//设备在线
				{
					SHTDEV->Step = SHT_MeasureCmdSend;
				}
				else if (SHTDEV->WorkState==SHT31_Offline)
				{
					SHTDEV->Step = SHT_Offline;
				}
				break;

			/*设备处于在线状态--*/
			case SHT_Online:
				SHTDEV->Step = SHT_MeasureCmdSend;
				break;

			/*发送测量命令*/  //可尝试STM32的时钟拉升功能来测试  HAL_I2C_Mem_Read
			case SHT_MeasureCmdSend:
				MYI2C_READ_FUNC(SHTDEV,SHT31_IIC_Address,SHT3X_CMD_MEASURE_LPM,temp,6);
				if((CheckCrc(temp,2)	==	temp[2]))	//数据校验正确
				{
					SHTDEV->T_RAW = ((temp[0]<<8) | temp[1]);
				}	
				if((CheckCrc(&temp[3],2)	==	temp[5]))	//数据校验正确
				{
					SHTDEV->RH_RAW = ((temp[3]<<8) | temp[4]);
				}
				tick_to_temperature(SHTDEV->T_RAW, &SHTDEV->T);
				tick_to_humidity(SHTDEV->RH_RAW, &SHTDEV->RH);	

				// SHTDEV->Step = SHT_MeasureCompleted;
				SHTDEV->Step = SHT_Idle;
				SHTDEV->WorkState = SHT31_Idle;

				break;

			/*等待设备测量完成*/
			case SHT_MeasureOngoing:

				break;

			/*读取设备测量结果，计算测量结果---进入空闲模式*/
			case SHT_MeasureCompleted:

				SHTDEV->Step = SHT_Idle;
				SHTDEV->WorkState = SHT31_Idle;
				break;

			/*设备处于空闲状态*/
			case SHT_Idle:
				SHTDEV->Step = SHT_MeasureCmdSend;
				SHTDEV->WorkState = SHT31_Measure_ongoing;
				break;	

			/*设备处于离线状态*/
			case SHT_Offline:

				break;

			default:
				break;
		}

		Set_Time(&SHTDEV->Count,SHTDEV->Period);	//重装载 闪烁周期计数变量
	}	

	return SHTDEV->WorkState;
}

