#ifndef _EnCoder_H
#define _EnCoder_H

#include "TIM_Management.h"


/*适配自定义*/
#define Encoder_Port            GPIO_TypeDef*
#define Encoder_Pin             uint16_t
#define Encoder_Pin_State       GPIO_PinState     
#define Encoder_Call_T          (2)                  //函数调用周期
#define Encoder_Time            u_Time
#define Encoder_Port_SET        GPIO_PIN_SET            //GPIO口高电平
#define Encoder_Port_RESET      GPIO_PIN_RESET          //GPIO口低电平

/*功能定义*/
typedef enum {
 Encoder_State_Released=(0),   //松开
 Encoder_State_Press,           //按下
 Encoder_State_Left,            //左转
 Encoder_State_Right,        //右转
}Encoder_State;

/*
彪马其设备结构体
*/
typedef struct Encoder_Device
{
    /*A引脚描述*/
    Encoder_Port        A_Port;         
    Encoder_Pin         A_Pin;     
    Encoder_Pin_State   A_State;    
    /*B引脚描述*/
    Encoder_Port        B_Port;         
    Encoder_Pin         B_Pin;     
    Encoder_Pin_State   B_State;    
    /*SW引脚描述*/
    Encoder_Port        SW_Port;         
    Encoder_Pin         SW_Pin;    
    Encoder_Pin_State   SW_State;   
    /*编码器状态描述*/
    Encoder_State       State;     

    Encoder_Time        Period;             //调用周期
    Encoder_Time        Call_Count;         //调用周期计数
    Encoder_Time        Delay_Count;        //延迟计数


}Encoder;



extern Encoder Encoder1;

void Encoder_Device_Enroll(Encoder* EncoderDEV,Encoder_Port A_Port,Encoder_Pin A_Pin,
							Encoder_Port B_Port,Encoder_Pin B_Pin,
							Encoder_Port SW_Port,Encoder_Pin SW_Pin,
							Encoder_State state,Encoder_Time Period);
// void lvgl_encoder_run(void);


#endif

