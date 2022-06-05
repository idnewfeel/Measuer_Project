#include "User_UI.h"




 /*******************************************************************************
* @FunctionName  : User_UI_Load
* @Description    : 用户UI载入动画
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
		
		lv_bar_set_value(ui_Loading, Bar_Num, LV_ANIM_ON);//进度条++
		Set_Time(&UILoadCnt,10);	//重装载 闪烁周期计数变量
		
		if(Bar_Num==100)
		{
			_ui_screen_change(ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0);
			Bar_Num++;
			Logout_Time_Tab(&Timer_OBJ,&UILoadCnt);//将变量从时间表注销
		}
	}

}

 /*******************************************************************************
* @FunctionName  : User_UI_Init
* @Description    : 用户添加UI
* @Input          : None
* @Output         : 
* @Return         : None
*******************************************************************************/


#define T_Defaul_Min 	10
#define	T_Defaul_Max	40
#define	RH_Defaul_Min	0
#define	RH_Defaul_Max	100
#define	VOC_Defaul_Min	0
#define	VOC_Defaul_Max	500
lv_chart_series_t * ser;

void User_UI_Init(void)
{
	uint8_t i = 0;
	//1.------------------电池图标设置-----------------
	/*设置电池电量图标*/
	lv_label_set_text(ui_BAT,LV_SYMBOL_BATTERY_FULL );


	//2.------------------曲线设置-----------------
	/*设置曲线没有栅格*/
	lv_chart_set_div_line_count(ui_TChart, 0, 0);
	lv_chart_set_div_line_count(ui_RHChart, 0, 0);
	lv_chart_set_div_line_count(ui_TVOCChart, 0, 0);

	/*设置曲线的点数*/
	lv_chart_set_point_count(ui_TChart, 144);
	lv_chart_set_point_count(ui_RHChart, 144);
	lv_chart_set_point_count(ui_TVOCChart, 144);

	/*设置曲线的点的大小*/
	lv_obj_set_style_size(ui_TChart, 0, LV_PART_INDICATOR);
	lv_obj_set_style_size(ui_RHChart, 0, LV_PART_INDICATOR);
	lv_obj_set_style_size(ui_TVOCChart, 0, LV_PART_INDICATOR);

	/*设置左轴垂直范围*/
	lv_chart_set_range(ui_TChart, LV_CHART_AXIS_PRIMARY_Y, T_Defaul_Min, T_Defaul_Max);//取采样值最大值和最小值的上下5℃为范围
	lv_chart_set_range(ui_RHChart, LV_CHART_AXIS_PRIMARY_Y, RH_Defaul_Min, RH_Defaul_Max);	//取采样值最大值和最小值的上下5%
	lv_chart_set_range(ui_TVOCChart, LV_CHART_AXIS_PRIMARY_Y, VOC_Defaul_Min, VOC_Defaul_Max);//取采样值最大值和最小值的上下50个点

	/*设置曲线的更新模式，*/
	lv_chart_set_update_mode(ui_TChart,LV_CHART_UPDATE_MODE_CIRCULAR);//---循环模式
	lv_chart_set_update_mode(ui_RHChart,LV_CHART_UPDATE_MODE_CIRCULAR);//---循环模式
	lv_chart_set_update_mode(ui_TVOCChart,LV_CHART_UPDATE_MODE_CIRCULAR);//---循环模式

	/*为图标添加曲线数组*/
	ser = lv_chart_add_series(ui_TChart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);

	/*设置刻度线*/
    lv_chart_set_axis_tick(ui_TChart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 5, true, 40);
    lv_chart_set_axis_tick(ui_TChart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 3, 7, false, 30);
    lv_chart_set_axis_tick(ui_RHChart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 5, true, 40);
    lv_chart_set_axis_tick(ui_RHChart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 3, 7, false, 30);
    lv_chart_set_axis_tick(ui_TVOCChart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 5, true, 40);
    lv_chart_set_axis_tick(ui_TVOCChart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 3, 7, false, 30);

	/**/
	for(i = 0; i < 50; i++) 
	{
        lv_chart_set_next_value(ui_TChart, ser, i);	
    }
	lv_chart_refresh(ui_TChart); 
	

}

