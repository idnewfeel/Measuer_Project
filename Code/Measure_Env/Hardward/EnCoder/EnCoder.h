#ifndef _EnCoder_H
#define _EnCoder_H

#include "TIM_Management.h"


/*�����Զ���*/
#define Encoder_Port            GPIO_TypeDef*
#define Encoder_Pin             uint16_t
#define Encoder_Pin_State       GPIO_PinState     
#define Encoder_Call_T          (2)                  //������������
#define Encoder_Time            u_Time
#define Encoder_Port_SET        GPIO_PIN_SET            //GPIO�ڸߵ�ƽ
#define Encoder_Port_RESET      GPIO_PIN_RESET          //GPIO�ڵ͵�ƽ

/*���ܶ���*/
typedef enum {
 Encoder_State_Released=(0),   //�ɿ�
 Encoder_State_Press,           //����
 Encoder_State_Left,            //��ת
 Encoder_State_Right,        //��ת
}Encoder_State;

/*
�������豸�ṹ��
*/
typedef struct Encoder_Device
{
    /*A��������*/
    Encoder_Port        A_Port;         
    Encoder_Pin         A_Pin;     
    Encoder_Pin_State   A_State;    
    /*B��������*/
    Encoder_Port        B_Port;         
    Encoder_Pin         B_Pin;     
    Encoder_Pin_State   B_State;    
    /*SW��������*/
    Encoder_Port        SW_Port;         
    Encoder_Pin         SW_Pin;    
    Encoder_Pin_State   SW_State;   
    /*������״̬����*/
    Encoder_State       State;     

    Encoder_Time        Period;             //��������
    Encoder_Time        Call_Count;         //�������ڼ���
    Encoder_Time        Delay_Count;        //�ӳټ���


}Encoder;



extern Encoder Encoder1;

void Encoder_Device_Enroll(Encoder* EncoderDEV,Encoder_Port A_Port,Encoder_Pin A_Pin,
							Encoder_Port B_Port,Encoder_Pin B_Pin,
							Encoder_Port SW_Port,Encoder_Pin SW_Pin,
							Encoder_State state,Encoder_Time Period);
// void lvgl_encoder_run(void);


#endif

