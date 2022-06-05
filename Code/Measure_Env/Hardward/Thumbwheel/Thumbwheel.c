#include "Thumbwheel.h"




/**
******************************************************************************
* 	@file 		Thumbwheel.c
* 	@brief 		拨轮驱动代码
*	@author	: 	李
******************************************************************************
*	@Description：这个驱动用来实现拨轮的驱动逻辑
*
******************************************************************************
* 	说明：时间管理配置代码					基数单位1ms
* 	要使用时间管理需要使用					Enroll_Time_Tab 	函数将需要计时的变量（变量应该和时间表中的变量数据类型保持一致） 注册到时间表中
* 	在 1ms的定时器中断中调用				Time_Tab_minus		函数对时间表中已经注册的变量挨个 -- 操作
* 	在减到0后调用							Set_Time					函数对计时变量进行赋值
* 	在不再需要变量计数时调用				Logout_Time_Tab 	函数将计时变量从时间表中删除
*	通过再TIM_Management.h中修改			MAX_TAB_NUM				宏定义来改变时间表的个数
*
******************************************************************************
*/



Thumbwheel Thumb_1;
 

 /*******************************************************************************
* @FunctionName   : Thumb_Device_Enroll
* @Description    : 将编码器属性注册到设备结构体z中
* @Input          : Thumbwheel----设备结构体  Port----设备IO口  Pin -----设备引脚号 
*					state------设备状态	   period----设备下一个调用周期
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
* @Description    : 拨轮设备运行函数
* @Input          : ThumbDEV----设备结构体
* @Output         : 
* @Return         : None
*******************************************************************************/
void Thumb_Run(Thumbwheel* ThumbDEV)
{
	static uint16_t	Front_time=0,Mid_time=0,Rear_time=0,Idle_time=0;//下拨时间，中键时间，上拨时间，空闲时间
	static uint8_t	Long_flag=0;//长按标记
	if (ThumbDEV->Call_Count<=0)
	{
		Set_Time(&ThumbDEV->Call_Count,Thumbwheel_Call_T);//重装载 调用周期计数

/*----------1.扫描拨轮的中键-----------*/
		ThumbDEV->Mid_State 	= 	Get_ThumbPort_State(ThumbDEV->Mid_Port,ThumbDEV->Mid_Pin);
		ThumbDEV->Front_State  	= 	Get_ThumbPort_State(ThumbDEV->Front_Port,ThumbDEV->Front_Pin);
		ThumbDEV->Rear_State  	= 	Get_ThumbPort_State(ThumbDEV->Rear_Port,ThumbDEV->Rear_Pin);

		if(ThumbDEV->Mid_State==Thumbwheel_Port_RESET )	//中键按下
		{
			Idle_time=0;
			Mid_time++;
			ThumbDEV->State = Thumbwheel_State_Press;//拨轮中键按下
			if(Mid_time>=Long_Time_trigger)//2s
			{
				if(Long_flag==0)
				{
					Long_flag=1;
					ThumbDEV->Event = Thumbwheel_Event_Press_long;//触发中键长按事件
					 return ;						
				}
			}
			
		} 
		else if (ThumbDEV->Front_State==Thumbwheel_Port_RESET)	
		{
			Idle_time=0;
			Front_time++;
			ThumbDEV->State = Thumbwheel_State_Front;//拨轮前拨
			if(Front_time>=Long_Time_trigger )//2s
			{
				if (Long_flag==0)
				{
					Long_flag=1;
					ThumbDEV->Event = Thumbwheel_Event_Front_long;//触发长按前拨事件
					 return;		
				}
			}
			
		}
		else if (ThumbDEV->Rear_State==Thumbwheel_Port_RESET)
		{
			Idle_time=0;
			Rear_time++;
			ThumbDEV->State = Thumbwheel_State_Rear;//拨轮后拨
			if(Rear_time>=Long_Time_trigger)//2s
			{
				if(Long_flag==0)
				{
					Long_flag=1;
					ThumbDEV->Event = Thumbwheel_Event_Rear_long;//触发后拨长按事件
					 return ;						
				}
			}
		
		}		
		else//拨轮处于无动作状态
		{
			if(Mid_time!=0 && Mid_time<Long_Time_trigger && Mid_time>=2)//按下事件低于2秒但大于20ms
			{
				
				ThumbDEV->Event = Thumbwheel_Event_Press;//触发中键短按事件
			}	
			else if(Front_time!=0 && Front_time<Long_Time_trigger && Front_time>=2)
			{
				
				ThumbDEV->Event = Thumbwheel_Event_Front;//触发前拨短按事件
			}
			else if(Rear_time!=0 && Rear_time<Long_Time_trigger && Rear_time>=2)
			{
				
				ThumbDEV->Event = Thumbwheel_Event_Rear;//触发后拨短按事件
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
			ThumbDEV->State =  Thumbwheel_State_Released;//编码器状态为松开
			 return ;//直接结束循环
		}
		//_______长按中键关机
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
* @Description    : 拨轮设备为LVGL设备新加入了一些函数和操作逻辑
* @Input          : ThumbDEV----设备结构体
* @Output         : 
* @Return         : None
*******************************************************************************/
#include "lv_port_indev.h"
#include "ui.h"
#include "ui_helpers.h"
lv_obj_t* current_scr;
void lvgl_Thumb_run(void)
{
	Thumb_Run(&Thumb_1);//拨轮运行函数


	//----界面切换处理
	lv_obj_t* scr = lv_scr_act();

	//----拨轮动作传入LVGL框架中
	if(Thumb_1.Event==Thumbwheel_Event_Front)//
	{encoder_diff = -1;}
	else if(Thumb_1.Event==Thumbwheel_Event_Rear)//
	{encoder_diff = 1;}
	else if(Thumb_1.Event==Thumbwheel_Event_Press)//
	{encoder_state = LV_INDEV_STATE_PRESSED;}	

	if(current_scr!=scr)
	{
		current_scr=scr;
		if(scr==ui_Main)	//进入Main页面添加改页面的可操作控件
		{
			lv_group_remove_all_objs(group);
			lv_group_add_obj(group,ui_MidBtn);		//第一个添加进去的控件，会被默认选中	
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
		else if (scr!=ui_Main && scr!=ui_StartUp && scr!=ui_SET)//其他页面没有可操作控件
		{
			lv_group_remove_all_objs(group);
		}
	}

	if (scr!=ui_Main && scr!=ui_StartUp && scr!=ui_SET)//没有可操作控件的界面
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
			if(Thumb_1.Event==Thumbwheel_Event_Press)//需要取消掉按下状态免得因为100ms延迟动画因为演示LVGL1ms的回调中会调用该动作
			{encoder_state=0;_ui_screen_change(ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);}
		}	

	}

	//________有拨轮时间发生蜂鸣器短音
	if(Thumb_1.Event != Thumbwheel_Event_None && Thumb_1.State ==  Thumbwheel_State_Released)
	{
		Thumb_1.Event = Thumbwheel_Event_None;
		PlaySound(0,1);
	}		
}


