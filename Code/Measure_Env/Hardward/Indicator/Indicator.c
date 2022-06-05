#include "Indicator.h"

Indicator LED1;
 

 /*******************************************************************************
* @FunctionName   : Indicator_Device_Enroll
* @Description    : ��ָʾ������ע�ᵽ�豸�ṹ��z��
* @Input          : IndiDEV----�豸�ṹ��  Port----�豸IO��  Pin -----�豸���ź� 
*					state------�豸״̬	   period----�豸״̬��ת����
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
* @Description    : ָʾ���豸���к���
* @Input          : IndiDEV----�豸�ṹ��
* @Output         : 
* @Return         : None
*******************************************************************************/
void Indicator_Run(Indicator* IndiDEV)
{
	if (IndiDEV->Count<=0)
	{
		IndiDEV->State = !IndiDEV->State;
		HAL_GPIO_WritePin(IndiDEV->Port,IndiDEV->Pin,IndiDEV->State);

		Set_Time(&IndiDEV->Count,IndiDEV->Period);	//��װ�� ��˸���ڼ�������
	}

}

 /*******************************************************************************
* @FunctionName   : Indicator_amend_Period
* @Description    : ָʾ���޸�״̬��ת����
* @Input          : IndiDEV----�豸�ṹ��  period----�豸״̬��ת����
* @Output         : 
* @Return         : None
*******************************************************************************/
void Indicator_amend_Period(Indicator* IndiDEV,Inid_period Period)
{	
	IndiDEV->Period = Period;

}
