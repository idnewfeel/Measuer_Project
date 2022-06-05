#include "User_UI.h"




 /*******************************************************************************
* @FunctionName  : User_UI_Load
* @Description    : �û�UI���붯��
* @Input          : None
* @Output         : 
* @Return         : None
*******************************************************************************/

u_Time UILoadCnt = 0;

void User_UI_Load(void)
{
	static uint16_t Bar_Num=0;
	if (UILoadCnt<=0)
	{
		if(Bar_Num<100)
		{Bar_Num++;}
		
		lv_bar_set_value(ui_Loading, Bar_Num, LV_ANIM_ON);//������++
		Set_Time(&UILoadCnt,10);	//��װ�� ��˸���ڼ�������
		
		if(Bar_Num==100)
		{
			_ui_screen_change(ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);
			lv_slider_set_value(ui_SWPower,50,LV_ANIM_ON);


			lv_group_remove_all_objs(group);
			lv_group_add_obj(group,ui_MidBtn);			
			lv_group_add_obj(group,ui_RightBtn);
			lv_group_add_obj(group,ui_LeftBtn);

			Bar_Num++;
			Logout_Time_Tab(&Timer_OBJ,&UILoadCnt);//��������ʱ���ע��
		}
	}

}

 /*******************************************************************************
* @FunctionName  : User_UI_Init
* @Description    : �û����UI
* @Input          : None
* @Output         : 
* @Return         : None
*******************************************************************************/


#define T_Defaul_Min 	0
#define	T_Defaul_Max	120
#define	RH_Defaul_Min	0
#define	RH_Defaul_Max	100
#define	VOC_Defaul_Min	0
#define	VOC_Defaul_Max	500

lv_chart_series_t * Tser;
lv_chart_series_t * RHser;
lv_chart_series_t * TVOCser;

void User_UI_Init(void)
{
	//1.------------------���ͼ������-----------------
	/*���õ�ص���ͼ��*/
	lv_label_set_text(ui_BAT,LV_SYMBOL_BATTERY_FULL );

	//2.------------------��������-----------------
	/*��������û��դ��*/
	lv_chart_set_div_line_count(ui_TChart, 0, 0);
	lv_chart_set_div_line_count(ui_RHChart, 0, 0);
	lv_chart_set_div_line_count(ui_TVOCChart, 0, 0);

	/*�������ߵĵ���*/
	lv_chart_set_point_count(ui_TChart, 120);
	lv_chart_set_point_count(ui_RHChart, 120);
	lv_chart_set_point_count(ui_TVOCChart, 120);

	/*�������ߵĵ�Ĵ�С*/
	lv_obj_set_style_size(ui_TChart, 0, LV_PART_INDICATOR);
	lv_obj_set_style_size(ui_RHChart, 0, LV_PART_INDICATOR);
	lv_obj_set_style_size(ui_TVOCChart, 0, LV_PART_INDICATOR);

	/*�������ᴹֱ��Χ*/
	lv_chart_set_range(ui_TChart, LV_CHART_AXIS_PRIMARY_Y, T_Defaul_Min, T_Defaul_Max);//ȡ����ֵ���ֵ����Сֵ������5��Ϊ��Χ
	lv_chart_set_range(ui_RHChart, LV_CHART_AXIS_PRIMARY_Y, RH_Defaul_Min, RH_Defaul_Max);	//ȡ����ֵ���ֵ����Сֵ������5%
	lv_chart_set_range(ui_TVOCChart, LV_CHART_AXIS_PRIMARY_Y, VOC_Defaul_Min, VOC_Defaul_Max);//ȡ����ֵ���ֵ����Сֵ������50����

	/*�������ߵĸ���ģʽ��*/
	lv_chart_set_update_mode(ui_TChart,LV_CHART_UPDATE_MODE_CIRCULAR);//---ѭ��ģʽ
	lv_chart_set_update_mode(ui_RHChart,LV_CHART_UPDATE_MODE_CIRCULAR);//---ѭ��ģʽ
	lv_chart_set_update_mode(ui_TVOCChart,LV_CHART_UPDATE_MODE_CIRCULAR);//---ѭ��ģʽ

	/*���ÿ̶���*/
    lv_chart_set_axis_tick(ui_TChart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 5, true, 40);
    lv_chart_set_axis_tick(ui_TChart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 3, 6, false, 30);
    lv_chart_set_axis_tick(ui_RHChart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 5, true, 40);
    lv_chart_set_axis_tick(ui_RHChart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 3, 6, false, 30);
    lv_chart_set_axis_tick(ui_TVOCChart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 5, true, 40);
    lv_chart_set_axis_tick(ui_TVOCChart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 3, 6, false, 30);


	/*Ϊͼ�������������*/
	Tser = lv_chart_add_series(ui_TChart, lv_palette_main(LV_PALETTE_TEAL), LV_CHART_AXIS_PRIMARY_Y);
	RHser = lv_chart_add_series(ui_RHChart, lv_palette_main(LV_PALETTE_TEAL), LV_CHART_AXIS_PRIMARY_Y);
	TVOCser = lv_chart_add_series(ui_TVOCChart, lv_palette_main(LV_PALETTE_TEAL), LV_CHART_AXIS_PRIMARY_Y);


}



 /*******************************************************************************
* @FunctionName  : Chart_Buff_Add_NewData
* @Description    : �����߻�������ʱ����ã����߻�����������ݣ�������ǰ�������ݼ��뵽���
* @Input          : None
* @Output         : 
* @Return         : None
*******************************************************************************/
static void Chart_Buff_Add_NewData(int16_t* Buff, int16_t BuffSize,int16_t data)
{
	int16_t i = 0 ;
	
	for(i=0;i<BuffSize-1;i++)
	{
		Buff[i] = Buff[i+1];
	}
	Buff[i] = data;
}
 /*******************************************************************************
* @FunctionName  : Chart_Buff_outMaxMin
* @Description    : ���߻��������Сֵ���
* @Input          : None
* @Output         : 
* @Return         : None
*******************************************************************************/
static void Chart_Buff_outMaxMin(int16_t* buff,int16_t buffsize,int16_t* max ,int16_t*min,uint8_t* flag)
{
	int16_t i = 0;
	*min=32767;
	*max=0;
	for(i=0;i<buffsize;i++)
	{
		if(buff[i]>*max)
		{*max=buff[i];*flag=1;}
	}
	for(i=0;i<buffsize;i++)
	{
		if(buff[i]<*min)
		{*min=buff[i];*flag=1;}
	}
}
 /*******************************************************************************
* @FunctionName  : lvgl_ChartRange_refresh
* @Description    : LVGLȷ�����ߵ������Сֵ
* @Input          : None
* @Output         : 
* @Return         : None
*******************************************************************************/
static void lvgl_ChartRange_refresh(int16_t* buff,int16_t buffsize,int16_t* max ,int16_t*min,uint8_t* flag)
{
	Chart_Buff_outMaxMin(buff,buffsize, max ,min, flag);
	if(*max-*min<20)
	{*max = *min+20;}
}
 /*******************************************************************************
* @FunctionName  : User_UI_Chart_Updata
* @Description    : �û���Ӹ������ߺ���
* @Input          : None
* @Output         : 
* @Return         : None
*******************************************************************************/
void User_UI_Chart_Updata(void)
{
	uint8_t MaxMinUpdataFlag=0;
		if(UI_Para.ChartUpdataFlag)//���߿ؼ��̶�120���㣬���ݿ���ʱ�����ж�
		{
			UI_Para.ChartUpdataFlag=0;
			if(UI_Para.Chart_Num<120)
			{
				UI_Para.Chart_T[UI_Para.Chart_Num]=UI_Para.Temperature;
				UI_Para.Chart_RH[UI_Para.Chart_Num]=UI_Para.RH;
				UI_Para.Chart_TVOC[UI_Para.Chart_Num]=UI_Para.TVocIndex;

				UI_Para.Chart_Num++;			

				lvgl_ChartRange_refresh(UI_Para.Chart_T,UI_Para.Chart_Num,&UI_Para.T_MaxRange,&UI_Para.T_MinRange,&MaxMinUpdataFlag);//���������Сֵˢ��
				lvgl_ChartRange_refresh(UI_Para.Chart_RH,UI_Para.Chart_Num,&UI_Para.RH_MaxRange,&UI_Para.RH_MinRange,&MaxMinUpdataFlag);
				lvgl_ChartRange_refresh(UI_Para.Chart_TVOC,UI_Para.Chart_Num,&UI_Para.TVOC_MaxRange,&UI_Para.TVOC_MinRange,&MaxMinUpdataFlag);

				lv_chart_set_next_value(ui_TChart, Tser, UI_Para.Temperature);	
				lv_chart_set_next_value(ui_RHChart, RHser, UI_Para.RH);
				lv_chart_set_next_value(ui_TVOCChart, TVOCser, UI_Para.TVocIndex);	
				if(UI_Para.Chart_Num==120)
				{
					lv_chart_set_ext_y_array(ui_TChart,Tser,UI_Para.Chart_T);	//Ϊ����Y����������
					lv_chart_set_ext_y_array(ui_RHChart,RHser,UI_Para.Chart_RH);
					lv_chart_set_ext_y_array(ui_TVOCChart,TVOCser,UI_Para.Chart_TVOC);		

					lv_chart_set_update_mode(ui_TChart,LV_CHART_UPDATE_MODE_SHIFT);//---���������Ҿ���������
					lv_chart_set_update_mode(ui_RHChart,LV_CHART_UPDATE_MODE_SHIFT);//---
					lv_chart_set_update_mode(ui_TVOCChart,LV_CHART_UPDATE_MODE_SHIFT);//---
				}
			}
			else
			{
				Chart_Buff_Add_NewData(UI_Para.Chart_T,120,UI_Para.Temperature);	//������ݵ����߻�����
				Chart_Buff_Add_NewData(UI_Para.Chart_RH,120,UI_Para.RH);
				Chart_Buff_Add_NewData(UI_Para.Chart_TVOC,120,UI_Para.TVocIndex);
				
				lvgl_ChartRange_refresh(UI_Para.Chart_T,UI_Para.Chart_Num,&UI_Para.T_MaxRange,&UI_Para.T_MinRange,&MaxMinUpdataFlag);//���������Сֵˢ��
				lvgl_ChartRange_refresh(UI_Para.Chart_RH,UI_Para.Chart_Num,&UI_Para.RH_MaxRange,&UI_Para.RH_MinRange,&MaxMinUpdataFlag);
				lvgl_ChartRange_refresh(UI_Para.Chart_TVOC,UI_Para.Chart_Num,&UI_Para.TVOC_MaxRange,&UI_Para.TVOC_MinRange,&MaxMinUpdataFlag);

				lv_chart_refresh(ui_TChart);			//��������
				lv_chart_refresh(ui_RHChart);
				lv_chart_refresh(ui_TVOCChart);							
			}
			if(MaxMinUpdataFlag==1)//����Y��������Сֵ��LVGL
			{
				lv_chart_set_range(ui_TChart, LV_CHART_AXIS_PRIMARY_Y, UI_Para.T_MinRange, UI_Para.T_MaxRange);//ȡ����ֵ���ֵ����Сֵ������5��Ϊ��Χ
				lv_chart_set_range(ui_RHChart, LV_CHART_AXIS_PRIMARY_Y, UI_Para.RH_MinRange, UI_Para.RH_MaxRange);	//ȡ����ֵ���ֵ����Сֵ������5%
				lv_chart_set_range(ui_TVOCChart, LV_CHART_AXIS_PRIMARY_Y, UI_Para.TVOC_MinRange, UI_Para.TVOC_MaxRange);//ȡ����ֵ���ֵ����Сֵ������50����
			}

		}	
}





u_Time UIUpdataCnt = 50;
	
void User_UI_Data_Updata(void)
{
	static uint16_t BatSoc_temp =0;
	float temp1,temp2;
	char text[50];
	char Onlinetxt[10] = "Online";
	char Offlinetxt[10] = "Offline";
	lv_color_t color_temp =lv_color_hex(0xFFFFFF);
	static lv_color_t color_temp2;
	static uint8_t usb_pwr_sta = 0;
	if (UIUpdataCnt<=0)
	{
		temp1 = bat.bat_v;
		temp2 = bat.BAT_MAX_VOL/1000.0;

		//----ADCͨ�������ĵ�ѹ
		sprintf(text,"%.2f V",temp1);
		lv_label_set_text(ui_BATvolN, (const char *)text);
		
		sprintf(text,"%.2f V",temp2);
		lv_label_set_text(ui_BATeleN, (const char *)text);

		//----���������Ĳ���
		temp1 = (float)SHT31.T;
		temp1 = (float)(temp1 /1000);
		temp2 = (float)SHT31.RH;
		temp2 = (float)(temp2/1000);
		sprintf(text,"%.1f ",temp1);
		lv_label_set_text(ui_TVal, (const char *)text);
		lv_label_set_text(ui_TValN, (const char *)text);
		lv_label_set_text(ui_TemperatureN, (const char *)text);
		
		sprintf(text,"%.1f ",temp2);
		lv_label_set_text(ui_RHVal, (const char *)text);
		lv_label_set_text(ui_RHValN, (const char *)text);
		lv_label_set_text(ui_RHnumN, (const char *)text);

		sprintf(text,"%d",SGP40.VOC_Index);
		lv_label_set_text(ui_TVOCVal, (const char *)text);		
		lv_label_set_text(ui_TVOCVal1, (const char *)text);
		lv_label_set_text(ui_VOCindexN, (const char *)text);

		//----VOCԭʼֵ��ʾ
		sprintf(text,"%d",SGP40.VOC_RAW);
		lv_label_set_text(ui_VOCrawN, (const char *)text);


		//----���Ͻǵ�ص�����ʾ
		if(BatSoc_temp!=bat.BAT_SOC)//��ص��������仯
		{
			BatSoc_temp = bat.BAT_SOC;
			
			sprintf(text,"%d",bat.BAT_SOC);	
			lv_label_set_text(ui_BATperN, (const char *)text);
			
			if(bat.BAT_SOC>90)
			{
				color_temp2 = lv_color_hex(0xFFFFFF);
				lv_obj_set_style_text_color(ui_BAT, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
				lv_label_set_text(ui_BAT,LV_SYMBOL_BATTERY_FULL );
			}
			else if (bat.BAT_SOC>75)
			{
				color_temp2 = lv_color_hex(0xFFFFFF);
				lv_obj_set_style_text_color(ui_BAT, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
				lv_label_set_text(ui_BAT,LV_SYMBOL_BATTERY_3 );
			
			}
			else if (bat.BAT_SOC>50)
			{
				color_temp2 = lv_color_hex(0xFFFFFF);
				lv_obj_set_style_text_color(ui_BAT, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
				lv_label_set_text(ui_BAT,LV_SYMBOL_BATTERY_2 );
			}
			else if (bat.BAT_SOC>25)
			{
				color_temp2 = lv_color_hex(0xFFD700);
				lv_obj_set_style_text_color(ui_BAT, lv_color_hex(0xFFD700), LV_PART_MAIN | LV_STATE_DEFAULT);//�������ڰٷ�֮25��ʾ��ɫ
				lv_label_set_text(ui_BAT,LV_SYMBOL_BATTERY_1 );
			}
			else if (bat.BAT_SOC>10)
			{
				color_temp2 = lv_color_hex(0xFF0000);
				lv_obj_set_style_text_color(ui_BAT, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);//��ʾ��ɫ
				lv_label_set_text(ui_BAT,LV_SYMBOL_BATTERY_EMPTY );
			}	
			usb_pwr_sta = 0xFF;//��ص��������仯USB��Դ����״̬����
		}
		//USB��Դ������ͼ�����
		if(usb_pwr_sta != bat.USB_PWR_Flag)
		{
			usb_pwr_sta = bat.USB_PWR_Flag;
			if(bat.USB_PWR_Flag)
			{
				color_temp = lv_color_hex(0x00FF00);
				lv_obj_set_style_text_color(ui_BAT, color_temp, LV_PART_MAIN | LV_STATE_DEFAULT);	
			}
			else
			{
				lv_obj_set_style_text_color(ui_BAT, color_temp2, LV_PART_MAIN | LV_STATE_DEFAULT);
			}			

		}		


		//----IIC״̬��ǩ
		if(UI_Para.IIC_State==1)
		{
			lv_label_set_text(ui_IICdevN, (const char *)Onlinetxt);
		}
		else
		{
			lv_label_set_text(ui_IICdevN, (const char *)Offlinetxt);
		}

		sprintf(text,"%02d:%02d",UI_Para.Hour,UI_Para.minute);
		lv_label_set_text(ui_StartTime, (const char *)text);

		//----X��������ʾ
		if(UI_Para.X_hour==0)
		{
			sprintf(text," %d M",0);
			lv_label_set_text(ui_Tshaft1, (const char *)text);
			lv_label_set_text(ui_RHshaft1, (const char *)text);
			lv_label_set_text(ui_TVshaft1, (const char *)text);
			sprintf(text," %d M",2);
			lv_label_set_text(ui_Tshaft2, (const char *)text);
			lv_label_set_text(ui_RHshaft2, (const char *)text);
			lv_label_set_text(ui_TVshaft2, (const char *)text);

			sprintf(text," %d M",4);
			lv_label_set_text(ui_Tshaft3, (const char *)text);
			lv_label_set_text(ui_RHshaft3, (const char *)text);
			lv_label_set_text(ui_TVshaft3, (const char *)text);			
		}
		else
		{
			sprintf(text," %d H",0);
			lv_label_set_text(ui_Tshaft1, (const char *)text);
			lv_label_set_text(ui_RHshaft1, (const char *)text);
			lv_label_set_text(ui_TVshaft1, (const char *)text);
			sprintf(text," %d H",UI_Para.X_hour/2);
			lv_label_set_text(ui_Tshaft2, (const char *)text);
			lv_label_set_text(ui_RHshaft2, (const char *)text);
			lv_label_set_text(ui_TVshaft2, (const char *)text);

			sprintf(text," %d H",UI_Para.X_hour);
			lv_label_set_text(ui_Tshaft3, (const char *)text);
			lv_label_set_text(ui_RHshaft3, (const char *)text);
			lv_label_set_text(ui_TVshaft3, (const char *)text);			
		}

		//----SD������
		sprintf(text,"%d MB",UI_Para.SD_size);
		lv_label_set_text(ui_SDsizeNum, (const char *)text);	
		
		//----���߸���
		User_UI_Chart_Updata();

		Set_Time(&UIUpdataCnt,199);	//��װ�� ��˸���ڼ�������
	}


}




