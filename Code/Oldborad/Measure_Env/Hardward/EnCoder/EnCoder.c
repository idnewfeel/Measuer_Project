


#include "EnCoder.h"

Encoder Encoder1;
 

 /*******************************************************************************
* @FunctionName   : Indicator_Device_Enroll
* @Description    : ������������ע�ᵽ�豸�ṹ��z��
* @Input          : EncoderDEV----�豸�ṹ��  Port----�豸IO��  Pin -----�豸���ź� 
*					state------�豸״̬	   period----�豸��һ����������
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
* @Description    : �������豸���к���
* @Input          : EncoderDEV----�豸�ṹ��
* @Output         : 
* @Return         : None
*******************************************************************************/
void Encoder_Run(Encoder* EncoderDEV)
{
	static Encoder_Pin_State SW_State_Temp = 0xFF;
	Encoder_Pin_State SW_state = 0xFF;
	if (EncoderDEV->Call_Count<=0)
	{

		/*1.ɨ���������SW����*/
		EncoderDEV->SW_State = SW_state = Get_EncoderPort_State(EncoderDEV->SW_Port,EncoderDEV->SW_Pin);
		if(SW_State_Temp==Encoder_Port_RESET && SW_state == Encoder_Port_RESET)	//SW���Ű���  2���������
		{
			EncoderDEV->State = Encoder_State_Press;//������״̬Ϊ����
			return;
		} 
		else if (SW_state == Encoder_Port_SET)
		{
			SW_State_Temp = 0xFF;
			SW_state	   = 0xFF;
			EncoderDEV->State =  Encoder_State_Released;//������״̬Ϊ�ɿ�
		}
		else
		{
			SW_State_Temp = SW_state;
			EncoderDEV->State =  Encoder_State_Released;//������״̬Ϊ�ɿ�
			
		}


		/*2.ɨ�����������ť���� �Դ�10ms�������*/
		Encoder_Pin_State A_state = 0xFF,B_state = 0xFF;
		static Encoder_Pin_State A_Stemp =0xFF,B_Stemp=0xFF;
		static uint8_t ABScan_time = 0;	//������ɨ��ʱ��
		static uint8_t PluseUpFlag = 0;	//���������б��
		static uint8_t ABRunFlag = 0;	//AB�����½����
		
		EncoderDEV->A_State = A_state	= Get_EncoderPort_State(EncoderDEV->A_Port,EncoderDEV->A_Pin);
		EncoderDEV->B_State = B_state = Get_EncoderPort_State(EncoderDEV->B_Port,EncoderDEV->B_Pin);
		/*2.1-���������Ƿ��ڿ���״̬*/
		if(A_state == Encoder_Port_SET && B_state == Encoder_Port_SET && \
		(A_Stemp == Encoder_Port_SET && B_state == Encoder_Port_SET))//���඼�Ǹߵ�ƽ���ڿ���״̬
		{
			ABScan_time= 20;//һ����ת������ƽ�ı仯��200ms��
			PluseUpFlag = 1;//��������ť���ڿ���״̬
		}
		else
		{
			A_Stemp = A_state;
			B_Stemp = B_state;
		}
		/*2.2-����������ת����ʱ��ɨ��AB�����ƽ���½�*/
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
		/*2.3-���������Ƿ������ת����*/
		if(ABRunFlag>0 && (A_state==Encoder_Port_RESET || B_state==Encoder_Port_RESET) )
		{
			if(A_Stemp==Encoder_Port_RESET && A_state==Encoder_Port_RESET && ABRunFlag==2)//��ת��B���ȳ��ֵ͵�ƽ��A�����ֵ͵�ƽ
			{
				PluseUpFlag=0;
				ABScan_time=0;
				ABRunFlag=0;
				EncoderDEV->State=Encoder_State_Left;//��������ת
				return;
			}
			else if(B_Stemp==Encoder_Port_RESET && B_state==Encoder_Port_RESET && ABRunFlag==1)//��ת��A���ȳ��ֵ͵�ƽ��B�����ֵ͵�ƽ
			{
				PluseUpFlag=0;
				ABScan_time=0;
				ABRunFlag=0;
				EncoderDEV->State=Encoder_State_Right;//��������ת		
				return;
			}
			else
			{
				A_Stemp = A_state;
				B_Stemp = B_state;
			}
		}

		if (ABScan_time>0)//������ɨ������
		{ABScan_time--;}

		if (PluseUpFlag==1 && ABScan_time<=0)
		{PluseUpFlag=0;}

		Set_Time(&EncoderDEV->Call_Count,Encoder_Call_T);//��װ�� �������ڼ���
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
		if(Encoder1.State==Encoder_State_Left)//��ת
		{encoder_diff = -1;}
		else if(Encoder1.State==Encoder_State_Right)//��ת
		{encoder_diff = 1;}
		else if(Encoder1.State==Encoder_State_Press)//����
		{encoder_state = LV_INDEV_STATE_PRESSED;}
		else if(Encoder1.State==Encoder_State_Released)//�ɿ�
		{encoder_state = LV_INDEV_STATE_RELEASED;}
	}
	else if (scr!=ui_Main && scr!=ui_StartUp)
	{
		if(scr==ui_TDetail)
		{
			if(Encoder1.State==Encoder_State_Left)//��ת
			{_ui_screen_change(ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);}
			else if(Encoder1.State==Encoder_State_Right)//��ת
			{_ui_screen_change(ui_RHDetail, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);}
		}
		else if(scr==ui_RHDetail)
		{
			if(Encoder1.State==Encoder_State_Left)//��ת
			{_ui_screen_change(ui_TDetail, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);}
			else if(Encoder1.State==Encoder_State_Right)//��ת
			{_ui_screen_change(ui_TVOCDetail, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);}
		}		
		else if(scr==ui_TVOCDetail)
		{
			if(Encoder1.State==Encoder_State_Left)//��ת
			{_ui_screen_change(ui_RHDetail, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);}
			else if(Encoder1.State==Encoder_State_Right)//��ת
			{_ui_screen_change(ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);}
		}	


	}

	
	
//	Encoder1.State=  Encoder_State_Released;//������״̬Ϊ�ɿ�
}


