#ifndef _SGP40_H
#define _SGP40_H

#include "TIM_Management.h"
#include "i2c.h"
#include "SHT31.h"
#include "sensirion_voc_algorithm.h"
/*-------------------------------������������ʢ˼��ٷ�GitHub---------------------------------------------*/



#define SGP40_CMD_MEASURE_RAW_WORDS 1
#define SGP40_CMD_MEASURE_RAW 0x260f

/* command and constants for reading the serial ID */
#define SGP40_CMD_GET_SERIAL_ID_DURATION_US 500
#define SGP40_CMD_GET_SERIAL_ID_WORDS 3
#define SGP40_CMD_GET_SERIAL_ID 0x3682

/* command and constants for reading the featureset version */
#define SGP40_CMD_GET_FEATURESET_DURATION_US 1000
#define SGP40_CMD_GET_FEATURESET_WORDS 1
#define SGP40_CMD_GET_FEATURESET 0x202f

/*-------------------------------������������ʢ˼��ٷ�GitHub---------------------------------------------*/

#define SGP40_CMD_EXECUTE_SELF_TEST 0x280E

/*���䶨��*/
#define SGP40_IIC_Address       (0x59)<<1               //SGP40�豸��ַ
#define SGP40_Port              GPIO_TypeDef*
#define SGP40_Pin               uint16_t
#define SGP40_IIC_Handle        I2C_HandleTypeDef       //SGP40��IIC���
#define SGP40_VOC_RAW           int32_t   
#define SGP40_Status            uint16_t
#define SGP40_VOC               int32_t
#define SGP40_period            u_Time          //����
#define SGP40_Call_T            (102)          //��������
#define SGP40_Serial            uint64_t

typedef enum {
	SGP40_Init=(0),                 //SGP40��ʼ��
    SGP40_Online,                   //SGP40����
    SGP40_Offline,                  //SGP40����
	SGP40_Measure_ongoing,          //SGP40���ڽ��в���
	SGP40_Measure_completed,        //SGP40�������
	SGP40_Idle,          	        //SGP40����

}SGP40_WoreState;


typedef enum {
	SGP_Init=(SGP40_Idle+1),
    SGP_Online,
    SGP_Offline,
    SGP_Execute_Self_Test,
    SGP_Execute_Self_Test_Over,
    SGP_MeasureCmdSend,
    SGP_MeasureOngoing,
    SGP_MeasureCompleted,
    SGP_Idle,


}SGP40_Run_Step;


/*
SGP40�豸�ṹ��
*/
typedef struct SGP4x_Device
{
    SGP40_Port          SDA_Port;               //SDA����
    SGP40_Pin           SDA_P;                  //SDA����
    SGP40_Port          SCL_Port;               //SCL����
    SGP40_Pin           SCL_P;                  //SCL����
    SGP40_IIC_Handle*   IIC_Net;                //IIC���߾��
    SGP40_VOC_RAW       VOC_RAW;                //VOCԭʼֵ
    SGP40_VOC           VOC_Index;              //ת�����VOCָ��
    SGP40_WoreState     WorkState;              //SGP40����״̬
    SGP40_Status        Status;                 //SGP40����״�Ĵ���
    SGP40_Serial        SerialNumber;
    SGP40_period        Period;                 //SGP40����������װ��ֵ
    SGP40_period        Count;                  //SGP40�������ڼ���
    SGP40_Run_Step      Step;                   //SGP40���в���
}SGP_DEV;



extern SGP_DEV SGP40;


unsigned char  CheckCrc(uint8_t *dat, uint8_t Num);
void SGP_Device_Enroll(SGP_DEV* SGPDEV,SGP40_Port SDAPort,SGP40_Pin SDAPin,SGP40_Port SCLPort,SGP40_Pin SCLPin,SGP40_period Period,
						SGP40_IIC_Handle*	IICNet);
SGP40_WoreState SGP40_Run(SGP_DEV* SGPDEV);





#endif

