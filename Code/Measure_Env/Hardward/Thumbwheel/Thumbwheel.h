#ifndef _ThumbWheel_H
#define _ThumbWheel_H

#include "TIM_Management.h"
#include "system.h"




/*适配自定义*/
#define Thumbwheel_Port            GPIO_TypeDef*
#define Thumbwheel_Pin             uint16_t
#define Thumbwheel_Pin_State       GPIO_PinState     
#define Thumbwheel_Call_T          (10)                  //函数调用周期
#define Thumbwheel_Time            u_Time
#define Thumbwheel_Port_SET        GPIO_PIN_SET            //GPIO口高电平
#define Thumbwheel_Port_RESET      GPIO_PIN_RESET          //GPIO口低电平
#define	Long_Time_trigger					(100)				   //长按触发事件


/*功能定义*/
typedef enum {
	Thumbwheel_State_Released=(0),    //松开
	Thumbwheel_State_Press,           //中键短按
	Thumbwheel_State_Front,            //拨轮向下
	Thumbwheel_State_Rear,          	 //拨轮向上
	
	// Thumbwheel_State_Press_long,		//中键长按
	// Thumbwheel_State_Down_long,			//拨轮长拨向下
	// Thumbwheel_State_Up_long,				//拨轮长拨向上
	
	// Thumbwheel_State_Press_two,			//中键二连击
	// Thumbwheel_State_Down_two,			//拨轮向上二连击
	// Thumbwheel_State_Up_two,				//拨轮向下二连击
	

	
}Thumbwheel_State;


typedef enum {
	Thumbwheel_Event_None=(0),          //无dd
	Thumbwheel_Event_Press,           //中键短按
	Thumbwheel_Event_Front,            //拨轮向下
	Thumbwheel_Event_Rear,          	 //拨轮向上
	
	Thumbwheel_Event_Press_long,			//中键长按
	Thumbwheel_Event_Front_long,			//拨轮长拨向下
	Thumbwheel_Event_Rear_long,				//拨轮长拨向上
	
	Thumbwheel_Event_Press_two,			//中键二连击
	Thumbwheel_Event_Front_two,			//拨轮向上二连击
	Thumbwheel_Event_Rear_two,				//拨轮向下二连击
	
    
	
}Thumbwheel_Event;


/*
彪马其设备结构体
*/
typedef struct ThumbWheel_Device
{
    /*Down引脚描述*/
    Thumbwheel_Port        Front_Port;         
    Thumbwheel_Pin         Front_Pin;     
    Thumbwheel_Pin_State   Front_State;    
    /*UP引脚描述*/
    Thumbwheel_Port        Rear_Port;         
    Thumbwheel_Pin         Rear_Pin;     
    Thumbwheel_Pin_State   Rear_State;    
    /*MID引脚描述*/
    Thumbwheel_Port        Mid_Port;         
    Thumbwheel_Pin         Mid_Pin;    
    Thumbwheel_Pin_State   Mid_State;   
	
    /*编码器状态描述*/
    Thumbwheel_State       State; 
    /*编码器事件*/ 
    Thumbwheel_Event       Event; 


    Thumbwheel_Time        Period;             //调用周期
    Thumbwheel_Time        Call_Count;         //调用周期计数
    Thumbwheel_Time        Delay_Count;        //延迟计数


}Thumbwheel;



extern Thumbwheel Thumb_1;

void Thumb_Device_Enroll(Thumbwheel* ThumbDEV,Thumbwheel_Port Front_Port,Thumbwheel_Pin Front_Pin,
							Thumbwheel_Port Rear_Port,Thumbwheel_Pin Rear_Pin,
							Thumbwheel_Port Mid_Port,Thumbwheel_Pin Mid_Pin,
							Thumbwheel_State state,Thumbwheel_Time Period);
void lvgl_Thumb_run(void);


#endif

