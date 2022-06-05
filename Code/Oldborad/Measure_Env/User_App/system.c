#include "system.h"




 /*******************************************************************************
* @FunctionName  : System_Init
* @Description    : 
* @Input          : None
* @Output         : 
* @Return         : None
*******************************************************************************/



void System_Init(void)
{
	//----ָʾ���豸ע������
	Indicator_Device_Enroll(&LED1,LED1_GPIO_Port,LED1_Pin,Inid_Open,Inid_DEVError);
	//----LED1�ļ�ʱ����ע�ᵽʱ���
	Enroll_Time_Tab(&Timer_OBJ,&LED1.Count);	
	//----�������豸ע������
	Encoder_Device_Enroll(&Encoder1,EnCoder_A_GPIO_Port,EnCoder_A_Pin,\
							EnCoder_B_GPIO_Port,EnCoder_B_Pin,\
							EnCoder_SW_GPIO_Port,EnCoder_SW_Pin,\
							Encoder_State_Released,Encoder_Call_T);
	//----�������ļ�ʱ����ע�ᵽʱ���
	Enroll_Time_Tab(&Timer_OBJ,&Encoder1.Call_Count);	

	Enroll_Time_Tab(&Timer_OBJ,&UILoadCnt);	
	
	
	//----������ʱ��1 
	HAL_TIM_Base_Start_IT(&htim1);
	
	User_UI_Init();
}


 /*******************************************************************************
* @FunctionName  	: System_Run
* @Description    : 
* @Input          : None
* @Output         : 
* @Return         : None
*******************************************************************************/


void System_Run(void)
{
	
	Indicator_Run(&LED1);		//ָʾ��
	lvgl_encoder_run();			//LVGL�����������������
	User_UI_Load();					//�û�LVGL��UI�������
	
	
}

