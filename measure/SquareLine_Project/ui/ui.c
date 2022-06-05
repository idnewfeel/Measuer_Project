// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_StartUp;
lv_obj_t * ui_Loading;
lv_obj_t * ui_Heath;
lv_obj_t * ui_Main;
lv_obj_t * ui_MidBtn;
lv_obj_t * ui_T;
lv_obj_t * ui_RH;
lv_obj_t * ui_TVOC;
lv_obj_t * ui_Panel1;
lv_obj_t * ui_StartTime;
lv_obj_t * ui_BAT;
lv_obj_t * ui_RightBtn;
lv_obj_t * ui_LeftBtn;
lv_obj_t * ui_TVal;
lv_obj_t * ui_degree;
lv_obj_t * ui_percent;
lv_obj_t * ui_RHVal;
lv_obj_t * ui_TVOCdd;
lv_obj_t * ui_TVOCVal;
lv_obj_t * ui_TDetail;
lv_obj_t * ui_TChart;
lv_obj_t * ui_degree1;
lv_obj_t * ui_TValN;
lv_obj_t * ui_T1;
lv_obj_t * ui_Tshaft1;
lv_obj_t * ui_Tshaft2;
lv_obj_t * ui_Tshaft3;
lv_obj_t * ui_RHDetail;
lv_obj_t * ui_RH1;
lv_obj_t * ui_RHValN;
lv_obj_t * ui_percent1;
lv_obj_t * ui_RHChart;
lv_obj_t * ui_RHshaft1;
lv_obj_t * ui_RHshaft2;
lv_obj_t * ui_RHshaft3;
lv_obj_t * ui_TVOCDetail;
lv_obj_t * ui_TVOCChart;
lv_obj_t * ui_TVOCN;
lv_obj_t * ui_TVOCVal1;
lv_obj_t * ui_TVOCdd1;
lv_obj_t * ui_TVshaft1;
lv_obj_t * ui_TVshaft2;
lv_obj_t * ui_TVshaft3;
lv_obj_t * ui_Debug;
lv_obj_t * ui_BATvol;
lv_obj_t * ui_Image1;
lv_obj_t * ui_BATele;
lv_obj_t * ui_RHnum;
lv_obj_t * ui_VOCraw;
lv_obj_t * ui_VOCindex;
lv_obj_t * ui_IICdevN;
lv_obj_t * ui_VOCindexN;
lv_obj_t * ui_VOCrawN;
lv_obj_t * ui_RHnumN;
lv_obj_t * ui_TemperatureN;
lv_obj_t * ui_BATperN;
lv_obj_t * ui_BATeleN;
lv_obj_t * ui_BATvolN;
lv_obj_t * ui_IICdev;
lv_obj_t * ui_Temperature;
lv_obj_t * ui_BATper;
lv_obj_t * ui_SDSize;
lv_obj_t * ui_SDsizeNum;
lv_obj_t * ui_SET;
lv_obj_t * ui_Image2;
lv_obj_t * ui_LeftBtn1;
lv_obj_t * ui_Roller2;
lv_obj_t * ui_UpTime;
lv_obj_t * ui_SdLabel;
lv_obj_t * ui_Switch1;
lv_obj_t * ui_SdLabel1;
lv_obj_t * ui_Power;
lv_obj_t * ui_SWPower;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "#error LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
static void ui_event_MidBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_TDetail, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);
    }
}
static void ui_event_RightBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_SET, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);
    }
}
static void ui_event_LeftBtn(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Debug, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);
    }
}
static void ui_event_LeftBtn1(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0);
    }
}

///////////////////// SCREENS ////////////////////
void ui_StartUp_screen_init(void)
{

    // ui_StartUp

    ui_StartUp = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_StartUp, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_StartUp, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StartUp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Loading

    ui_Loading = lv_bar_create(ui_StartUp);
    lv_bar_set_range(ui_Loading, 0, 100);

    lv_obj_set_width(ui_Loading, 150);
    lv_obj_set_height(ui_Loading, 10);

    lv_obj_set_x(ui_Loading, 0);
    lv_obj_set_y(ui_Loading, 55);

    lv_obj_set_align(ui_Loading, LV_ALIGN_CENTER);

    lv_obj_set_style_anim_time(ui_Loading, 500, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Heath

    ui_Heath = lv_img_create(ui_StartUp);
    lv_img_set_src(ui_Heath, &ui_img_max_heath_png);

    lv_obj_set_width(ui_Heath, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Heath, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Heath, 0);
    lv_obj_set_y(ui_Heath, -43);

    lv_obj_set_align(ui_Heath, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Heath, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Heath, LV_OBJ_FLAG_SCROLLABLE);

}
void ui_Main_screen_init(void)
{

    // ui_Main

    ui_Main = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Main, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);

    lv_obj_set_scrollbar_mode(ui_Main, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_bg_color(ui_Main, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Main, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_MidBtn

    ui_MidBtn = lv_btn_create(ui_Main);

    lv_obj_set_width(ui_MidBtn, 50);
    lv_obj_set_height(ui_MidBtn, 30);

    lv_obj_set_x(ui_MidBtn, 0);
    lv_obj_set_y(ui_MidBtn, 200);

    lv_obj_set_align(ui_MidBtn, LV_ALIGN_TOP_MID);

    lv_obj_add_flag(ui_MidBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_MidBtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_MidBtn, ui_event_MidBtn, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_MidBtn, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MidBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_MidBtn, &ui_img_menu_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MidBtn, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_MidBtn, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_MidBtn, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_MidBtn, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    // ui_T

    ui_T = lv_img_create(ui_Main);
    lv_img_set_src(ui_T, &ui_img_t4_png);

    lv_obj_set_width(ui_T, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_T, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_T, -75);
    lv_obj_set_y(ui_T, 30);

    lv_obj_set_align(ui_T, LV_ALIGN_TOP_MID);

    lv_obj_clear_flag(ui_T, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_T, LV_SCROLLBAR_MODE_OFF);

    // ui_RH

    ui_RH = lv_img_create(ui_Main);
    lv_img_set_src(ui_RH, &ui_img_rh1_png);

    lv_obj_set_width(ui_RH, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RH, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RH, -75);
    lv_obj_set_y(ui_RH, 82);

    lv_obj_set_align(ui_RH, LV_ALIGN_TOP_MID);

    lv_obj_clear_flag(ui_RH, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_RH, LV_SCROLLBAR_MODE_OFF);

    // ui_TVOC

    ui_TVOC = lv_img_create(ui_Main);
    lv_img_set_src(ui_TVOC, &ui_img_tvoc2_png);

    lv_obj_set_width(ui_TVOC, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TVOC, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TVOC, -75);
    lv_obj_set_y(ui_TVOC, 134);

    lv_obj_set_align(ui_TVOC, LV_ALIGN_TOP_MID);

    lv_obj_clear_flag(ui_TVOC, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_TVOC, LV_SCROLLBAR_MODE_OFF);

    // ui_Panel1

    ui_Panel1 = lv_obj_create(ui_Main);

    lv_obj_set_width(ui_Panel1, 240);
    lv_obj_set_height(ui_Panel1, 20);

    lv_obj_set_x(ui_Panel1, 0);
    lv_obj_set_y(ui_Panel1, 0);

    lv_obj_set_align(ui_Panel1, LV_ALIGN_TOP_MID);

    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_Panel1, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_radius(ui_Panel1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x1A2843), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel1, lv_color_hex(0x1A2843), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_Panel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_StartTime

    ui_StartTime = lv_label_create(ui_Panel1);

    lv_obj_set_width(ui_StartTime, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_StartTime, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_StartTime, 0);
    lv_obj_set_y(ui_StartTime, 0);

    lv_obj_set_align(ui_StartTime, LV_ALIGN_CENTER);

    lv_label_set_text(ui_StartTime, "OPEN:9:20");

    lv_obj_clear_flag(ui_StartTime, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_StartTime, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_text_color(ui_StartTime, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StartTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_StartTime, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BAT

    ui_BAT = lv_label_create(ui_Panel1);

    lv_obj_set_width(ui_BAT, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BAT, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BAT, 100);
    lv_obj_set_y(ui_BAT, 0);

    lv_obj_set_align(ui_BAT, LV_ALIGN_CENTER);

    lv_label_set_text(ui_BAT, "XX");

    lv_obj_clear_flag(ui_BAT, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_BAT, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_text_color(ui_BAT, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_BAT, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_BAT, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_RightBtn

    ui_RightBtn = lv_btn_create(ui_Main);

    lv_obj_set_width(ui_RightBtn, 50);
    lv_obj_set_height(ui_RightBtn, 30);

    lv_obj_set_x(ui_RightBtn, -10);
    lv_obj_set_y(ui_RightBtn, 200);

    lv_obj_set_align(ui_RightBtn, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_RightBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_RightBtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_RightBtn, ui_event_RightBtn, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_RightBtn, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RightBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_RightBtn, &ui_img_set_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RightBtn, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_RightBtn, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_RightBtn, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_RightBtn, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    // ui_LeftBtn

    ui_LeftBtn = lv_btn_create(ui_Main);

    lv_obj_set_width(ui_LeftBtn, 50);
    lv_obj_set_height(ui_LeftBtn, 30);

    lv_obj_set_x(ui_LeftBtn, 10);
    lv_obj_set_y(ui_LeftBtn, 200);

    lv_obj_add_flag(ui_LeftBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_LeftBtn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_LeftBtn, ui_event_LeftBtn, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_LeftBtn, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LeftBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_LeftBtn, &ui_img_detail_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_LeftBtn, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_LeftBtn, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_LeftBtn, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_LeftBtn, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    // ui_TVal

    ui_TVal = lv_label_create(ui_Main);

    lv_obj_set_width(ui_TVal, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TVal, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TVal, -8);
    lv_obj_set_y(ui_TVal, 30);

    lv_obj_set_align(ui_TVal, LV_ALIGN_TOP_MID);

    lv_label_set_text(ui_TVal, "25.5");

    lv_obj_clear_flag(ui_TVal, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_TVal, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_text_font(ui_TVal, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_degree

    ui_degree = lv_img_create(ui_Main);
    lv_img_set_src(ui_degree, &ui_img_ssd_png);

    lv_obj_set_width(ui_degree, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_degree, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_degree, -55);
    lv_obj_set_y(ui_degree, 30);

    lv_obj_set_align(ui_degree, LV_ALIGN_TOP_RIGHT);

    lv_obj_clear_flag(ui_degree, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_degree, LV_SCROLLBAR_MODE_OFF);

    // ui_percent

    ui_percent = lv_img_create(ui_Main);
    lv_img_set_src(ui_percent, &ui_img_1878437319);

    lv_obj_set_width(ui_percent, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_percent, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_percent, -55);
    lv_obj_set_y(ui_percent, 82);

    lv_obj_set_align(ui_percent, LV_ALIGN_TOP_RIGHT);

    lv_obj_clear_flag(ui_percent, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_percent, LV_SCROLLBAR_MODE_OFF);

    // ui_RHVal

    ui_RHVal = lv_label_create(ui_Main);

    lv_obj_set_width(ui_RHVal, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RHVal, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RHVal, -8);
    lv_obj_set_y(ui_RHVal, 82);

    lv_obj_set_align(ui_RHVal, LV_ALIGN_TOP_MID);

    lv_label_set_text(ui_RHVal, "60.6");

    lv_obj_clear_flag(ui_RHVal, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_RHVal, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_text_font(ui_RHVal, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_TVOCdd

    ui_TVOCdd = lv_img_create(ui_Main);
    lv_img_set_src(ui_TVOCdd, &ui_img_dw_png);

    lv_obj_set_width(ui_TVOCdd, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TVOCdd, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TVOCdd, -55);
    lv_obj_set_y(ui_TVOCdd, 134);

    lv_obj_set_align(ui_TVOCdd, LV_ALIGN_TOP_RIGHT);

    lv_obj_clear_flag(ui_TVOCdd, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_TVOCdd, LV_SCROLLBAR_MODE_OFF);

    // ui_TVOCVal

    ui_TVOCVal = lv_label_create(ui_Main);

    lv_obj_set_width(ui_TVOCVal, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TVOCVal, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TVOCVal, -8);
    lv_obj_set_y(ui_TVOCVal, 134);

    lv_obj_set_align(ui_TVOCVal, LV_ALIGN_TOP_MID);

    lv_label_set_text(ui_TVOCVal, "25");

    lv_obj_clear_flag(ui_TVOCVal, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_TVOCVal, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_text_font(ui_TVOCVal, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_TDetail_screen_init(void)
{

    // ui_TDetail

    ui_TDetail = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_TDetail, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);

    lv_obj_set_scrollbar_mode(ui_TDetail, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_radius(ui_TDetail, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TDetail, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TDetail, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_TChart

    ui_TChart = lv_chart_create(ui_TDetail);

    lv_obj_set_width(ui_TChart, 190);
    lv_obj_set_height(ui_TChart, 115);

    lv_obj_set_x(ui_TChart, 15);
    lv_obj_set_y(ui_TChart, 80);

    lv_obj_set_align(ui_TChart, LV_ALIGN_TOP_MID);

    lv_obj_set_style_bg_color(ui_TChart, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TChart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_TChart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_TChart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_TChart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_TChart, false, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_TChart, lv_color_hex(0xF4C8FC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_TChart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_TChart, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_TChart, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_left(ui_TChart, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TChart, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TChart, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TChart, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_line_color(ui_TChart, lv_color_hex(0x1296DB), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_TChart, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui_TChart, lv_color_hex(0x1296DB), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_TChart, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui_TChart, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui_TChart, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui_TChart, false, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui_TChart, false, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // ui_degree1

    ui_degree1 = lv_img_create(ui_TDetail);
    lv_img_set_src(ui_degree1, &ui_img_ssd_png);

    lv_obj_set_width(ui_degree1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_degree1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_degree1, -55);
    lv_obj_set_y(ui_degree1, 30);

    lv_obj_set_align(ui_degree1, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_degree1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_degree1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_TValN

    ui_TValN = lv_label_create(ui_TDetail);

    lv_obj_set_width(ui_TValN, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TValN, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TValN, -8);
    lv_obj_set_y(ui_TValN, 30);

    lv_obj_set_align(ui_TValN, LV_ALIGN_TOP_MID);

    lv_label_set_text(ui_TValN, "25.5");

    lv_obj_clear_flag(ui_TValN, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_TValN, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_text_font(ui_TValN, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_T1

    ui_T1 = lv_img_create(ui_TDetail);
    lv_img_set_src(ui_T1, &ui_img_t4_png);

    lv_obj_set_width(ui_T1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_T1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_T1, -75);
    lv_obj_set_y(ui_T1, 30);

    lv_obj_set_align(ui_T1, LV_ALIGN_TOP_MID);

    lv_obj_clear_flag(ui_T1, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_Tshaft1

    ui_Tshaft1 = lv_label_create(ui_TDetail);

    lv_obj_set_width(ui_Tshaft1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Tshaft1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Tshaft1, -80);
    lv_obj_set_y(ui_Tshaft1, 95);

    lv_obj_set_align(ui_Tshaft1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Tshaft1, "0_h");

    // ui_Tshaft2

    ui_Tshaft2 = lv_label_create(ui_TDetail);

    lv_obj_set_width(ui_Tshaft2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Tshaft2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Tshaft2, 15);
    lv_obj_set_y(ui_Tshaft2, 95);

    lv_obj_set_align(ui_Tshaft2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Tshaft2, "12_h");

    // ui_Tshaft3

    ui_Tshaft3 = lv_label_create(ui_TDetail);

    lv_obj_set_width(ui_Tshaft3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Tshaft3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Tshaft3, 100);
    lv_obj_set_y(ui_Tshaft3, 95);

    lv_obj_set_align(ui_Tshaft3, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Tshaft3, "24_h");

}
void ui_RHDetail_screen_init(void)
{

    // ui_RHDetail

    ui_RHDetail = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_RHDetail, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);

    lv_obj_set_style_radius(ui_RHDetail, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RHDetail, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RHDetail, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_RH1

    ui_RH1 = lv_img_create(ui_RHDetail);
    lv_img_set_src(ui_RH1, &ui_img_rh1_png);

    lv_obj_set_width(ui_RH1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RH1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RH1, -75);
    lv_obj_set_y(ui_RH1, 30);

    lv_obj_set_align(ui_RH1, LV_ALIGN_TOP_MID);

    lv_obj_add_flag(ui_RH1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_RH1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_RHValN

    ui_RHValN = lv_label_create(ui_RHDetail);

    lv_obj_set_width(ui_RHValN, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RHValN, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RHValN, -8);
    lv_obj_set_y(ui_RHValN, 30);

    lv_obj_set_align(ui_RHValN, LV_ALIGN_TOP_MID);

    lv_label_set_text(ui_RHValN, "60.6");

    lv_obj_set_style_text_font(ui_RHValN, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_percent1

    ui_percent1 = lv_img_create(ui_RHDetail);
    lv_img_set_src(ui_percent1, &ui_img_1878437319);

    lv_obj_set_width(ui_percent1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_percent1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_percent1, -55);
    lv_obj_set_y(ui_percent1, 30);

    lv_obj_set_align(ui_percent1, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_percent1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_percent1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_RHChart

    ui_RHChart = lv_chart_create(ui_RHDetail);

    lv_obj_set_width(ui_RHChart, 190);
    lv_obj_set_height(ui_RHChart, 115);

    lv_obj_set_x(ui_RHChart, 15);
    lv_obj_set_y(ui_RHChart, 80);

    lv_obj_set_align(ui_RHChart, LV_ALIGN_TOP_MID);

    lv_obj_set_style_bg_color(ui_RHChart, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RHChart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_RHChart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_RHChart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_RHChart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_RHChart, false, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_RHChart, lv_color_hex(0xF4C8FC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RHChart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_RHChart, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_RHChart, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_left(ui_RHChart, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_RHChart, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_RHChart, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_RHChart, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_line_color(ui_RHChart, lv_color_hex(0x1296DB), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_RHChart, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui_RHChart, lv_color_hex(0x1296DB), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_RHChart, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui_RHChart, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui_RHChart, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui_RHChart, false, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui_RHChart, false, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // ui_RHshaft1

    ui_RHshaft1 = lv_label_create(ui_RHDetail);

    lv_obj_set_width(ui_RHshaft1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RHshaft1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RHshaft1, -80);
    lv_obj_set_y(ui_RHshaft1, 95);

    lv_obj_set_align(ui_RHshaft1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_RHshaft1, "0_h");

    // ui_RHshaft2

    ui_RHshaft2 = lv_label_create(ui_RHDetail);

    lv_obj_set_width(ui_RHshaft2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RHshaft2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RHshaft2, 15);
    lv_obj_set_y(ui_RHshaft2, 95);

    lv_obj_set_align(ui_RHshaft2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_RHshaft2, "12_h");

    // ui_RHshaft3

    ui_RHshaft3 = lv_label_create(ui_RHDetail);

    lv_obj_set_width(ui_RHshaft3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RHshaft3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RHshaft3, 100);
    lv_obj_set_y(ui_RHshaft3, 95);

    lv_obj_set_align(ui_RHshaft3, LV_ALIGN_CENTER);

    lv_label_set_text(ui_RHshaft3, "24_h");

}
void ui_TVOCDetail_screen_init(void)
{

    // ui_TVOCDetail

    ui_TVOCDetail = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_TVOCDetail, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);

    lv_obj_set_style_bg_color(ui_TVOCDetail, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TVOCDetail, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_TVOCChart

    ui_TVOCChart = lv_chart_create(ui_TVOCDetail);

    lv_obj_set_width(ui_TVOCChart, 190);
    lv_obj_set_height(ui_TVOCChart, 115);

    lv_obj_set_x(ui_TVOCChart, 15);
    lv_obj_set_y(ui_TVOCChart, 80);

    lv_obj_set_align(ui_TVOCChart, LV_ALIGN_TOP_MID);

    lv_obj_set_style_bg_color(ui_TVOCChart, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TVOCChart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_TVOCChart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_TVOCChart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_TVOCChart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_TVOCChart, false, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_TVOCChart, lv_color_hex(0xF4C8FC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_TVOCChart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_TVOCChart, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_TVOCChart, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_left(ui_TVOCChart, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TVOCChart, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TVOCChart, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TVOCChart, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_line_color(ui_TVOCChart, lv_color_hex(0x1296DB), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_TVOCChart, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui_TVOCChart, lv_color_hex(0x1296DB), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_TVOCChart, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui_TVOCChart, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui_TVOCChart, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui_TVOCChart, false, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui_TVOCChart, false, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // ui_TVOCN

    ui_TVOCN = lv_img_create(ui_TVOCDetail);
    lv_img_set_src(ui_TVOCN, &ui_img_tvoc2_png);

    lv_obj_set_width(ui_TVOCN, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TVOCN, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TVOCN, -75);
    lv_obj_set_y(ui_TVOCN, 30);

    lv_obj_set_align(ui_TVOCN, LV_ALIGN_TOP_MID);

    lv_obj_add_flag(ui_TVOCN, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_TVOCN, LV_OBJ_FLAG_SCROLLABLE);

    // ui_TVOCVal1

    ui_TVOCVal1 = lv_label_create(ui_TVOCDetail);

    lv_obj_set_width(ui_TVOCVal1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TVOCVal1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TVOCVal1, -8);
    lv_obj_set_y(ui_TVOCVal1, 30);

    lv_obj_set_align(ui_TVOCVal1, LV_ALIGN_TOP_MID);

    lv_label_set_text(ui_TVOCVal1, "25");

    lv_obj_set_style_text_font(ui_TVOCVal1, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_TVOCdd1

    ui_TVOCdd1 = lv_img_create(ui_TVOCDetail);
    lv_img_set_src(ui_TVOCdd1, &ui_img_dw_png);

    lv_obj_set_width(ui_TVOCdd1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TVOCdd1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TVOCdd1, -55);
    lv_obj_set_y(ui_TVOCdd1, 30);

    lv_obj_set_align(ui_TVOCdd1, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_TVOCdd1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_TVOCdd1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_TVshaft1

    ui_TVshaft1 = lv_label_create(ui_TVOCDetail);

    lv_obj_set_width(ui_TVshaft1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TVshaft1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TVshaft1, -80);
    lv_obj_set_y(ui_TVshaft1, 95);

    lv_obj_set_align(ui_TVshaft1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TVshaft1, "0_h");

    // ui_TVshaft2

    ui_TVshaft2 = lv_label_create(ui_TVOCDetail);

    lv_obj_set_width(ui_TVshaft2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TVshaft2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TVshaft2, 15);
    lv_obj_set_y(ui_TVshaft2, 95);

    lv_obj_set_align(ui_TVshaft2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TVshaft2, "12_h");

    // ui_TVshaft3

    ui_TVshaft3 = lv_label_create(ui_TVOCDetail);

    lv_obj_set_width(ui_TVshaft3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TVshaft3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TVshaft3, 100);
    lv_obj_set_y(ui_TVshaft3, 95);

    lv_obj_set_align(ui_TVshaft3, LV_ALIGN_CENTER);

    lv_label_set_text(ui_TVshaft3, "24_h");

}
void ui_Debug_screen_init(void)
{

    // ui_Debug

    ui_Debug = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Debug, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_Debug, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Debug, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BATvol

    ui_BATvol = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_BATvol, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BATvol, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BATvol, 80);
    lv_obj_set_y(ui_BATvol, lv_pct(-28));

    lv_obj_set_align(ui_BATvol, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_BATvol, "BAT_V");

    lv_obj_clear_flag(ui_BATvol, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_align(ui_BATvol, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_BATvol, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Image1

    ui_Image1 = lv_img_create(ui_Debug);
    lv_img_set_src(ui_Image1, &ui_img_device_png);

    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image1, 24);
    lv_obj_set_y(ui_Image1, lv_pct(0));

    lv_obj_set_align(ui_Image1, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BATele

    ui_BATele = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_BATele, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BATele, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BATele, 80);
    lv_obj_set_y(ui_BATele, lv_pct(-20));

    lv_obj_set_align(ui_BATele, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_BATele, "BAT_ I");

    lv_obj_set_style_text_font(ui_BATele, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_RHnum

    ui_RHnum = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_RHnum, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RHnum, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RHnum, 80);
    lv_obj_set_y(ui_RHnum, lv_pct(4));

    lv_obj_set_align(ui_RHnum, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_RHnum, "RH");

    lv_obj_set_style_text_font(ui_RHnum, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_VOCraw

    ui_VOCraw = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_VOCraw, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_VOCraw, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_VOCraw, 80);
    lv_obj_set_y(ui_VOCraw, lv_pct(12));

    lv_obj_set_align(ui_VOCraw, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_VOCraw, "VOC_R");

    lv_obj_set_style_text_font(ui_VOCraw, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_VOCindex

    ui_VOCindex = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_VOCindex, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_VOCindex, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_VOCindex, 80);
    lv_obj_set_y(ui_VOCindex, lv_pct(20));

    lv_obj_set_align(ui_VOCindex, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_VOCindex, "VOC_I");

    lv_obj_set_style_text_font(ui_VOCindex, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_IICdevN

    ui_IICdevN = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_IICdevN, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_IICdevN, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_IICdevN, 160);
    lv_obj_set_y(ui_IICdevN, lv_pct(28));

    lv_obj_set_align(ui_IICdevN, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_IICdevN, "xxxx");

    lv_obj_set_style_text_font(ui_IICdevN, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_VOCindexN

    ui_VOCindexN = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_VOCindexN, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_VOCindexN, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_VOCindexN, 160);
    lv_obj_set_y(ui_VOCindexN, lv_pct(20));

    lv_obj_set_align(ui_VOCindexN, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_VOCindexN, "xxxx");

    lv_obj_set_style_text_font(ui_VOCindexN, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_VOCrawN

    ui_VOCrawN = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_VOCrawN, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_VOCrawN, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_VOCrawN, 160);
    lv_obj_set_y(ui_VOCrawN, lv_pct(12));

    lv_obj_set_align(ui_VOCrawN, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_VOCrawN, "xxxx");

    lv_obj_set_style_text_font(ui_VOCrawN, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_RHnumN

    ui_RHnumN = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_RHnumN, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RHnumN, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RHnumN, 160);
    lv_obj_set_y(ui_RHnumN, lv_pct(4));

    lv_obj_set_align(ui_RHnumN, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_RHnumN, "xxxx");

    lv_obj_set_style_text_font(ui_RHnumN, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_TemperatureN

    ui_TemperatureN = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_TemperatureN, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TemperatureN, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TemperatureN, 160);
    lv_obj_set_y(ui_TemperatureN, lv_pct(-4));

    lv_obj_set_align(ui_TemperatureN, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_TemperatureN, "xxxx");

    lv_obj_set_style_text_font(ui_TemperatureN, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BATperN

    ui_BATperN = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_BATperN, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BATperN, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BATperN, 160);
    lv_obj_set_y(ui_BATperN, lv_pct(-12));

    lv_obj_set_align(ui_BATperN, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_BATperN, "xxxx");

    lv_obj_set_style_text_font(ui_BATperN, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BATeleN

    ui_BATeleN = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_BATeleN, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BATeleN, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BATeleN, 160);
    lv_obj_set_y(ui_BATeleN, lv_pct(-20));

    lv_obj_set_align(ui_BATeleN, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_BATeleN, "xxxx");

    lv_obj_set_style_text_font(ui_BATeleN, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BATvolN

    ui_BATvolN = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_BATvolN, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BATvolN, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BATvolN, 160);
    lv_obj_set_y(ui_BATvolN, lv_pct(-28));

    lv_obj_set_align(ui_BATvolN, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_BATvolN, "xxxx");

    lv_obj_clear_flag(ui_BATvolN, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_align(ui_BATvolN, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_BATvolN, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_IICdev

    ui_IICdev = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_IICdev, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_IICdev, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_IICdev, 80);
    lv_obj_set_y(ui_IICdev, lv_pct(28));

    lv_obj_set_align(ui_IICdev, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_IICdev, "IIC");

    lv_obj_set_style_text_font(ui_IICdev, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Temperature

    ui_Temperature = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_Temperature, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Temperature, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Temperature, 80);
    lv_obj_set_y(ui_Temperature, lv_pct(-4));

    lv_obj_set_align(ui_Temperature, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_Temperature, "T");

    lv_obj_set_style_text_font(ui_Temperature, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BATper

    ui_BATper = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_BATper, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BATper, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BATper, 80);
    lv_obj_set_y(ui_BATper, lv_pct(-12));

    lv_obj_set_align(ui_BATper, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_BATper, "BAT");

    lv_obj_set_style_text_font(ui_BATper, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SDSize

    ui_SDSize = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_SDSize, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_SDSize, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_SDSize, 80);
    lv_obj_set_y(ui_SDSize, lv_pct(36));

    lv_obj_set_align(ui_SDSize, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_SDSize, "SD_size");

    lv_obj_set_style_text_font(ui_SDSize, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SDsizeNum

    ui_SDsizeNum = lv_label_create(ui_Debug);

    lv_obj_set_width(ui_SDsizeNum, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_SDsizeNum, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_SDsizeNum, 160);
    lv_obj_set_y(ui_SDsizeNum, lv_pct(36));

    lv_obj_set_align(ui_SDsizeNum, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_SDsizeNum, "xxxx");

    lv_obj_set_style_text_font(ui_SDsizeNum, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_SET_screen_init(void)
{

    // ui_SET

    ui_SET = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_SET, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);

    lv_obj_set_scrollbar_mode(ui_SET, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_bg_color(ui_SET, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SET, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Image2

    ui_Image2 = lv_img_create(ui_SET);
    lv_img_set_src(ui_Image2, &ui_img_set32_png);

    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image2, 24);
    lv_obj_set_y(ui_Image2, lv_pct(0));

    lv_obj_set_align(ui_Image2, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_SCROLLABLE);

    // ui_LeftBtn1

    ui_LeftBtn1 = lv_btn_create(ui_SET);

    lv_obj_set_width(ui_LeftBtn1, 50);
    lv_obj_set_height(ui_LeftBtn1, 30);

    lv_obj_set_x(ui_LeftBtn1, 160);
    lv_obj_set_y(ui_LeftBtn1, 75);

    lv_obj_set_align(ui_LeftBtn1, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_LeftBtn1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_LeftBtn1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_LeftBtn1, ui_event_LeftBtn1, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_LeftBtn1, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LeftBtn1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_LeftBtn1, &ui_img_return_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_LeftBtn1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_LeftBtn1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_LeftBtn1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_LeftBtn1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    // ui_Roller2

    ui_Roller2 = lv_roller_create(ui_SET);
    lv_roller_set_options(ui_Roller2, "4Minu\n2Hour\n4Hour\n6Hour\n8Hour\n10Hour\n12Hour\n24Hour", LV_ROLLER_MODE_INFINITE);

    lv_obj_set_height(ui_Roller2, 40);
    lv_obj_set_width(ui_Roller2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Roller2, 150);
    lv_obj_set_y(ui_Roller2, -75);

    lv_obj_set_align(ui_Roller2, LV_ALIGN_LEFT_MID);

    lv_obj_set_style_bg_color(ui_Roller2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Roller2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_UpTime

    ui_UpTime = lv_label_create(ui_SET);

    lv_obj_set_width(ui_UpTime, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_UpTime, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_UpTime, 80);
    lv_obj_set_y(ui_UpTime, -75);

    lv_obj_set_align(ui_UpTime, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_UpTime, "X_Time");

    lv_obj_clear_flag(ui_UpTime, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_align(ui_UpTime, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_UpTime, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_UpTime, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_UpTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_UpTime, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_UpTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_UpTime, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_UpTime, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_UpTime, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_UpTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_UpTime, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_UpTime, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SdLabel

    ui_SdLabel = lv_label_create(ui_SET);

    lv_obj_set_width(ui_SdLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_SdLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_SdLabel, 80);
    lv_obj_set_y(ui_SdLabel, -25);

    lv_obj_set_align(ui_SdLabel, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_SdLabel, "SDSave");

    lv_obj_clear_flag(ui_SdLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_align(ui_SdLabel, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SdLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SdLabel, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SdLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_SdLabel, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_SdLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_SdLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SdLabel, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_SdLabel, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_SdLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_SdLabel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_SdLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Switch1

    ui_Switch1 = lv_switch_create(ui_SET);

    lv_obj_set_width(ui_Switch1, 50);
    lv_obj_set_height(ui_Switch1, 25);

    lv_obj_set_x(ui_Switch1, 160);
    lv_obj_set_y(ui_Switch1, -25);

    lv_obj_set_align(ui_Switch1, LV_ALIGN_LEFT_MID);

    // ui_SdLabel1

    ui_SdLabel1 = lv_label_create(ui_SET);

    lv_obj_set_width(ui_SdLabel1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_SdLabel1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_SdLabel1, 80);
    lv_obj_set_y(ui_SdLabel1, 75);

    lv_obj_set_align(ui_SdLabel1, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_SdLabel1, "Return");

    lv_obj_clear_flag(ui_SdLabel1, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_align(ui_SdLabel1, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SdLabel1, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SdLabel1, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SdLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_SdLabel1, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_SdLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_SdLabel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_SdLabel1, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_SdLabel1, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_SdLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_SdLabel1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_SdLabel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Power

    ui_Power = lv_label_create(ui_SET);

    lv_obj_set_width(ui_Power, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Power, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Power, 80);
    lv_obj_set_y(ui_Power, 25);

    lv_obj_set_align(ui_Power, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_Power, "PowerS");

    lv_obj_clear_flag(ui_Power, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_align(ui_Power, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Power, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Power, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Power, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Power, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Power, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Power, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Power, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_Power, lv_color_hex(0x1296DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_Power, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_Power, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_Power, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SWPower

    ui_SWPower = lv_slider_create(ui_SET);
    lv_slider_set_range(ui_SWPower, 0, 100);

    lv_obj_set_width(ui_SWPower, 85);
    lv_obj_set_height(ui_SWPower, 4);

    lv_obj_set_x(ui_SWPower, 71);
    lv_obj_set_y(ui_SWPower, 27);

    lv_obj_set_align(ui_SWPower, LV_ALIGN_CENTER);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_StartUp_screen_init();
    ui_Main_screen_init();
    ui_TDetail_screen_init();
    ui_RHDetail_screen_init();
    ui_TVOCDetail_screen_init();
    ui_Debug_screen_init();
    ui_SET_screen_init();
    lv_disp_load_scr(ui_StartUp);
}

