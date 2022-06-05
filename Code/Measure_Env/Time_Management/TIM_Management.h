
#ifndef _TIM_Management_H
#define _TIM_Management_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
/*User�Զ�������*/

#define MAX_TAB_NUM			(20)			        			/*  ʱ���������  */
#define u_Time	        uint32_t	              /*  ʱ�����������������*/
#define T_Base          (1)                     /*  ʱ���ʱ����  */




#define	SUCCEED	(1)
#define FAIL		(0)

typedef struct {
	uint8_t 	obj_num;									  
	u_Time* 	obj_index[MAX_TAB_NUM];		  

	

}Timer_T;

extern Timer_T Timer_OBJ;

uint8_t Enroll_Time_Tab (Timer_T* TIM_T,u_Time* obj_inde);
void Set_Time(u_Time* time,u_Time time_num);
uint8_t Logout_Time_Tab (Timer_T* TIM_T,u_Time* obj_inde);



#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
