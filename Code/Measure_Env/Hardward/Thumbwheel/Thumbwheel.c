#include "Thumbwheel.h"




/**
******************************************************************************
* 	@file 		Thumbwheel.c
* 	@brief 		������������
*	@author	: 	��
******************************************************************************
*	@Description�������������ʵ�ֲ��ֵ������߼�
*
******************************************************************************
* 	˵����ʱ��������ô���					������λ1ms
* 	Ҫʹ��ʱ�������Ҫʹ��					Enroll_Time_Tab 	��������Ҫ��ʱ�ı���������Ӧ�ú�ʱ����еı����������ͱ���һ�£� ע�ᵽʱ�����
* 	�� 1ms�Ķ�ʱ���ж��е���				Time_Tab_minus		������ʱ������Ѿ�ע��ı������� -- ����
* 	�ڼ���0�����							Set_Time					�����Լ�ʱ�������и�ֵ
* 	�ڲ�����Ҫ��������ʱ����				Logout_Time_Tab 	��������ʱ������ʱ�����ɾ��
*	ͨ����TIM_Management.h���޸�			MAX_TAB_NUM				�궨�����ı�ʱ���ĸ���
*
******************************************************************************
*/



Thumbwheel Thumb_1;
 

 /*******************************************************************************
* @FunctionName   : Thumb_Device_Enroll
* @Description    : ������������ע�ᵽ�豸�ṹ��z��
* @Input          : Thumbwheel----�豸�ṹ��  Port----�豸IO��  Pin -----�豸���ź� 
*					state------�豸״̬	   period----�豸��һ����������
* @Output         : 
* @Return         : None
*******************************************************************************/
void Thumb_Device_Enroll(Thumbwheel* ThumbDEV,Thumbwheel_Port Front_Port,Thumbwheel_Pin Front_Pin,
							Thumbwheel_Port Rear_Port,Thumbwheel_Pin Rear_Pin,
							Thumbwheel_Port Mid_Port,Thumbwheel_Pin Mid_Pin,
							Thumbwheel_State state,Thumbwheel_Time Period)
{
	
	
	ThumbDEV->Front_Port 		= 	Front_Port;
	ThumbDEV->Front_Pin			=	Front_Pin;
	ThumbDEV->Rear_Port 		= 	Rear_Port;
	ThumbDEV->Rear_Pin			=	Rear_Pin;
	ThumbDEV->Mid_Port 			= 	Mid_Port;
	ThumbDEV->Mid_Pin			=	Mid_Pin;
	ThumbDEV->State				=	state;
	ThumbDEV->Period 			=	Period; 
	ThumbDEV->Call_Count		=	Period;
	ThumbDEV->Event				=	Thumbwheel_Event_None;

}


static Thumbwheel_Pin_State Get_ThumbPort_State(Thumbwheel_Port Port,Thumbwheel_Pin Pin)
{
	return HAL_GPIO_ReadPin(Port,Pin);
}
 /*******************************************************************************
* @FunctionName   : Thumb_Run
* @Description    : �����豸���к���
* @Input          : ThumbDEV----�豸�ṹ��
* @Output         : 
* @Return         : None
*******************************************************************************/
void Thumb_Run(Thumbwheel* ThumbDEV)
{
	static uint16_t	Front_time=0,Mid_time=0,Rear_time=0,Idle_time=0;//�²�ʱ�䣬�м�ʱ�䣬�ϲ�ʱ�䣬����ʱ��
	static uint8_t	Long_flag=0;//�������
	if (ThumbDEV->Call_Count<=0)
	{
		Set_Time(&ThumbDEV->Call_Count,Thumbwheel_Call_T);//��װ�� �������ڼ���

/*----------1.ɨ�貦�ֵ��м�-----------*/
		ThumbDEV->Mid_State 	= 	Get_ThumbPort_State(ThumbDEV->Mid_Port,ThumbDEV->Mid_Pin);
		ThumbDEV->Front_State  	= 	Get_ThumbPort_State(ThumbDEV->Front_Port,ThumbDEV->Front_Pin);
		ThumbDEV->Rear_State  	= 	Get_ThumbPort_State(ThumbDEV->Rear_Port,ThumbDEV->Rear_Pin);

		if(ThumbDEV->Mid_State==Thumbwheel_Port_RESET )	//�м�����
		{
			Idle_time=0;
			Mid_time++;
			ThumbDEV->State = Thumbwheel_State_Press;//�����м�����
			if(Mid_time>=Long_Time_trigger)//2s
			{
				if(Long_flag==0)
				{
					Long_flag=1;
					ThumbDEV->Event = Thumbwheel_Event_Press_long;//�����м������¼�
					 return ;						
				}
			}
			
		} 
		else if (ThumbDEV->Front_State==Thumbwheel_Port_RESET)	
		{
			Idle_time=0;
			Front_time++;
			ThumbDEV->State = Thumbwheel_State_Front;//����ǰ��
			if(Front_time>=Long_Time_trigger )//2s
			{
				if (Long_flag==0)
				{
					Long_flag=1;
					ThumbDEV->Event = Thumbwheel_Event_Front_long;//��������ǰ���¼�
					 return;		
				}
			}
			
		}
		else if (ThumbDEV->Rear_State==Thumbwheel_Port_RESET)
		{
			Idle_time=0;
			Rear_time++;
			ThumbDEV->State = Thumbwheel_State_Rear;//���ֺ�
			if(Rear_time>=Long_Time_trigger)//2s
			{
				if(Long_flag==0)
				{
					Long_flag=1;
					ThumbDEV->Event = Thumbwheel_Event_Rear_long;//�����󲦳����¼�
					 return ;						
				}
			}
		
		}		
		else//���ִ����޶���״̬
		{
			if(Mid_time!=0 && Mid_time<Long_Time_trigger && Mid_time>=2)//�����¼�����2�뵫����20ms
			{
				
				ThumbDEV->Event = Thumbwheel_Event_Press;//�����м��̰��¼�
			}	
			else if(Front_time!=0 && Front_time<Long_Time_trigger && Front_time>=2)
			{
				
				ThumbDEV->Event = Thumbwheel_Event_Front;//����ǰ���̰��¼�
			}
			else if(Rear_time!=0 && Rear_time<Long_Time_trigger && Rear_time>=2)
			{
				
				ThumbDEV->Event = Thumbwheel_Event_Rear;//�����󲦶̰��¼�
			}
			else
			{
				ThumbDEV->Event = Thumbwheel_Event_None;
			}

			Idle_time++;
			Mid_time= 0;
			Front_time=0;
			Rear_time=0;
			Long_flag=0;
			ThumbDEV->State =  Thumbwheel_State_Released;//������״̬Ϊ�ɿ�
			 return ;//ֱ�ӽ���ѭ��
		}
		//_______�����м��ػ�
		if(Thumb_1.Event == Thumbwheel_Event_Press_long)
		{
			POWER_OFF;
		}
		else if(Thumb_1.Event == Thumbwheel_Event_Front_long)
		{
			if(lv_group_get_focused(group) == ui_SWPower)
			{
				lv_slider_set_value(ui_SWPower,lv_slider_get_value(ui_SWPower)-1,LV_ANIM_ON);
			}
		}
		else if(Thumb_1.Event == Thumbwheel_Event_Rear_long)
		{
			if(lv_group_get_focused(group) == ui_SWPower)
			{
				lv_slider_set_value(ui_SWPower,lv_slider_get_value(ui_SWPower)+1,LV_ANIM_ON);
			}		
		}


	}
	//  return Thumbwheel_Event_None;
}





 /*******************************************************************************
* @FunctionName   : lvgl_Thumb_run
* @Description    : �����豸ΪLVGL�豸�¼�����һЩ�����Ͳ����߼�
* @Input          : ThumbDEV----�豸�ṹ��
* @Output         : 
* @Return         : None
*******************************************************************************/
#include "lv_port_indev.h"
#include "ui.h"
#include "ui_helpers.h"
lv_obj_t* current_scr;
void lvgl_Thumb_run(void)
{
	Thumb_Run(&Thumb_1);//�������к���


	//----�����л�����
	lv_obj_t* scr = lv_scr_act();

	//----���ֶ�������LVGL�����
	if(Thumb_1.Event==Thumbwheel_Event_Front)//
	{encoder_diff = -1;}
	else if(Thumb_1.Event==Thumbwheel_Event_Rear)//
	{encoder_diff = 1;}
	else if(Thumb_1.Event==Thumbwheel_Event_Press)//
	{encoder_state = LV_INDEV_STATE_PRESSED;}	

	if(current_scr!=scr)
	{
		current_scr=scr;
		if(scr==ui_Main)	//����Mainҳ����Ӹ�ҳ��Ŀɲ����ؼ�
		{
			lv_group_remove_all_objs(group);
			lv_group_add_obj(group,ui_MidBtn);		//��һ����ӽ�ȥ�Ŀؼ����ᱻĬ��ѡ��	
			lv_group_add_obj(group,ui_RightBtn);
			lv_group_add_obj(group,ui_LeftBtn);			
		}
		else if(scr==ui_SET)
		{
			lv_group_remove_all_objs(group);

			lv_group_add_obj(group,ui_Roller2);
			lv_group_add_obj(group,ui_Switch1);
			lv_group_add_obj(group,ui_SWPower);
			lv_group_add_obj(group,ui_LeftBtn1);


		}
		else if (scr!=ui_Main && scr!=ui_StartUp && scr!=ui_SET)//����ҳ��û�пɲ����ؼ�
		{
			lv_group_remove_all_objs(group);
		}
	}

	if (scr!=ui_Main && scr!=ui_StartUp && scr!=ui_SET)//û�пɲ����ؼ��Ľ���
	{
		if(scr==ui_TDetail)
		{
			if(Thumb_1.Event==Thumbwheel_Event_Front)//
			{_ui_screen_change(ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);}
			else if(Thumb_1.Event==Thumbwheel_Event_Rear)//
			{_ui_screen_change(ui_RHDetail, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);}
		}
		else if(scr==ui_RHDetail)
		{
			if(Thumb_1.Event==Thumbwheel_Event_Front)//
			{_ui_screen_change(ui_TDetail, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);}
			else if(Thumb_1.Event==Thumbwheel_Event_Rear)//
			{_ui_screen_change(ui_TVOCDetail, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);}
		}		
		else if(scr==ui_TVOCDetail)
		{
			if(Thumb_1.Event==Thumbwheel_Event_Front)//
			{_ui_screen_change(ui_RHDetail, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);}
			else if(Thumb_1.Event==Thumbwheel_Event_Rear)//
			{_ui_screen_change(ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);}
		}	
		else if(scr==ui_Debug)
		{
			if(Thumb_1.Event==Thumbwheel_Event_Press)//��Ҫȡ��������״̬�����Ϊ100ms�ӳٶ�����Ϊ��ʾLVGL1ms�Ļص��л���øö���
			{encoder_state=0;_ui_screen_change(ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);}
		}	

	}

	//________�в���ʱ�䷢������������
	if(Thumb_1.Event != Thumbwheel_Event_None && Thumb_1.State ==  Thumbwheel_State_Released)
	{
		Thumb_1.Event = Thumbwheel_Event_None;
		PlaySound(0,1);
	}		
}


