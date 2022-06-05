
/**
******************************************************************************
* 	@file 		TimeManagement.c
* 	@brief 		这个框架是时间管理框架
*	@author	: 	罗志祥
******************************************************************************
*	@Description：这个框架机器简单为了实现时间表管理
*
******************************************************************************
* 	说明：时间管理配置代码					基数单位1ms
* 	要使用时间管理需要使用					Enroll_Time_Tab 	函数将需要计时的变量（变量应该和时间表中的变量数据类型保持一致） 注册到时间表中
* 	在 1ms的定时器中断中调用				Time_Tab_minus		函数对时间表中已经注册的变量挨个 -- 操作
* 	在减到0后调用							Set_Time			函数对计时变量进行赋值
* 	在不再需要变量计数时调用				Logout_Time_Tab 	函数将计时变量从时间表中删除
*	通过再TIM_Management.h中修改			MAX_TAB_NUM			宏定义来改变时间表的个数
*
******************************************************************************
*/


/**
*	注意：
*	计时变量的初值不能为0，计时变量的数据类型应该和时间表中的变量一致！！！！

typedef struct {

	uint8_t 		obj_num;									//时间表的个数
	u_Time* 	obj_index[MAX_TAB_NUM];			//时间表中数据类型在宏定义中
	
}Timer_T;

*/




#include "TIM_Management.h"

/*	外部声明		*/
#include "tim.h"
#include "lvgl.h"

#define		TIM_Num		htim1



Timer_T Timer_OBJ ={
			.obj_num = 0,
			.obj_index = {NULL},
			
};


/*******************************************************************************
* @FunctionName  : Set_Time
* @Description    : 设置时间
* @Input          : uint32_t* time---传入时间变量指针,uint32_t time_num---传入时间数据
* @Output         : 
* @Return         : 
*******************************************************************************/
void Set_Time(u_Time* time,u_Time time_num)
{
	*time = time_num;
}

 /*******************************************************************************
* @FunctionName  : Enroll_Time_Tab
* @Description    : 将该目标时间变量注册到时间表中
* @Input          : Timer_T* TIM_T---时间表结构体,uint32_t* obj_inde---时间变量指针
* @Output         : 
* @Return         : 成功返回 SUCCEED  失败返回FAIL
*******************************************************************************/
uint8_t Enroll_Time_Tab (Timer_T* TIM_T,u_Time* obj_inde)
{
	uint8_t num = TIM_T->obj_num;
	if(num<MAX_TAB_NUM)
	{
		if(obj_inde!=NULL)
		{
			TIM_T->obj_index[num] = obj_inde;	//时间表中时间指针指向
			TIM_T->obj_num++;	//时间表变量数量++
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
* @Description    : 将该目标时间变量从时间表注销
* @Input          : Timer_T* TIM_T---时间表结构体,uint32_t* obj_inde---时间变量指针
* @Output         : 
* @Return         : 成功返回 SUCCEED  失败返回FAIL
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
			TIM_T->obj_index[i]	=		NULL;//删除掉该时间
			TIM_T->obj_num-=1;
			for(j=i;j<TIM_T->obj_num;j++)
			{
				TIM_T->obj_index[j]	=	TIM_T->obj_index[j+1];
			}
			TIM_T->obj_index[j]	=	NULL;
			return	SUCCEED;
		}
	}
	return FAIL;	//没在注册表内找到该时间
}




 /*******************************************************************************
* @FunctionName  : Time_Tab_minus
* @Description    : 将时间表内的注册的时间 全部减1
* @Input          : Timer_T* TIM_T---时间表结构体
* @Output         : 
* @Return         : 成功返回 SUCCEED  失败返回FAIL
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
* @Description    : STM32的定时器中断回调函数
* @Input          : Timer_T* TIM_T---时间表结构体
* @Output         : 
* @Return         : 成功返回 SUCCEED  失败返回FAIL
*******************************************************************************/


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==(&TIM_Num))
	{/*中断周期1ms*/
			Time_Tab_minus(&Timer_OBJ);
			lv_tick_inc(1);//lvgl 的 1ms 心跳
	}

}



