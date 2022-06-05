#ifndef  _BUZ_H_
#define  _BUZ_H_

#include "TIM_Management.h"
#include "tim.h"

#define Beep_TIM		TIM_HandleTypeDef*
#define Beep_Channel	uint32_t
#define Beep_period     u_Time 
#define Beep_Call_T 	(10)              //ϵͳʱ�� 



typedef struct Beep_Device
{
    Beep_TIM    			TIM;      				//������PWM����Ķ�ʱ��  
    Beep_Channel      CHANNEL;          //������PWM�����ͨ��
		
    Beep_period   Period;               //��������������
    Beep_period   Count;                //�������������ڼ���
}Beep;

extern Beep BEEP_DEV;

#define BUZ_ON(a,b)  	HAL_TIM_PWM_Start(a,b)
#define BUZ_OFF(a,b) 	HAL_TIM_PWM_Stop(a,b)

void Beep_Device_Enroll(Beep* BeepDEV,Beep_TIM tim,Beep_Channel ch,Beep_period Period);
void BeepProc(Beep* BeepDEV);
void PlaySound(uint8_t u8Mode,uint16_t u16Cnt);

#endif

