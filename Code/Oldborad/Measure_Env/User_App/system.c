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
	//----指示灯设备注册属性
	Indicator_Device_Enroll(&LED1,LED1_GPIO_Port,LED1_Pin,Inid_Open,Inid_DEVError);
	//----LED1的计时变量注册到时间表
	Enroll_Time_Tab(&Timer_OBJ,&LED1.Count);	
	//----编码器设备注册属性
	Encoder_Device_Enroll(&Encoder1,EnCoder_A_GPIO_Port,EnCoder_A_Pin,\
							EnCoder_B_GPIO_Port,EnCoder_B_Pin,\
							EnCoder_SW_GPIO_Port,EnCoder_SW_Pin,\
							Encoder_State_Released,Encoder_Call_T);
	//----编码器的计时变量注册到时间表
	Enroll_Time_Tab(&Timer_OBJ,&Encoder1.Call_Count);	

	Enroll_Time_Tab(&Timer_OBJ,&UILoadCnt);	
	
	
	//----启动定时器1 
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
	
	Indicator_Run(&LED1);		//指示灯
	lvgl_encoder_run();			//LVGL适配编码器处理任务
	User_UI_Load();					//用户LVGL的UI补充代码
	
	
}

