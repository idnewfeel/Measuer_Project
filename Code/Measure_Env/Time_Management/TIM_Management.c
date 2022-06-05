
/**
******************************************************************************
* 	@file 		TimeManagement.c
* 	@brief 		��������ʱ�������
*	@author	: 	��־��
******************************************************************************
*	@Description�������ܻ�����Ϊ��ʵ��ʱ������
*
******************************************************************************
* 	˵����ʱ��������ô���					������λ1ms
* 	Ҫʹ��ʱ�������Ҫʹ��					Enroll_Time_Tab 	��������Ҫ��ʱ�ı���������Ӧ�ú�ʱ����еı����������ͱ���һ�£� ע�ᵽʱ�����
* 	�� 1ms�Ķ�ʱ���ж��е���				Time_Tab_minus		������ʱ������Ѿ�ע��ı������� -- ����
* 	�ڼ���0�����							Set_Time			�����Լ�ʱ�������и�ֵ
* 	�ڲ�����Ҫ��������ʱ����				Logout_Time_Tab 	��������ʱ������ʱ�����ɾ��
*	ͨ����TIM_Management.h���޸�			MAX_TAB_NUM			�궨�����ı�ʱ���ĸ���
*
******************************************************************************
*/


/**
*	ע�⣺
*	��ʱ�����ĳ�ֵ����Ϊ0����ʱ��������������Ӧ�ú�ʱ����еı���һ�£�������

typedef struct {

	uint8_t 		obj_num;									//ʱ���ĸ���
	u_Time* 	obj_index[MAX_TAB_NUM];			//ʱ��������������ں궨����
	
}Timer_T;

*/




#include "TIM_Management.h"

/*	�ⲿ����		*/
#include "tim.h"
#include "lvgl.h"

#define		TIM_Num		htim1



Timer_T Timer_OBJ ={
			.obj_num = 0,
			.obj_index = {NULL},
			
};


/*******************************************************************************
* @FunctionName  : Set_Time
* @Description    : ����ʱ��
* @Input          : uint32_t* time---����ʱ�����ָ��,uint32_t time_num---����ʱ������
* @Output         : 
* @Return         : 
*******************************************************************************/
void Set_Time(u_Time* time,u_Time time_num)
{
	*time = time_num;
}

 /*******************************************************************************
* @FunctionName  : Enroll_Time_Tab
* @Description    : ����Ŀ��ʱ�����ע�ᵽʱ�����
* @Input          : Timer_T* TIM_T---ʱ���ṹ��,uint32_t* obj_inde---ʱ�����ָ��
* @Output         : 
* @Return         : �ɹ����� SUCCEED  ʧ�ܷ���FAIL
*******************************************************************************/
uint8_t Enroll_Time_Tab (Timer_T* TIM_T,u_Time* obj_inde)
{
	uint8_t num = TIM_T->obj_num;
	if(num<MAX_TAB_NUM)
	{
		if(obj_inde!=NULL)
		{
			TIM_T->obj_index[num] = obj_inde;	//ʱ�����ʱ��ָ��ָ��
			TIM_T->obj_num++;	//ʱ����������++
			return SUCCEED;
		}	
		else
			return FAIL;
	}
	else
		return FAIL;
}
 /*******************************************************************************
* @FunctionName  : Logout_Time_Tab
* @Description    : ����Ŀ��ʱ�������ʱ���ע��
* @Input          : Timer_T* TIM_T---ʱ���ṹ��,uint32_t* obj_inde---ʱ�����ָ��
* @Output         : 
* @Return         : �ɹ����� SUCCEED  ʧ�ܷ���FAIL
*******************************************************************************/

uint8_t Logout_Time_Tab (Timer_T* TIM_T,u_Time* obj_inde)
{
	u_Time*	temp_p	=	obj_inde;
	uint8_t	i	=	0;
	uint8_t	j	=	0;
	for(i=0;i<TIM_T->obj_num;i++)
	{
		if(temp_p	==	TIM_T->obj_index[i])
		{
			TIM_T->obj_index[i]	=		NULL;//ɾ������ʱ��
			TIM_T->obj_num-=1;
			for(j=i;j<TIM_T->obj_num;j++)
			{
				TIM_T->obj_index[j]	=	TIM_T->obj_index[j+1];
			}
			TIM_T->obj_index[j]	=	NULL;
			return	SUCCEED;
		}
	}
	return FAIL;	//û��ע������ҵ���ʱ��
}




 /*******************************************************************************
* @FunctionName  : Time_Tab_minus
* @Description    : ��ʱ����ڵ�ע���ʱ�� ȫ����1
* @Input          : Timer_T* TIM_T---ʱ���ṹ��
* @Output         : 
* @Return         : �ɹ����� SUCCEED  ʧ�ܷ���FAIL
*******************************************************************************/
void Time_Tab_minus(Timer_T* TIM_T)
{
	uint8_t num = TIM_T->obj_num;
	uint8_t i = 0;
	
	for(i=0;i<num;i++)
	{
		if(      (*(TIM_T->obj_index[i]))>0      )
		{
			(*(TIM_T->obj_index[i])) -= T_Base;
		}
		
	}
}



 /*******************************************************************************
* @FunctionName  : 	HAL_TIM_PeriodElapsedCallback
* @Description    : STM32�Ķ�ʱ���жϻص�����
* @Input          : Timer_T* TIM_T---ʱ���ṹ��
* @Output         : 
* @Return         : �ɹ����� SUCCEED  ʧ�ܷ���FAIL
*******************************************************************************/


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==(&TIM_Num))
	{/*�ж�����1ms*/
			Time_Tab_minus(&Timer_OBJ);
			lv_tick_inc(1);//lvgl �� 1ms ����
	}

}



