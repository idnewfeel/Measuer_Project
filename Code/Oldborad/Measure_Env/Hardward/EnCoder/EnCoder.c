


#include "EnCoder.h"

Encoder Encoder1;
 

 /*******************************************************************************
* @FunctionName   : Indicator_Device_Enroll
* @Description    : 将编码器属性注册到设备结构体z中
* @Input          : EncoderDEV----设备结构体  Port----设备IO口  Pin -----设备引脚号 
*					state------设备状态	   period----设备下一个调用周期
* @Output         : 
* @Return         : None
*******************************************************************************/
void Encoder_Device_Enroll(Encoder* EncoderDEV,Encoder_Port A_Port,Encoder_Pin A_Pin,
							Encoder_Port B_Port,Encoder_Pin B_Pin,
							Encoder_Port SW_Port,Encoder_Pin SW_Pin,
							Encoder_State state,Encoder_Time Period)
{
	EncoderDEV->A_Port 			= 	A_Port;
	EncoderDEV->A_Pin			=	A_Pin;
	EncoderDEV->B_Port 			= 	B_Port;
	EncoderDEV->B_Pin			=	B_Pin;
	EncoderDEV->SW_Port 		= 	SW_Port;
	EncoderDEV->SW_Pin			=	SW_Pin;
	EncoderDEV->State			=	state;
	EncoderDEV->Period 			=	Period; 
	EncoderDEV->Call_Count		=	Period;
	
}


Encoder_Pin_State Get_EncoderPort_State(Encoder_Port Port,Encoder_Pin Pin)
{
	return HAL_GPIO_ReadPin(Port,Pin);
}
 /*******************************************************************************
* @FunctionName   : Encoder_Run
* @Description    : 编码器设备运行函数
* @Input          : EncoderDEV----设备结构体
* @Output         : 
* @Return         : None
*******************************************************************************/
void Encoder_Run(Encoder* EncoderDEV)
{
	static Encoder_Pin_State SW_State_Temp = 0xFF;
	Encoder_Pin_State SW_state = 0xFF;
	if (EncoderDEV->Call_Count<=0)
	{

		/*1.扫描编码器的SW按键*/
		EncoderDEV->SW_State = SW_state = Get_EncoderPort_State(EncoderDEV->SW_Port,EncoderDEV->SW_Pin);
		if(SW_State_Temp==Encoder_Port_RESET && SW_state == Encoder_Port_RESET)	//SW引脚按下  2次软件消抖
		{
			EncoderDEV->State = Encoder_State_Press;//编码器状态为按下
			return;
		} 
		else if (SW_state == Encoder_Port_SET)
		{
			SW_State_Temp = 0xFF;
			SW_state	   = 0xFF;
			EncoderDEV->State =  Encoder_State_Released;//编码器状态为松开
		}
		else
		{
			SW_State_Temp = SW_state;
			EncoderDEV->State =  Encoder_State_Released;//编码器状态为松开
			
		}


		/*2.扫描编码器的旋钮引脚 自带10ms软件消抖*/
		Encoder_Pin_State A_state = 0xFF,B_state = 0xFF;
		static Encoder_Pin_State A_Stemp =0xFF,B_Stemp=0xFF;
		static uint8_t ABScan_time = 0;	//编码器扫描时间
		static uint8_t PluseUpFlag = 0;	//编码器空闲标记
		static uint8_t ABRunFlag = 0;	//AB相先下降标记
		
		EncoderDEV->A_State = A_state	= Get_EncoderPort_State(EncoderDEV->A_Port,EncoderDEV->A_Pin);
		EncoderDEV->B_State = B_state = Get_EncoderPort_State(EncoderDEV->B_Port,EncoderDEV->B_Pin);
		/*2.1-检查编码器是否处于空闲状态*/
		if(A_state == Encoder_Port_SET && B_state == Encoder_Port_SET && \
		(A_Stemp == Encoder_Port_SET && B_state == Encoder_Port_SET))//两相都是高电平处于空闲状态
		{
			ABScan_time= 20;//一次旋转动作电平的变化在200ms内
			PluseUpFlag = 1;//编码器旋钮处于空闲状态
		}
		else
		{
			A_Stemp = A_state;
			B_Stemp = B_state;
		}
		/*2.2-编码器有旋转动作时的扫描AB那相电平先下降*/
		if(PluseUpFlag==1 && ABScan_time>0 && ABRunFlag==0)
		{
			if(A_state==Encoder_Port_RESET && A_Stemp==Encoder_Port_RESET)
			{
				ABRunFlag=1;
			}
			else if(B_state==Encoder_Port_RESET && B_Stemp==Encoder_Port_RESET)
			{
				ABRunFlag=2;
			}
			else
			{
				A_Stemp = A_state;
				B_Stemp = B_state;
			}
		}
		/*2.3-检查编码器是否完成旋转动作*/
		if(ABRunFlag>0 && (A_state==Encoder_Port_RESET || B_state==Encoder_Port_RESET) )
		{
			if(A_Stemp==Encoder_Port_RESET && A_state==Encoder_Port_RESET && ABRunFlag==2)//左转是B相先出现低电平，A相后出现低电平
			{
				PluseUpFlag=0;
				ABScan_time=0;
				ABRunFlag=0;
				EncoderDEV->State=Encoder_State_Left;//编码器左转
				return;
			}
			else if(B_Stemp==Encoder_Port_RESET && B_state==Encoder_Port_RESET && ABRunFlag==1)//右转是A相先出现低电平，B相后出现低电平
			{
				PluseUpFlag=0;
				ABScan_time=0;
				ABRunFlag=0;
				EncoderDEV->State=Encoder_State_Right;//编码器右转		
				return;
			}
			else
			{
				A_Stemp = A_state;
				B_Stemp = B_state;
			}
		}

		if (ABScan_time>0)//编码器扫描周期
		{ABScan_time--;}

		if (PluseUpFlag==1 && ABScan_time<=0)
		{PluseUpFlag=0;}

		Set_Time(&EncoderDEV->Call_Count,Encoder_Call_T);//重装载 调用周期计数
	}
}

#include "lv_port_indev.h"
#include "ui.h"
#include "ui_helpers.h"
void lvgl_encoder_run(void)
{
	Encoder_Run(&Encoder1);
	lv_obj_t* scr = lv_scr_act();
	if(scr==ui_Main)
	{
		if(Encoder1.State==Encoder_State_Left)//左转
		{encoder_diff = -1;}
		else if(Encoder1.State==Encoder_State_Right)//右转
		{encoder_diff = 1;}
		else if(Encoder1.State==Encoder_State_Press)//按下
		{encoder_state = LV_INDEV_STATE_PRESSED;}
		else if(Encoder1.State==Encoder_State_Released)//松开
		{encoder_state = LV_INDEV_STATE_RELEASED;}
	}
	else if (scr!=ui_Main && scr!=ui_StartUp)
	{
		if(scr==ui_TDetail)
		{
			if(Encoder1.State==Encoder_State_Left)//左转
			{_ui_screen_change(ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);}
			else if(Encoder1.State==Encoder_State_Right)//右转
			{_ui_screen_change(ui_RHDetail, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);}
		}
		else if(scr==ui_RHDetail)
		{
			if(Encoder1.State==Encoder_State_Left)//左转
			{_ui_screen_change(ui_TDetail, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);}
			else if(Encoder1.State==Encoder_State_Right)//右转
			{_ui_screen_change(ui_TVOCDetail, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);}
		}		
		else if(scr==ui_TVOCDetail)
		{
			if(Encoder1.State==Encoder_State_Left)//左转
			{_ui_screen_change(ui_RHDetail, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);}
			else if(Encoder1.State==Encoder_State_Right)//右转
			{_ui_screen_change(ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);}
		}	


	}

	
	
//	Encoder1.State=  Encoder_State_Released;//编码器状态为松开
}


