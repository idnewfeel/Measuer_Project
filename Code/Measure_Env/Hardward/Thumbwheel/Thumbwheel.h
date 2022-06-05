#ifndef _ThumbWheel_H
#define _ThumbWheel_H

#include "TIM_Management.h"
#include "system.h"




/*�����Զ���*/
#define Thumbwheel_Port            GPIO_TypeDef*
#define Thumbwheel_Pin             uint16_t
#define Thumbwheel_Pin_State       GPIO_PinState     
#define Thumbwheel_Call_T          (10)                  //������������
#define Thumbwheel_Time            u_Time
#define Thumbwheel_Port_SET        GPIO_PIN_SET            //GPIO�ڸߵ�ƽ
#define Thumbwheel_Port_RESET      GPIO_PIN_RESET          //GPIO�ڵ͵�ƽ
#define	Long_Time_trigger					(100)				   //���������¼�


/*���ܶ���*/
typedef enum {
	Thumbwheel_State_Released=(0),    //�ɿ�
	Thumbwheel_State_Press,           //�м��̰�
	Thumbwheel_State_Front,            //��������
	Thumbwheel_State_Rear,          	 //��������
	
	// Thumbwheel_State_Press_long,		//�м�����
	// Thumbwheel_State_Down_long,			//���ֳ�������
	// Thumbwheel_State_Up_long,				//���ֳ�������
	
	// Thumbwheel_State_Press_two,			//�м�������
	// Thumbwheel_State_Down_two,			//�������϶�����
	// Thumbwheel_State_Up_two,				//�������¶�����
	

	
}Thumbwheel_State;


typedef enum {
	Thumbwheel_Event_None=(0),          //��dd
	Thumbwheel_Event_Press,           //�м��̰�
	Thumbwheel_Event_Front,            //��������
	Thumbwheel_Event_Rear,          	 //��������
	
	Thumbwheel_Event_Press_long,			//�м�����
	Thumbwheel_Event_Front_long,			//���ֳ�������
	Thumbwheel_Event_Rear_long,				//���ֳ�������
	
	Thumbwheel_Event_Press_two,			//�м�������
	Thumbwheel_Event_Front_two,			//�������϶�����
	Thumbwheel_Event_Rear_two,				//�������¶�����
	
    
	
}Thumbwheel_Event;


/*
�������豸�ṹ��
*/
typedef struct ThumbWheel_Device
{
    /*Down��������*/
    Thumbwheel_Port        Front_Port;         
    Thumbwheel_Pin         Front_Pin;     
    Thumbwheel_Pin_State   Front_State;    
    /*UP��������*/
    Thumbwheel_Port        Rear_Port;         
    Thumbwheel_Pin         Rear_Pin;     
    Thumbwheel_Pin_State   Rear_State;    
    /*MID��������*/
    Thumbwheel_Port        Mid_Port;         
    Thumbwheel_Pin         Mid_Pin;    
    Thumbwheel_Pin_State   Mid_State;   
	
    /*������״̬����*/
    Thumbwheel_State       State; 
    /*�������¼�*/ 
    Thumbwheel_Event       Event; 


    Thumbwheel_Time        Period;             //��������
    Thumbwheel_Time        Call_Count;         //�������ڼ���
    Thumbwheel_Time        Delay_Count;        //�ӳټ���


}Thumbwheel;



extern Thumbwheel Thumb_1;

void Thumb_Device_Enroll(Thumbwheel* ThumbDEV,Thumbwheel_Port Front_Port,Thumbwheel_Pin Front_Pin,
							Thumbwheel_Port Rear_Port,Thumbwheel_Pin Rear_Pin,
							Thumbwheel_Port Mid_Port,Thumbwheel_Pin Mid_Pin,
							Thumbwheel_State state,Thumbwheel_Time Period);
void lvgl_Thumb_run(void);


#endif

