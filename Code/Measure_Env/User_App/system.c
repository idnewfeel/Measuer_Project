#include "system.h"


DEVICE_UI_PARA UI_Para;

 /*******************************************************************************
* @FunctionName  : System_Init
* @Description    : 
* @Input          : None
* @Output         : 
* @Return         : None
*******************************************************************************/



void System_Init(void)
{
	//----打开供电NMOS开关
	POWER_ON;	
//------------------------------------------------------------------------------------------------------

	//----指示灯设备注册属性
	Indicator_Device_Enroll(&LED1,LED_GPIO_Port,LED_Pin,Inid_Open,Inid_DEVNormal_Fast);//198毫秒调用一次
	//----LED1的计时变量注册到时间表
	Enroll_Time_Tab(&Timer_OBJ,&LED1.Count);

//------------------------------------------------------------------------------------------------------

	//----拨轮设备注册属性
	Thumb_Device_Enroll(&Thumb_1,FRONT_GPIO_Port,FRONT_Pin,\
							REAR_GPIO_Port,REAR_Pin,\
							MID_GPIO_Port,MID_Pin,\
							Thumbwheel_State_Released,Thumbwheel_Call_T);//10ms调用一次
	//----拨轮的计时变量注册到时间表
	Enroll_Time_Tab(&Timer_OBJ,&Thumb_1.Call_Count);	
//-----------------------------------------------------------------------------------------------
	//----蜂鸣器设备注册属性
	Beep_Device_Enroll(&BEEP_DEV,&htim5,TIM_CHANNEL_2,Beep_Call_T);
		//----蜂鸣器的计时变量注册到时间表
	Enroll_Time_Tab(&Timer_OBJ,&BEEP_DEV.Count);	
//------------------------------------------------------------------------------------------------------
	//----SHT31注册属性
	SHT_Device_Enroll(&SHT31,SDA_GPIO_Port,SDA_Pin,SCL_GPIO_Port,SCL_Pin,SHT31_Call_T,
							&hi2c1);
	Enroll_Time_Tab(&Timer_OBJ,&SHT31.Count);
//------------------------------------------------------------------------------------------------------
	//----SGP40注册属性
	SGP_Device_Enroll(&SGP40,SDA_GPIO_Port,SDA_Pin,SCL_GPIO_Port,SCL_Pin,SGP40_Call_T,
							&hi2c1);
	Enroll_Time_Tab(&Timer_OBJ,&SGP40.Count);
//------------------------------------------------------------------------------------------------------
	//----MAX17048注册属性
	MAX17048_Device_Enroll(&max17048,MAX17048_Call_T,&hi2c1);
	Power_On_Reset(&max17048);	//执行复位
	Enroll_Time_Tab(&Timer_OBJ,&max17048.Count);	

//------------------------------------------------------------------------------------------------------



	//----UI载入计时变量注册到时间表
	Enroll_Time_Tab(&Timer_OBJ,&UILoadCnt);			//开机画面 结束后不就注销掉
	Enroll_Time_Tab(&Timer_OBJ,&UIUpdataCnt);	 	//199ms调用一次
	Enroll_Time_Tab(&Timer_OBJ,&UI_Para.Count);	 	//100ms调用一次
	
	//----启动定时器1 
	HAL_TIM_Base_Start_IT(&htim1);
	
	//----UI补充初始化
	User_UI_Init();
	
	//----电池开始采样
	Battery_Start();
	
	UI_Para.Rollernum = 100;//赋值非0值
}







 /*******************************************************************************
* @FunctionName  	: UI_PARA_Load
* @Description    : 	UI数据载入
* @Input          : None
* @Output         : 
* @Return         : None
*******************************************************************************/
#include "lcd_init.h"

void UI_PARA_Load(void)//UI100ms更新一次
{

	uint16_t rollerNum =0;
	static uint8_t Back_temp=0;
	if(UI_Para.Count<=0)
	{
		
		if(SHT31.WorkState != SHT31_Offline && SGP40.WorkState != SGP40_Offline && max17048.WorkState != MAX17048_Offline)
		{
			UI_Para.IIC_State = 1;//IIC总线正常
		}
		else
		{
			UI_Para.IIC_State = 0;	//IIC总线异常
		}

		UI_Para.Temperature = SHT31.T/1000;
		UI_Para.RH = SHT31.RH/1000;
		UI_Para.VocRaw = SGP40.VOC_RAW;
		UI_Para.TVocIndex = SGP40.VOC_Index;

		//背光亮度值

		UI_Para.BackLight = lv_slider_get_value(ui_SWPower);
		if(Back_temp!=UI_Para.BackLight)
		{
			Back_temp=UI_Para.BackLight;
			if(UI_Para.BackLight>100)
			{UI_Para.BackLight=100;}
			if(UI_Para.BackLight<=5)
			{UI_Para.BackLight=5;}

			LCD_BLK_Set(UI_Para.BackLight);
		}




		rollerNum = lv_roller_get_selected(ui_Roller2);//滚轮值获取
		if(UI_Para.Rollernum != rollerNum)
		{
			UI_Para.Rollernum=rollerNum;
			
			memset(UI_Para.Chart_RH,0,120);
			memset(UI_Para.Chart_T,0,120);
			memset(UI_Para.Chart_TVOC,0,120);


			lv_chart_remove_series(ui_TChart,Tser);
			lv_chart_remove_series(ui_RHChart,RHser);
			lv_chart_remove_series(ui_TVOCChart,TVOCser);

			UI_Para.Chart_Num=0;
			UI_Para.Open_Minute=0;

			Tser = lv_chart_add_series(ui_TChart, lv_palette_main(LV_PALETTE_TEAL), LV_CHART_AXIS_PRIMARY_Y);
			RHser = lv_chart_add_series(ui_RHChart, lv_palette_main(LV_PALETTE_TEAL), LV_CHART_AXIS_PRIMARY_Y);
			TVOCser = lv_chart_add_series(ui_TVOCChart, lv_palette_main(LV_PALETTE_TEAL), LV_CHART_AXIS_PRIMARY_Y);

			lv_chart_set_update_mode(ui_TChart,LV_CHART_UPDATE_MODE_CIRCULAR);//---循环模式
			lv_chart_set_update_mode(ui_RHChart,LV_CHART_UPDATE_MODE_CIRCULAR);//---循环模式
			lv_chart_set_update_mode(ui_TVOCChart,LV_CHART_UPDATE_MODE_CIRCULAR);//---循环模式
			
			UI_Para.X_hour = (rollerNum)*2;	//得到X轴最大时间
			if(rollerNum==7)
			UI_Para.X_hour=24;					
		}

		if(UI_Para.X_hour==0)
		{
			UI_Para.Open_Sec++;
			if(UI_Para.Open_Sec>=20)//2sec, x_hour=0选择的是4分钟的X轴
			{
				UI_Para.Open_Sec=0;
				UI_Para.ChartUpdataFlag=1;
			}
		}

		UI_Para.Open_T++;
		if(UI_Para.Open_T>=600)//1分钟
		{
			UI_Para.Open_T=0;
			UI_Para.minute++;
			if(UI_Para.minute>=60)
			{
				UI_Para.minute=0;
				UI_Para.Hour++;
			}
			UI_Para.Open_Minute++;
			if(UI_Para.Open_Minute%(UI_Para.X_hour/2)==0 && UI_Para.X_hour)
			{
				UI_Para.ChartUpdataFlag=1;
			}

		}

		Set_Time(&UI_Para.Count,100);
	}
}


 /*******************************************************************************
* @FunctionName  	: System_Run
* @Description    : 
* @Input          : None
* @Output         : 
* @Return         : None
*******************************************************************************/
uint8_t sys_state= 0;
uint16_t sgp_idle_time = 0;
void System_Run(void)
{
	// uint8_t	reg[10] =	{0};
	
	
	Indicator_Run(&LED1);		//指示灯					//198ms
	lvgl_Thumb_run();			//LVGL适配编码器处理任务	 //1ms  //拨轮 10ms
	User_UI_Load();				//用户LVGL的UI补充代码		 //10ms 执行完不再执行
	BeepProc(&BEEP_DEV);		//蜂鸣器					//10ms
	User_UI_Data_Updata();		//UI数据更新				//199ms
	// Battery_Conversion();		//电池参数转换				//没有延时
	UI_PARA_Load();				//UI参数载入				//100ms
	if(sys_state == 0)
	{
		if(MAX17048_Run(&max17048)==MAX17048_Idle && SHT31_Run(&SHT31)==SHT31_Idle && sgp_idle_time>=1000)//MAX17048电池电量测量 96ms		//SHT31温湿度传感器测量  	//97ms
		{
			sys_state = 1;
		}	
		else if ((max17048.WorkState == MAX17048_Offline) || (SHT31.WorkState == SHT31_Offline))
		{
			sys_state = 1;
		}

	}
	else
	{
		if(SGP40_Run(&SGP40)==SGP40_Idle)			//SGP40气体传感器测量		//103ms
		{
			sgp_idle_time=0;
			sys_state=0;
		}
		else if(SGP40.Status == SGP_Offline)
		{
			sgp_idle_time=0;
			sys_state=0;			
		}
		
	}
}



