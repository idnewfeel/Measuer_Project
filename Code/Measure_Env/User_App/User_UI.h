#ifndef _User_UI_H
#define _User_UI_H

#include "main.h"
#include "TIM_Management.h"
#include "lvgl.h"
#include "ui.h"
#include "ui_helpers.h"
#include "system.h"
#include "stdio.h"
#include "lv_port_indev.h"

extern u_Time UILoadCnt;
extern u_Time UIUpdataCnt;

extern lv_chart_series_t * Tser;
extern lv_chart_series_t * RHser;
extern lv_chart_series_t * TVOCser;

void User_UI_Load(void);
void User_UI_Init(void);
void User_UI_Data_Updata(void);

#endif

