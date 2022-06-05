#include "SGP40.h"

SGP_DEV SGP40;
VocAlgorithmParams	SGP40_Algorithm_STU;



 /*******************************************************************************
* @FunctionName   : SHT_Device_Enroll
* @Description    : ��SGP40����ע�ᵽ�豸�ṹ��z��
* @Input          : SGPDEV----�豸�ṹ��  	SDAPort----�豸IIC�ӿ�����		SDAPin -----�豸IIC�ӿ�����
*					status------�豸״̬	Period----��������				IICNet-----�豸��IIC���߾��
* @Output         : 
* @Return         : None
*******************************************************************************/
void SGP_Device_Enroll(SGP_DEV* SGPDEV,SGP40_Port SDAPort,SGP40_Pin SDAPin,SGP40_Port SCLPort,SGP40_Pin SCLPin,SGP40_period Period,
						SGP40_IIC_Handle*	IICNet)
{
	SGPDEV->SDA_Port 	= 	SDAPort;
	SGPDEV->SDA_P		=	SDAPin;
	SGPDEV->SCL_Port 	= 	SCLPort;
	SGPDEV->SCL_P		=	SCLPin;
	SGPDEV->IIC_Net		=	IICNet;	
	SGPDEV->VOC_RAW		=	0;
	SGPDEV->VOC_Index	=	0;
	SGPDEV->WorkState	=	SGP40_Init;		//SGP40��ʼ��
	SGPDEV->Status		=	0;
	SGPDEV->Period 		=	Period; 
	SGPDEV->Count		=	Period;
	SGPDEV->Step		=	SGP_Init;

}

 /*******************************************************************************
* @Function Name  : MYI2C_SGP_WRITE_FUNC
* @Description    : Ӳ��IICд�� ����
* @Input          : DEVICE_T*	Dev_Obj---IIC�豸���,unsigned char device_addr---�豸��ַ,char register_addr---�Ĵ�����ַ
										unsigned char *pDATA---���ݻ����ַ, unsigned char len---���ݳ���
* @Output         : 
* @Return         :sucess=0 ,fail=1
*******************************************************************************/
unsigned char MYI2C_SGP_WRITE_FUNC(SGP_DEV* SGPDEV,unsigned char device_addr,uint16_t register_addr,unsigned char* write_data,unsigned char Writelen)
{	
	uint8_t i = 0;
	uint8_t	reg[10] =	{0};
	uint8_t LEN	=	0;
		reg[0]	=	(uint8_t)((register_addr&0xFF00)>>8);
		reg[1]	=	(uint8_t)(register_addr&0x00FF);	
		if (Writelen!=0)
		{
			for(i=0;i<Writelen;i++)
			{
				reg[2+i] = write_data[i];
			}
		}
		LEN = Writelen+2;
	if(HAL_I2C_Master_Transmit(SGPDEV->IIC_Net,device_addr, reg, LEN,1000) != HAL_OK)	
	{
		return 1;
	}
	return 0 ;
}

 /*******************************************************************************
* @Function Name  : MYI2C_SGP_READ_FUNC
* @Description    : Ӳ��IIC��ȡ���ݣ�����Ҫ�ȴ���
* @Input          : DEVICE_T*	Dev_Obj---IIC�豸���,unsigned char device_addr---�豸��ַ,char register_addr---�Ĵ�����ַ
										unsigned char *pDATA---���ݻ����ַ, unsigned char len---���ݳ���
* @Output         : 
* @Return         :sucess=0 ,fail=1
*******************************************************************************/
unsigned char MYI2C_SGP_READ_FUNC(SGP_DEV* SGPDEV,unsigned char device_addr,unsigned char *pDATA, unsigned char len)
{
		if(HAL_I2C_Master_Receive(SGPDEV->IIC_Net,device_addr,pDATA,len,1000) != HAL_OK)
		{
			return 1;
		}
		return 0;	
}

/*******************************************************************************
* @FunctionName   : SGP_Check_Online
* @Description    : SGP40����Ƿ�����
* @Input          : SGPDEV----�豸�ṹ�� 
* @Output         : 
* @Return         : None
*******************************************************************************/
static void SGP_Check_Online(SGP_DEV* SGPDEV )
{

	uint8_t data[20] = {0};
	if(MYI2C_SGP_WRITE_FUNC(SGPDEV,SGP40_IIC_Address,SGP40_CMD_GET_SERIAL_ID,(unsigned char*)SGPDEV,0)==0)
	{
		if (MYI2C_SGP_READ_FUNC(SGPDEV,SGP40_IIC_Address,data, 9)==0)
		{
			if((CheckCrc(data,2)==data[2]) && (CheckCrc(&data[3],2)==data[5]) && (CheckCrc(&data[6],2)==data[8]))	//����У����ȷ
			{
				SGPDEV->SerialNumber =  ((data[3]<<24) | (data[4]<<16) | (data[6]<<8) | (data[7]));//((data[0]<<40) | (data[1]<<32) |
				SGPDEV->WorkState = SGP40_Online;
				SGPDEV->Status = SGP_Online;
			}
		}
	}
	else
	{
		SGPDEV->WorkState = SGP40_Offline;
		SGPDEV->Status = SGP_Offline;
	}	
}




/**
 * Convert humidity and temperature in the format used by the sensor.
 *
 * @param humidity                  Relative humidity in [percent relative
 *                                  humidity], multiplied by 1000.
 * @param temperature               Temperature in [degree Celsius], multiplied
 *                                  by 1000.
 * @param humidity_sensor_format    Output parameter, humidity in the format
 *                                  expected by the sensor.
 * @param temperature_sensor_format Output parameter, temperature in the format
 *                                  expected by the sensor.
 */
void sgp40_convert_rht(int32_t humidity, int32_t temperature,
                       uint16_t* humidity_sensor_format,
                       uint16_t* temperature_sensor_format) {
    if (humidity < 0) {
        humidity = 0;
    } else if (humidity > 100000) {
        humidity = 100000;
    }
    if (temperature < -45000) {
        temperature = -45000;
    } else if (temperature > 129760) {
        temperature = 129760;
    }

    /* humidity_sensor_format = humidity / 100000 * 65535;
     * 65535 / 100000 = 0.65535 -> 0.65535 * 2^5 = 20.9712 / 2^10 ~= 671
     */
    *humidity_sensor_format = (uint16_t)((humidity * 671) >> 10);

    /* temperature_sensor_format[1] = (temperature + 45000) / 175000 * 65535;
     * 65535 / 175000 ~= 0.375 -> 0.375 * 2^3 = 2.996 ~= 3
     */
    *temperature_sensor_format = (uint16_t)(((temperature + 45000) * 3) >> 3);
}


 /*******************************************************************************
* @FunctionName   : SGP40_Run
* @Description    : SGP40�����������豸���к���
* @Input          : SGPDEV----�豸�ṹ��
* @Output         : 
* @Return         : SGP40_WorkState   �������Ĺ���״̬
*******************************************************************************/

SGP40_WoreState SGP40_Run(SGP_DEV* SGPDEV)
{
	uint8_t temp[6] = {0};
	// int32_t i32temp_t = 0, i32temp_rh= 0;
	if (SGPDEV->Count<=0)
	{
		switch (SGPDEV->Step)
		{
			/*��ʼ����ɣ���ѯ�豸�Ƿ�����*/
			case SGP_Init:
				SGP_Check_Online(SGPDEV);
				if(SGPDEV->WorkState==SHT31_Online)//�豸����
				{
					VocAlgorithm_init(&SGP40_Algorithm_STU);//��ʼ��SGP40VOC�㷨�ṹ��
					SGPDEV->Step = SGP_Online;
				}
				else if (SGPDEV->WorkState==SHT31_Offline)
				{
					SGPDEV->Step = SGP_Offline;
				}
				SGPDEV->Period = 10;
				Set_Time(&SGPDEV->Count,SGPDEV->Period);	//��װ�� ��˸���ڼ�������
				break;

			/*�豸��������״̬-�����Լ�������õȴ�350ms*/
			case SGP_Online:
				MYI2C_SGP_WRITE_FUNC(SGPDEV,SGP40_IIC_Address,SGP40_CMD_EXECUTE_SELF_TEST,NULL,0);
				SGPDEV->Step = SGP_Execute_Self_Test;
				SGPDEV->Period = 350;
				Set_Time(&SGPDEV->Count,SGPDEV->Period);	//��װ�� ��˸���ڼ�������
				break;

			case SGP_Execute_Self_Test:
				if (MYI2C_SGP_READ_FUNC(SGPDEV,SGP40_IIC_Address,temp, 3)==0)
				{
					if(CheckCrc(temp,2)==temp[2] )	//����У����ȷ
					{
						if(temp[0] == 0xD4)	//0xD4���������Լ�ͨ��
						{

						}
						else if (temp[0] == 0x4B)	//���������Լ�һ������������
						{
							
						}
						SGPDEV->Status = ((temp[0]<<8) | (temp[1]));
						SGPDEV->WorkState = SGP40_Measure_ongoing;
					}
				}
				SGPDEV->Period = 100;
				Set_Time(&SGPDEV->Count,SGPDEV->Period);	//��װ�� ��˸���ڼ�������				
				SGPDEV->Step = SGP_MeasureCmdSend;
				break;

			/*���Ͳ�������*/  //�ɳ���STM32��ʱ����������������  HAL_I2C_Mem_Read
			case SGP_MeasureCmdSend:
				// i32temp_t = SHT31.T ;
				// i32temp_rh = SHT31.RH;
				// sgp40_convert_rht(i32temp_t,i32temp_rh,);
				temp[0] = (SHT31.T_RAW&0xFF00)>>8;
				temp[1] = (SHT31.T_RAW&0x00FF);
				temp[2] = CheckCrc(temp,2);
				temp[3] = (SHT31.RH_RAW&0xFF00)>>8;
				temp[4] = (SHT31.RH_RAW&0x00FF);
				temp[5] = CheckCrc(&temp[3],2);
				MYI2C_SGP_WRITE_FUNC(SGPDEV,SGP40_IIC_Address,SGP40_CMD_MEASURE_RAW,temp,6);
				SGPDEV->Step = SGP_MeasureOngoing;
				SGPDEV->Period = 30;
				Set_Time(&SGPDEV->Count,SGPDEV->Period);	//��װ�� ��˸���ڼ�������				
				break;

			/*�ȴ��豸�������*/
			case SGP_MeasureOngoing:
				if (MYI2C_SGP_READ_FUNC(SGPDEV,SGP40_IIC_Address,temp, 3)==0)
				{
					if(CheckCrc(temp,2)==temp[2] )	//����У����ȷ
					{
						SGPDEV->VOC_RAW = ((temp[0]<<8) | (temp[1]));
					}
				}
				SGPDEV->Period = 1;
				Set_Time(&SGPDEV->Count,SGPDEV->Period);	//��װ�� ��˸���ڼ�������				
				SGPDEV->Step = SGP_MeasureCompleted;
				break;

			/*��ȡ�豸�������������������---�ȴ���1s���ٴβ���*/
			case SGP_MeasureCompleted:
				VocAlgorithm_process(&SGP40_Algorithm_STU, (int32_t)SGPDEV->VOC_RAW, (int32_t*)&(SGPDEV->VOC_Index));	
				SGPDEV->Period = 1000;
				Set_Time(&SGPDEV->Count,SGPDEV->Period);	//��װ�� ��˸���ڼ�������				
				SGPDEV->Step = SGP_Idle;
				SGPDEV->WorkState = SGP40_Idle;
				break;

			/*�豸���ڿ���״̬*/
			case SGP_Idle:
				SGPDEV->Step = SGP_MeasureCmdSend;
				SGPDEV->WorkState = SGP40_Measure_ongoing;
				break;	

			/*�豸��������״̬*/
			case SGP_Offline:

				break;

			default:
				break;
		}

		
	}	

	return SGPDEV->WorkState;
}

