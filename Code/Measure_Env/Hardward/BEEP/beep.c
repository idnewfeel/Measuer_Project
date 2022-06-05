#include "beep.h" 


Beep BEEP_DEV;

static uint16_t m_u16Cycles;           //ѭ�����Ŵ���
static uint8_t m_u8BeepOnTime;        //�򿪷�������ʱ��
static uint8_t m_u8BeepOffTime;       //�رշ�������ʱ��
static uint8_t m_u8BeepCount    =   0;    //ѭ��һ�β��ź͹رյĴ���


 /*******************************************************************************
* @FunctionName   : Beep_Device_Enroll
* @Description    : ������������ע�ᵽ�豸�ṹ��z��
* @Input          : BeepDEV----�豸�ṹ��  tim----PWM�����ʱ��  ch -----PWM���ͨ��
*						   			period----��������
* @Output         : 
* @Return         : None
*******************************************************************************/
void Beep_Device_Enroll(Beep* BeepDEV,Beep_TIM tim,Beep_Channel ch,Beep_period Period)
{
	
	BeepDEV->TIM 		=   tim;
	BeepDEV->CHANNEL 	=   ch;
	BeepDEV->Period 	=	Period; 
	BeepDEV->Count		=	Period;
}

 /*******************************************************************************
* @FunctionName   : BeepProc
* @Description    : �������豸���к���
* @Input          : BeepDEV----�豸�ṹ��
* @Output         : 
* @Return         : None
*******************************************************************************/
extern uint16_t sgp_idle_time;
void BeepProc(Beep* BeepDEV)
{
	if (BeepDEV->Count<=0)
	{
		if(sgp_idle_time<1000)
		{
			sgp_idle_time+=10;
		}
        
        if(m_u16Cycles == 0)
        {                               //ѭ��������Ϸ���
            return;
        }

        if(m_u8BeepCount < m_u8BeepOnTime)
        {  
            BUZ_ON(BeepDEV->TIM,BeepDEV->CHANNEL);
                
        }
        else
        {
            BUZ_OFF(BeepDEV->TIM,BeepDEV->CHANNEL);
        }

        m_u8BeepCount++;                                     //����һ�κ� ��������1
        if(m_u8BeepCount > (m_u8BeepOnTime + m_u8BeepOffTime))
        {                                                     //�򿪷������͹رշ�������ʱ��Ϊһ�μ���
            m_u8BeepCount  =   0;
            m_u16Cycles--;
        }
		Set_Time(&BeepDEV->Count,BeepDEV->Period);	//��װ�� ��˸���ڼ�������
	}
}

void PlaySound(uint8_t u8Mode,uint16_t u16Cnt)                 //ѡ�񲥷�ģʽ �����Ŵ���
{
    switch(u8Mode)
    {
        case 0:
            m_u8BeepOnTime  =   200/Beep_Call_T;         //���� 200ms;   SYS_TICK_BASE ϵͳ����Ƶ��
            m_u8BeepOffTime =   0;
            break;

        case 1:
            m_u8BeepOnTime  =   800/Beep_Call_T;         //�г���   800ms
            m_u8BeepOffTime =   800/Beep_Call_T;
            break;

        case 2:
            m_u8BeepOnTime  =   1500/Beep_Call_T;         //����        1500ms
            m_u8BeepOffTime =   0;
            break;
       
        case 3:
            m_u8BeepOnTime  =   50/Beep_Call_T;           //��duan��
            m_u8BeepOffTime =   20/Beep_Call_T;
            break;
        case 4:
            m_u8BeepOnTime  =   0;          //������
            m_u8BeepOffTime =   0;
            break;
    }
    m_u16Cycles         =   u16Cnt;    
}
