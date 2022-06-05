#include "beep.h" 


Beep BEEP_DEV;

static uint16_t m_u16Cycles;           //循环播放次数
static uint8_t m_u8BeepOnTime;        //打开蜂鸣器的时间
static uint8_t m_u8BeepOffTime;       //关闭蜂鸣器的时间
static uint8_t m_u8BeepCount    =   0;    //循环一次播放和关闭的次数


 /*******************************************************************************
* @FunctionName   : Beep_Device_Enroll
* @Description    : 将蜂鸣器属性注册到设备结构体z中
* @Input          : BeepDEV----设备结构体  tim----PWM输出定时器  ch -----PWM输出通道
*						   			period----调用周期
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
* @Description    : 蜂鸣器设备运行函数
* @Input          : BeepDEV----设备结构体
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
        {                               //循环播放完毕返回
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

        m_u8BeepCount++;                                     //播放一次后 计数器加1
        if(m_u8BeepCount > (m_u8BeepOnTime + m_u8BeepOffTime))
        {                                                     //打开蜂鸣器和关闭蜂鸣器的时间为一次计数
            m_u8BeepCount  =   0;
            m_u16Cycles--;
        }
		Set_Time(&BeepDEV->Count,BeepDEV->Period);	//重装载 闪烁周期计数变量
	}
}

void PlaySound(uint8_t u8Mode,uint16_t u16Cnt)                 //选择播放模式 ，播放次数
{
    switch(u8Mode)
    {
        case 0:
            m_u8BeepOnTime  =   200/Beep_Call_T;         //短音 200ms;   SYS_TICK_BASE 系统调用频率
            m_u8BeepOffTime =   0;
            break;

        case 1:
            m_u8BeepOnTime  =   800/Beep_Call_T;         //中长音   800ms
            m_u8BeepOffTime =   800/Beep_Call_T;
            break;

        case 2:
            m_u8BeepOnTime  =   1500/Beep_Call_T;         //长音        1500ms
            m_u8BeepOffTime =   0;
            break;
       
        case 3:
            m_u8BeepOnTime  =   50/Beep_Call_T;           //超duan音
            m_u8BeepOffTime =   20/Beep_Call_T;
            break;
        case 4:
            m_u8BeepOnTime  =   0;          //超长音
            m_u8BeepOffTime =   0;
            break;
    }
    m_u16Cycles         =   u16Cnt;    
}
