#include "Indicator.h"

Indicator LED1;
 

 /*******************************************************************************
* @FunctionName   : Indicator_Device_Enroll
* @Description    : 将指示灯属性注册到设备结构体z中
* @Input          : IndiDEV----设备结构体  Port----设备IO口  Pin -----设备引脚号 
*					state------设备状态	   period----设备状态反转周期
* @Output         : 
* @Return         : None
*******************************************************************************/
void Indicator_Device_Enroll(Indicator* IndiDEV,Inid_Port Port,Inid_Pin Pin,Inid_State state,Inid_period Period)
{
	IndiDEV->Port 	= 	Port;
	IndiDEV->Pin	=	Pin;
	IndiDEV->State	=	state;
	IndiDEV->Period =	Period; 
	IndiDEV->Count	=	Period;
}

 /*******************************************************************************
* @FunctionName   : Indicator_Run
* @Description    : 指示灯设备运行函数
* @Input          : IndiDEV----设备结构体
* @Output         : 
* @Return         : None
*******************************************************************************/
void Indicator_Run(Indicator* IndiDEV)
{
	if (IndiDEV->Count<=0)
	{
		IndiDEV->State = !IndiDEV->State;
		HAL_GPIO_WritePin(IndiDEV->Port,IndiDEV->Pin,IndiDEV->State);

		Set_Time(&IndiDEV->Count,IndiDEV->Period);	//重装载 闪烁周期计数变量
	}

}

 /*******************************************************************************
* @FunctionName   : Indicator_amend_Period
* @Description    : 指示灯修改状态反转周期
* @Input          : IndiDEV----设备结构体  period----设备状态反转周期
* @Output         : 
* @Return         : None
*******************************************************************************/
void Indicator_amend_Period(Indicator* IndiDEV,Inid_period Period)
{	
	IndiDEV->Period = Period;

}
