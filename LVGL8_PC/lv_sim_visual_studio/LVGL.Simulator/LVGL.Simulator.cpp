/*
 * PROJECT:   LVGL PC Simulator using Visual Studio
 * FILE:      LVGL.Simulator.cpp
 * PURPOSE:   Implementation for LVGL ported to Windows Desktop
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Windows.h>

#include "resource.h"

#if _MSC_VER >= 1200
 // Disable compilation warnings.
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4244)
#endif

#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lv_demos/lv_demo.h"
#include "lv_drivers/win32drv/win32drv.h"
#include "lv_lib_freetype/lv_freetype.h"
#include "lv_demos/lv_demo_conf_template.h"


#if _MSC_VER >= 1200
// Restore compilation warnings.
#pragma warning(pop)
#endif

#include <stdio.h>

lv_fs_res_t lv_win32_filesystem_driver_error_from_win32(
    DWORD Error)
{
    lv_fs_res_t res;

    switch (Error)
    {
    case ERROR_SUCCESS:
        res = LV_FS_RES_OK;
        break;
    case ERROR_BAD_UNIT:
    case ERROR_NOT_READY:
    case ERROR_CRC:
    case ERROR_SEEK:
    case ERROR_NOT_DOS_DISK:
    case ERROR_WRITE_FAULT:
    case ERROR_READ_FAULT:
    case ERROR_GEN_FAILURE:
    case ERROR_WRONG_DISK:
        res = LV_FS_RES_HW_ERR;
        break;
    case ERROR_INVALID_HANDLE:
    case ERROR_INVALID_TARGET_HANDLE:
        res = LV_FS_RES_FS_ERR;
        break;
    case ERROR_FILE_NOT_FOUND:
    case ERROR_PATH_NOT_FOUND:
    case ERROR_INVALID_DRIVE:
    case ERROR_NO_MORE_FILES:
    case ERROR_SECTOR_NOT_FOUND:
    case ERROR_BAD_NETPATH:
    case ERROR_BAD_NET_NAME:
    case ERROR_BAD_PATHNAME:
    case ERROR_FILENAME_EXCED_RANGE:
        res = LV_FS_RES_NOT_EX;
        break;
    case ERROR_DISK_FULL:
        res = LV_FS_RES_FULL;
        break;
    case ERROR_SHARING_VIOLATION:
    case ERROR_LOCK_VIOLATION:
    case ERROR_DRIVE_LOCKED:
        res = LV_FS_RES_LOCKED;
        break;
    case ERROR_ACCESS_DENIED:
    case ERROR_CURRENT_DIRECTORY:
    case ERROR_WRITE_PROTECT:
    case ERROR_NETWORK_ACCESS_DENIED:
    case ERROR_CANNOT_MAKE:
    case ERROR_FAIL_I24:
    case ERROR_SEEK_ON_DEVICE:
    case ERROR_NOT_LOCKED:
    case ERROR_LOCK_FAILED:
        res = LV_FS_RES_DENIED;
        break;
    case ERROR_BUSY:
        res = LV_FS_RES_BUSY;
        break;
    case ERROR_TIMEOUT:
        res = LV_FS_RES_TOUT;
        break;
    case ERROR_NOT_SAME_DEVICE:
    case ERROR_DIRECT_ACCESS_HANDLE:
        res = LV_FS_RES_NOT_IMP;
        break;
    case ERROR_TOO_MANY_OPEN_FILES:
    case ERROR_ARENA_TRASHED:
    case ERROR_NOT_ENOUGH_MEMORY:
    case ERROR_INVALID_BLOCK:
    case ERROR_OUT_OF_PAPER:
    case ERROR_SHARING_BUFFER_EXCEEDED:
    case ERROR_NOT_ENOUGH_QUOTA:
        res = LV_FS_RES_OUT_OF_MEM;
        break;
    case ERROR_INVALID_FUNCTION:
    case ERROR_INVALID_ACCESS:
    case ERROR_INVALID_DATA:
    case ERROR_BAD_COMMAND:
    case ERROR_BAD_LENGTH:
    case ERROR_INVALID_PARAMETER:
    case ERROR_NEGATIVE_SEEK:
        res = LV_FS_RES_INV_PARAM;
        break;
    default:
        res = LV_FS_RES_UNKNOWN;
        break;
    }

    return res;
}

static void* lv_win32_filesystem_driver_open_callback(
    lv_fs_drv_t* drv,
    const char* path,
    lv_fs_mode_t mode)
{
    UNREFERENCED_PARAMETER(drv);

    DWORD DesiredAccess = 0;

    if (mode & LV_FS_MODE_RD)
    {
        DesiredAccess |= GENERIC_READ;
    }

    if (mode & LV_FS_MODE_WR)
    {
        DesiredAccess |= GENERIC_WRITE;
    }

    char Buffer[MAX_PATH];
    sprintf(Buffer, ".\\%s", path);

    return (void*)CreateFileA(
        Buffer,
        DesiredAccess,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
}

static lv_fs_res_t lv_win32_filesystem_driver_close_callback(
    lv_fs_drv_t* drv,
    void* file_p)
{
    UNREFERENCED_PARAMETER(drv);

    return CloseHandle((HANDLE)file_p)
        ? LV_FS_RES_OK
        : lv_win32_filesystem_driver_error_from_win32(GetLastError());
}

static lv_fs_res_t lv_win32_filesystem_driver_read_callback(
    lv_fs_drv_t* drv,
    void* file_p,
    void* buf,
    uint32_t btr,
    uint32_t* br)
{
    UNREFERENCED_PARAMETER(drv);

    return ReadFile((HANDLE)file_p, buf, btr, (LPDWORD)br, NULL)
        ? LV_FS_RES_OK
        : lv_win32_filesystem_driver_error_from_win32(GetLastError());
}

static lv_fs_res_t lv_win32_filesystem_driver_write_callback(
    lv_fs_drv_t* drv,
    void* file_p,
    const void* buf,
    uint32_t btw,
    uint32_t* bw)
{
    UNREFERENCED_PARAMETER(drv);

    return WriteFile((HANDLE)file_p, buf, btw, (LPDWORD)bw, NULL)
        ? LV_FS_RES_OK
        : lv_win32_filesystem_driver_error_from_win32(GetLastError()); 
}

static lv_fs_res_t lv_win32_filesystem_driver_seek_callback(
    lv_fs_drv_t* drv,
    void* file_p,
    uint32_t pos,
    lv_fs_whence_t whence)
{
    UNREFERENCED_PARAMETER(drv);

    DWORD MoveMethod = (DWORD)-1;
    if (whence == LV_FS_SEEK_SET)
    {
        MoveMethod = FILE_BEGIN;
    }
    else if(whence == LV_FS_SEEK_CUR)
    {
        MoveMethod = FILE_CURRENT;
    }
    else if(whence == LV_FS_SEEK_END)
    {
        MoveMethod = FILE_END;
    }

    LARGE_INTEGER DistanceToMove;
    DistanceToMove.QuadPart = pos;
    return SetFilePointerEx((HANDLE)file_p, DistanceToMove, NULL, MoveMethod)
        ? LV_FS_RES_OK
        : lv_win32_filesystem_driver_error_from_win32(GetLastError());
}

static lv_fs_res_t lv_win32_filesystem_driver_tell_callback(
    lv_fs_drv_t* drv,
    void* file_p,
    uint32_t* pos_p)
{
    UNREFERENCED_PARAMETER(drv);

    if (!pos_p)
    {
        return LV_FS_RES_INV_PARAM;
    }
    *pos_p = (uint32_t)-1;

    LARGE_INTEGER FilePointer;
    FilePointer.QuadPart = 0;

    LARGE_INTEGER DistanceToMove;
    DistanceToMove.QuadPart = 0;
    if (SetFilePointerEx(
        (HANDLE)file_p,
        DistanceToMove,
        &FilePointer,
        FILE_CURRENT))
    {
        if (FilePointer.QuadPart > LONG_MAX)
        {
            return LV_FS_RES_INV_PARAM;
        }
        else
        {
            *pos_p = FilePointer.LowPart;
            return LV_FS_RES_OK;
        }
    }
    else
    {
        return lv_win32_filesystem_driver_error_from_win32(GetLastError());
    }
}

static char next_filename_buffer[MAX_PATH];
static lv_fs_res_t next_filename_error = LV_FS_RES_OK;

static bool is_dots_name(
    _In_ LPCSTR Name)
{
    return Name[0] == L'.' && (!Name[1] || (Name[1] == L'.' && !Name[2]));
}

static void* lv_win32_filesystem_driver_dir_open_callback(
    lv_fs_drv_t* drv,
    const char* path)
{
    UNREFERENCED_PARAMETER(drv);

    HANDLE FindHandle = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATAA FindData;

    char Buffer[256];
    sprintf(Buffer, ".\\%s\\*", path);

    strcpy(next_filename_buffer, "");

    FindHandle = FindFirstFileA(Buffer, &FindData);
    do
    {
        if (is_dots_name(FindData.cFileName))
        {
            continue;
        }
        else
        {
            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                sprintf(next_filename_buffer, "/%s", FindData.cFileName);
            }
            else
            {
                sprintf(next_filename_buffer, "%s", FindData.cFileName);
            }

            break;
        }

    } while (FindNextFileA(FindHandle, &FindData));

    next_filename_error =
        lv_win32_filesystem_driver_error_from_win32(GetLastError());

    return (void*)FindHandle;
}

static lv_fs_res_t lv_win32_filesystem_driver_dir_read_callback(
    lv_fs_drv_t* drv,
    void* rddir_p,
    char* fn)
{
    UNREFERENCED_PARAMETER(drv);

    strcpy(fn, next_filename_buffer);
    lv_fs_res_t current_filename_error = next_filename_error;
    next_filename_error = LV_FS_RES_OK;

    strcpy(next_filename_buffer, "");
    WIN32_FIND_DATAA FindData;

    while (FindNextFileA((HANDLE)rddir_p, &FindData))
    {
        if (is_dots_name(FindData.cFileName))
        {
            continue;
        }
        else
        {
            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                sprintf(next_filename_buffer, "/%s", FindData.cFileName);
            }
            else
            {
                sprintf(next_filename_buffer, "%s", FindData.cFileName);
            }

            break;
        }
    }

    if (next_filename_buffer[0] == '\0')
    {
        next_filename_error =
            lv_win32_filesystem_driver_error_from_win32(GetLastError());
    }

    return current_filename_error;
}

static lv_fs_res_t lv_win32_filesystem_driver_dir_close_callback(
    lv_fs_drv_t* drv,
    void* rddir_p)
{
    UNREFERENCED_PARAMETER(drv);

    return FindClose((HANDLE)rddir_p)
        ? LV_FS_RES_OK
        : lv_win32_filesystem_driver_error_from_win32(GetLastError());
}

void lv_win32_filesystem_driver_initialize()
{
    static lv_fs_drv_t filesystem_driver;
    lv_fs_drv_init(&filesystem_driver);

    filesystem_driver.letter = '/';

    filesystem_driver.open_cb = lv_win32_filesystem_driver_open_callback;
    filesystem_driver.close_cb = lv_win32_filesystem_driver_close_callback;
    filesystem_driver.read_cb = lv_win32_filesystem_driver_read_callback;
    filesystem_driver.write_cb = lv_win32_filesystem_driver_write_callback;
    filesystem_driver.seek_cb = lv_win32_filesystem_driver_seek_callback;
    filesystem_driver.tell_cb = lv_win32_filesystem_driver_tell_callback;

    filesystem_driver.dir_open_cb = lv_win32_filesystem_driver_dir_open_callback;
    filesystem_driver.dir_read_cb = lv_win32_filesystem_driver_dir_read_callback;
    filesystem_driver.dir_close_cb = lv_win32_filesystem_driver_dir_close_callback;

    lv_fs_drv_register(&filesystem_driver);
}













// 定义三个style变量
static lv_style_t style_btn;
static lv_style_t style_btn_pressed;
static lv_style_t style_pr;
static lv_style_t style_scr;

lv_obj_t* scr;
lv_obj_t* Set_btn;//设置按钮
lv_obj_t* DBC_btn;//DBC按钮
lv_obj_t* Fan_btn;//反射百分比按钮
lv_obj_t* Cool_btn;//制冷按钮
lv_obj_t* DEW;      //露点文本标签
lv_obj_t* RH;       //相对湿度文本标签
lv_obj_t* TMP;      //温度标签
lv_obj_t* Bright_slider;

lv_obj_t* Set_scr;//设置页面屏幕
static lv_style_t style_set_scr;
lv_style_t style_Set_label;//添加设置页面文字标签样式
//extern const lv_font_t my_font_image;
#define MY_FANSHE           "\xEE\x98\xBA"
#define MY_man_fanshe       "\xEE\x98\x82"
#define MY_suoding          "\xEE\x98\x80"
#define MY_jiesuo           "\xEE\x98\x81"
#define MY_UPjiantou        "\xEE\x98\xAF"
#define MY_Down_jiantou     "\xEE\x98\xB0"
#define MY_jingmian         "\xEE\x98\xB7"
#define MY_HOME             "\xEE\xA3\xBF"
#define MY_ZHILENG          "\xEE\x9A\x84"
#define MY_JIARE            "\xEE\x9F\xAD"


/**
 * @brief 设置页面HOME按钮回调函数
 * @param e
*/
static void Home_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
        /*创建设置页面*/
        lv_scr_load_anim(scr, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, false);
        //lv_disp_load_scr(scr);
    }
}

/**
 * @brief 主页设置按钮回调函数
 * @param e 
*/
static void event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
        /*创建设置页面*/
        //Set_scr_Create();
        //       lv_disp_load_scr(Set_scr);
        lv_scr_load_anim(Set_scr, LV_SCR_LOAD_ANIM_OVER_LEFT, 300, 0, false);
        //lv_obj_clear_flag(Set_scr, LV_OBJ_FLAG_HIDDEN);
        //lv_obj_add_flag(scr, LV_OBJ_FLAG_HIDDEN);

    }
}



static void slider_event_cb(lv_event_t* e);
static lv_obj_t* slider_label;
/**
 * 背光亮度设置控件
 */
void Brightness_slider(void)
{
    static lv_style_t style_main;
    static lv_style_t style_indicator;
    static lv_style_t style_knob;
    static lv_style_t style_SliderLabel_color;

    //设置滑块主样式
    lv_style_init(&style_main);
    lv_style_set_bg_opa(&style_main, LV_OPA_COVER);//设为不透明
    lv_style_set_bg_color(&style_main, lv_color_make(0xDC, 0xDC, 0xDC));//滑块背景颜色
    lv_style_set_radius(&style_main, LV_RADIUS_CIRCLE);//设置圆角为半圆弧
    lv_style_set_pad_ver(&style_main, 0); /*Makes the indicator larger指示器放大*/

    //设置指示器样式
    lv_style_init(&style_indicator);
    lv_style_set_bg_opa(&style_indicator, LV_OPA_COVER);//设背景为不透明
    lv_style_set_bg_color(&style_indicator, lv_color_white());//设置背景颜色
    lv_style_set_radius(&style_indicator, LV_RADIUS_CIRCLE);

    //设置滑块样式
    lv_style_init(&style_knob);
    lv_style_set_bg_opa(&style_knob, LV_OPA_COVER);
    lv_style_set_bg_color(&style_knob, lv_palette_main(LV_PALETTE_CYAN));//设置背景颜色
    lv_style_set_border_color(&style_knob, lv_palette_darken(LV_PALETTE_CYAN, 3));
    lv_style_set_border_width(&style_knob, 2);//
    lv_style_set_radius(&style_knob, LV_RADIUS_CIRCLE);//设置圆角为半圆
    lv_style_set_pad_all(&style_knob, 6); /*Makes the knob larger把旋钮变大*/
 //   lv_style_set_transition(&style_knob, &transition_dsc);
    //字符的样式
    lv_style_init(&style_SliderLabel_color);
    lv_style_set_bg_color(&style_SliderLabel_color, lv_color_white());
    lv_style_set_text_font(&style_SliderLabel_color, &lv_font_montserrat_14);
    lv_style_set_text_color(&style_SliderLabel_color, lv_color_white());


    /*Create a slider in the center of the display*/
    Bright_slider = lv_slider_create(Set_scr);
    lv_obj_remove_style_all(Bright_slider);        /*清除默认样式*/
    lv_obj_add_event_cb(Bright_slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);//添加回调事件
    lv_obj_add_style(Bright_slider, &style_main, LV_PART_MAIN);//添加主背景样式
    lv_obj_add_style(Bright_slider, &style_indicator, LV_PART_INDICATOR);//添加指示样式
    lv_obj_add_style(Bright_slider, &style_knob, LV_PART_KNOB);//添加抓取的样式
    lv_slider_set_value(Bright_slider, 50, LV_ANIM_OFF);
    lv_obj_set_pos(Bright_slider, 185, 398);
    lv_obj_set_size(Bright_slider, 150, 10);
    /*Create a label below the slider*/
    slider_label = lv_label_create(Set_scr);//lv_scr_act()
    lv_obj_add_style(slider_label, &style_SliderLabel_color, LV_STATE_DEFAULT); // 给对象添加默认样式
    lv_label_set_text(slider_label, "50%");
    lv_obj_align_to(slider_label, Bright_slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}
/**
 * @brief *背光亮度滑块条的回调函数
*/
static void slider_event_cb(lv_event_t* e)
{
    lv_obj_t* slider = lv_event_get_target(e);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", lv_slider_get_value(slider));
    lv_label_set_text(slider_label, buf);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}
/**
 * @brief *创建强制结霜开关按钮回调函数
*/
static void eFrost_SW_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("State: %s\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
    }
}


/**
 * @brief *创建强制结霜开关按钮
*/
lv_obj_t* sw;
void eFrost_switch(void)
{
    static lv_style_t style_eFrost_main;
    static lv_style_t style_eFrost_indicator;
    static lv_style_t style_eFrost_knob;
    lv_style_init(&style_eFrost_main);
    lv_style_set_bg_opa(&style_eFrost_main, LV_OPA_COVER);//设为不透明
    lv_style_set_bg_color(&style_eFrost_main, lv_palette_main(LV_PALETTE_RED));//滑块背景颜色
    lv_style_set_radius(&style_eFrost_main, LV_RADIUS_CIRCLE);//设置圆角为半圆弧
    lv_style_set_pad_ver(&style_eFrost_main, 0); /*Makes the indicator larger指示器放大*/

    //设置指示器样式
    lv_style_init(&style_eFrost_indicator);
    lv_style_set_bg_opa(&style_eFrost_indicator, LV_OPA_COVER);//设背景为不透明
    lv_style_set_bg_color(&style_eFrost_indicator, lv_color_make(0,0xFF,0));//设置背景颜色 绿色
    lv_style_set_shadow_color(&style_eFrost_indicator, lv_color_make(240, 0xFF, 255));//设置背景颜色 绿色
    lv_style_set_radius(&style_eFrost_indicator, LV_RADIUS_CIRCLE);

    //设置滑块样式
    lv_style_init(&style_eFrost_knob);
    lv_style_set_bg_opa(&style_eFrost_knob, LV_OPA_COVER);
    lv_style_set_bg_color(&style_eFrost_knob, lv_color_make(100, 149, 237));//设置背景颜色
    lv_style_set_radius(&style_eFrost_knob, LV_RADIUS_CIRCLE);//设置圆角为半圆

    
    sw = lv_switch_create(Set_scr);
    //lv_obj_remove_style_all(sw);
    //lv_obj_add_style(sw, &style_eFrost_main, LV_PART_MAIN);//添加主背景样式
    //lv_obj_add_style(sw, &style_eFrost_indicator, LV_PART_INDICATOR);//添加指示样式
    //lv_obj_add_style(sw, &style_eFrost_knob, LV_PART_KNOB);//添加抓取的样式
    lv_obj_set_size(sw, 50, 25);
    lv_obj_set_pos(sw, 600, 390);
    lv_obj_add_state(sw, LV_STATE_DEFAULT);//| LV_STATE_DISABLED
    lv_obj_add_event_cb(sw, eFrost_SW_handler, LV_EVENT_ALL, NULL);
}

//创建设置页面的标签
static void Set_page_label_create(const char* s,uint8_t line,uint8_t num)
{
    uint16_t x = 0, y = 0;


    lv_obj_t* Set_label_s = lv_label_create(Set_scr);
    lv_obj_add_style(Set_label_s, &style_Set_label, LV_STATE_DEFAULT); // 给对象添加默认样式
    lv_label_set_text(Set_label_s, s); // 设置标签文本
    if (line == 1)
    {
        x = 50;
        y = 90 + (num-1)*60;
    }
    else if (line == 2)
    {
        x = 450;
        y = 90 + (num - 1) * 60;
    }
    lv_obj_set_pos(Set_label_s, x, y);

}

/*创建文本输入框*/
static lv_obj_t* kb;
lv_obj_t* Tempta;
static void ta_event_cb(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = lv_event_get_target(e);
    if (code == LV_EVENT_FOCUSED) {
//        if (lv_indev_get_type(lv_indev_get_act()) != LV_INDEV_TYPE_KEYPAD) {
            lv_keyboard_set_textarea(kb, ta);
            lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);

//        }
    }
    else if (code == LV_EVENT_LEAVE) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
    }
    else if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
        lv_indev_reset(NULL, ta);   /*To forget the last clicked object to make it focusable again*/
    }

    //lv_event_code_t code = lv_event_get_code(e);
    //ta = lv_event_get_target(e);
    //const char* txt = lv_textarea_get_text(ta);

    //if (code == LV_EVENT_FOCUSED)//点击文本框选中
    //{
    //    lv_keyboard_set_textarea(kb, ta);
    //    lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    //}
    //else if (code == LV_EVENT_LEAVE)//点到其他控件上
    //{
    //    lv_keyboard_set_textarea(kb, NULL);
    //    printf("111\r\n");
    //    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    //    lv_obj_clear_state(ta, LV_STATE_FOCUSED);
    //}
    //else if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL)//点击勾按钮
    //{
    //    lv_keyboard_set_textarea(kb, NULL);
    //    lv_obj_clear_state(ta, LV_STATE_FOCUSED);
    //    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    //    lv_indev_reset(NULL, ta);
    //    printf("222\r\n");
 
    //}
}




lv_style_t Set_Text;
void TempCail_Text()
{

    lv_style_init(&Set_Text);
    lv_style_set_bg_color(&Set_Text, lv_color_make(0, 191, 255));
    lv_style_set_border_color(&Set_Text, lv_color_white()); // 设置边框颜色为白色
    lv_style_set_border_opa(&Set_Text, LV_OPA_100); // 设置边框透明度为100%
    lv_style_set_border_width(&Set_Text, 2); // 设置边框宽度为2
    lv_style_set_radius(&Set_Text, 0); // 设置按钮样式圆角弧度
    lv_style_set_text_font(&Set_Text, &lv_font_montserrat_18);
    lv_style_set_text_color(&Set_Text, lv_color_white());
    lv_style_set_text_align(&Set_Text, LV_ALIGN_CENTER);


    /*Create the text area*/
    Tempta = lv_textarea_create(Set_scr);//创建文本输入框
    lv_obj_remove_style_all(Tempta);
    lv_obj_add_style(Tempta,&Set_Text, LV_PART_MAIN);//添加文本框样式
    lv_obj_set_size(Tempta,125,50);//设置控件尺寸
    lv_obj_set_pos(Tempta,185,90);//设置坐标
 //   lv_textarea_set_placeholder_text(ta, "0.00");//设置占位字符
    lv_obj_add_event_cb(Tempta, ta_event_cb, LV_EVENT_ALL, kb);//设置回调函数
    lv_textarea_set_accepted_chars(Tempta, "-+0123456789.");//设置输入接受的范围
    lv_textarea_set_max_length(Tempta, 5);//设置文本框最大长度
    lv_textarea_set_one_line(Tempta, true);//设置一行
    lv_textarea_set_text(Tempta, "0.00");

    lv_obj_t* tal = lv_textarea_create(Set_scr);//创建文本输入框
    lv_obj_remove_style_all(tal);
    lv_obj_add_style(tal, &Set_Text, LV_PART_MAIN);//添加文本框样式
    lv_obj_set_size(tal, 125, 50);//设置控件尺寸
    lv_obj_set_pos(tal, 185, 150);//设置坐标
 //   lv_textarea_set_placeholder_text(ta, "0.00");//设置占位字符
    lv_obj_add_event_cb(tal, ta_event_cb, LV_EVENT_ALL, kb);//设置回调函数
    lv_textarea_set_accepted_chars(tal, "-+0123456789.");//设置输入接受的范围
    lv_textarea_set_max_length(tal, 5);//设置文本框最大长度
    lv_textarea_set_one_line(tal, true);//设置一行
    lv_textarea_set_text(tal, "0.00");

    tal = lv_textarea_create(Set_scr);//创建文本输入框
    lv_obj_remove_style_all(tal);
    lv_obj_add_style(tal, &Set_Text, LV_PART_MAIN);//添加文本框样式
    lv_obj_set_size(tal, 125, 50);//设置控件尺寸
    lv_obj_set_pos(tal, 185, 210);//设置坐标
 //   lv_textarea_set_placeholder_text(ta, "0.00");//设置占位字符
    lv_obj_add_event_cb(tal, ta_event_cb, LV_EVENT_ALL, kb);//设置回调函数
    lv_textarea_set_accepted_chars(tal, "0123456789");//设置输入接受的范围
    lv_textarea_set_max_length(tal, 4);//设置文本框最大长度
    lv_textarea_set_one_line(tal, true);//设置一行
    lv_textarea_set_text(tal, "999");

    tal = lv_textarea_create(Set_scr);//创建文本输入框
    lv_obj_remove_style_all(tal);
    lv_obj_add_style(tal, &Set_Text, LV_PART_MAIN);//添加文本框样式
    lv_obj_set_size(tal, 125, 50);//设置控件尺寸
    lv_obj_set_pos(tal, 185, 270);//设置坐标
 //   lv_textarea_set_placeholder_text(ta, "0.00");//设置占位字符
    lv_obj_add_event_cb(tal, ta_event_cb, LV_EVENT_ALL, kb);//设置回调函数
    lv_textarea_set_accepted_chars(tal, "0123456789");//设置输入接受的范围
    lv_textarea_set_max_length(tal, 3);//设置文本框最大长度
    lv_textarea_set_one_line(tal, true);//设置一行
    lv_textarea_set_text(tal, "001");





    tal = lv_textarea_create(Set_scr);//创建文本输入框
    lv_obj_remove_style_all(tal);
    lv_obj_add_style(tal, &Set_Text, LV_PART_MAIN);//添加文本框样式
    lv_obj_set_size(tal, 125, 50);//设置控件尺寸
    lv_obj_set_pos(tal, 600, 210);//设置坐标
 //   lv_textarea_set_placeholder_text(ta, "0.00");//设置占位字符
    lv_obj_add_event_cb(tal, ta_event_cb, LV_EVENT_ALL, kb);//设置回调函数
    lv_textarea_set_accepted_chars(tal, "0123456789");//设置输入接受的范围
    lv_textarea_set_max_length(tal, 3);//设置文本框最大长度
    lv_textarea_set_one_line(tal, true);//设置一行
    lv_textarea_set_text(tal, "9");

    tal = lv_textarea_create(Set_scr);//创建文本输入框
    lv_obj_remove_style_all(tal);
    lv_obj_add_style(tal, &Set_Text, LV_PART_MAIN);//添加文本框样式
    lv_obj_set_size(tal, 125, 50);//设置控件尺寸
    lv_obj_set_pos(tal, 600, 270);//设置坐标
 //   lv_textarea_set_placeholder_text(ta, "0.00");//设置占位字符
    lv_obj_add_event_cb(tal, ta_event_cb, LV_EVENT_ALL, kb);//设置回调函数
    lv_textarea_set_accepted_chars(tal, "0123456789");//设置输入接受的范围
    lv_textarea_set_max_length(tal, 3);//设置文本框最大长度
    lv_textarea_set_one_line(tal, true);//设置一行
    lv_textarea_set_text(tal, "3");

    tal = lv_textarea_create(Set_scr);//创建文本输入框
    lv_obj_remove_style_all(tal);
    lv_obj_add_style(tal, &Set_Text, LV_PART_MAIN);//添加文本框样式
    lv_obj_set_size(tal, 125, 50);//设置控件尺寸
    lv_obj_set_pos(tal, 600, 330);//设置坐标
 //   lv_textarea_set_placeholder_text(ta, "0.00");//设置占位字符
    lv_obj_add_event_cb(tal, ta_event_cb, LV_EVENT_ALL, kb);//设置回调函数
    lv_textarea_set_accepted_chars(tal, "0123456789");//设置输入接受的范围
    lv_textarea_set_max_length(tal, 3);//设置文本框最大长度
    lv_textarea_set_one_line(tal, true);//设置一行
    lv_textarea_set_text(tal, "4");

    tal = lv_textarea_create(Set_scr);//创建文本输入框
    lv_obj_remove_style_all(tal);
    lv_obj_add_style(tal, &Set_Text, LV_PART_MAIN);//添加文本框样式
    lv_obj_set_size(tal, 125, 50);//设置控件尺寸
    lv_obj_set_pos(tal, 185, 330);//设置坐标
 //   lv_textarea_set_placeholder_text(ta, "0.00");//设置占位字符
 //   lv_obj_add_event_cb(tal, ta_event_cb, LV_EVENT_ALL, kb);//设置回调函数
//    lv_textarea_set_accepted_chars(tal, "0123456789");//设置输入接受的范围
    lv_textarea_set_max_length(tal, 6);//设置文本框最大长度
    lv_textarea_set_one_line(tal, true);//设置一行
    lv_textarea_set_text(tal, " Dew");

    tal = lv_textarea_create(Set_scr);//创建文本输入框
    lv_obj_remove_style_all(tal);
    lv_obj_add_style(tal, &Set_Text, LV_PART_MAIN);//添加文本框样式
    lv_obj_set_size(tal, 125, 50);//设置控件尺寸
    lv_obj_set_pos(tal, 600, 90);//设置坐标
    lv_textarea_set_max_length(tal, 6);//设置文本框最大长度
    lv_textarea_set_one_line(tal, true);//设置一行
    lv_textarea_set_text(tal, " F");

    tal = lv_textarea_create(Set_scr);//创建文本输入框
    lv_obj_remove_style_all(tal);
    lv_obj_add_style(tal, &Set_Text, LV_PART_MAIN);//添加文本框样式
    lv_obj_set_size(tal, 125, 50);//设置控件尺寸
    lv_obj_set_pos(tal, 600, 150);//设置坐标
 //   lv_textarea_set_placeholder_text(ta, "0.00");//设置占位字符
 //   lv_obj_add_event_cb(tal, ta_event_cb, LV_EVENT_ALL, kb);//设置回调函数
//    lv_textarea_set_accepted_chars(tal, "0123456789");//设置输入接受的范围
    lv_textarea_set_max_length(tal, 6);//设置文本框最大长度
    lv_textarea_set_one_line(tal, true);//设置一行
    lv_textarea_set_text(tal, " English");



    static lv_style_t text_style;
    lv_style_init(&text_style);
    lv_style_set_text_font(&text_style, &lv_font_montserrat_18);
    lv_style_set_text_color(&text_style, lv_color_white());
    lv_style_set_text_align(&text_style, LV_ALIGN_CENTER);

    lv_obj_t* label_t;

    label_t = lv_label_create(Set_scr);
    lv_obj_add_style(label_t, &text_style, LV_STATE_DEFAULT);
    lv_label_set_text(label_t, "min"); // 设置标签文本
    lv_obj_set_pos(label_t, 670, 212); // 设置按钮对象的位置X和Y

    label_t = lv_label_create(Set_scr);
    lv_obj_add_style(label_t, &text_style, LV_STATE_DEFAULT);
    lv_label_set_text(label_t, "min"); // 设置标签文本
    lv_obj_set_pos(label_t, 670, 212+60); // 设置按钮对象的位置X和Y

    label_t = lv_label_create(Set_scr);
    lv_obj_add_style(label_t, &text_style, LV_STATE_DEFAULT);
    lv_label_set_text(label_t, "Hour"); // 设置标签文本
    lv_obj_set_pos(label_t, 670, 212+120); // 设置按钮对象的位置X和Y

    /*Create a keyboard*/
    kb = lv_keyboard_create(Set_scr);
    lv_obj_set_size(kb, 240, 280);
    lv_obj_set_pos(kb, 0, 0);
    lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_NUMBER);
//    lv_keyboard_set_textarea(kb, Tempta);
    lv_obj_add_flag(kb,LV_OBJ_FLAG_HIDDEN);
}



static void Set_scr_Create()
{
    
    lv_style_init(&style_Set_label); // 初始化按钮样式
    lv_style_set_text_font(&style_Set_label, &lv_font_montserrat_20);
    lv_style_set_text_color(&style_Set_label, lv_color_white());

    static lv_style_t style_home_btn;//添加设置页面房子按钮样式
    lv_style_init(&style_home_btn); // 初始化按钮样式
    lv_style_set_radius(&style_home_btn, 0); // 设置按钮样式圆角弧度
    lv_style_set_bg_opa(&style_home_btn, LV_OPA_COVER); // 设置背景的透明度
    lv_style_set_bg_color(&style_home_btn, lv_color_make(0, 191, 255)); // 设置背景的颜色为背景色一样
    lv_style_set_border_color(&style_home_btn, lv_color_white()); // 设置边框颜色为白色
    lv_style_set_border_opa(&style_home_btn, LV_OPA_100); // 设置边框透明度为100%
    lv_style_set_border_width(&style_home_btn, 4); // 设置边框宽度为2
    lv_style_set_text_font(&style_home_btn, &my_font_image);

    lv_obj_t* Home_btn = lv_btn_create(Set_scr);//创建房子按钮
    lv_obj_set_pos(Home_btn, 740, 0); // 设置按钮对象的位置X和Y
    lv_obj_set_size(Home_btn, 60, 60); // 设置按钮对象的宽度和高度
    lv_obj_add_event_cb(Home_btn, Home_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_style(Home_btn, &style_home_btn, LV_STATE_DEFAULT); // 给按钮对象添加默认样式
    lv_obj_add_style(Home_btn, &style_pr, LV_STATE_PRESSED); // 给按钮对象添加按下状态的样式

    lv_obj_t* label = lv_label_create(Home_btn);
    lv_label_set_text(label, MY_HOME); // 设置标签文本
    lv_obj_align_to(label, Home_btn, LV_ALIGN_TOP_MID, 0, -7);//标签在按钮居中对其向下偏移30

    //添加设置页面齿轮标签样式
    static lv_style_t style_Set_page;
    lv_style_init(&style_Set_page); // 初始化按钮样式
    lv_style_set_text_font(&style_Set_page, &lv_font_montserrat_40);
    lv_style_set_text_color(&style_Set_page, lv_color_white());

    lv_obj_t* Set_label = lv_label_create(Set_scr);
    lv_obj_add_style(Set_label, &style_Set_page, LV_STATE_DEFAULT); // 给对象添加默认样式
    lv_label_set_text(Set_label, LV_SYMBOL_SETTINGS); // 设置标签文本
    lv_obj_set_pos(Set_label, 35, 10);

    //添加设置页面SET标签
    static lv_style_t style_Set_label;
    lv_style_init(&style_Set_label); // 初始化按钮样式
    lv_style_set_text_font(&style_Set_label, &lv_font_montserrat_20);
    lv_style_set_text_color(&style_Set_label, lv_color_white());

    lv_obj_t* Set_label_1 = lv_label_create(Set_scr);
    lv_obj_add_style(Set_label_1, &style_Set_label, LV_STATE_DEFAULT); // 给对象添加默认样式
    lv_label_set_text(Set_label_1, "SET"); // 设置标签文本
    lv_obj_align_to(Set_label_1, Set_label, LV_ALIGN_OUT_RIGHT_MID, 5, 0);//标签在按钮居中对其向下偏移30

    Set_page_label_create("TempCail",    1, 1);
    Set_page_label_create("DewCail",     1, 2);
    Set_page_label_create("LEDCur",      1, 3);
    Set_page_label_create("Address",     1, 4);
    Set_page_label_create("Dew/Frost",   1, 5);
    Set_page_label_create("Brightness",  1, 6);

    Set_page_label_create("TempUnit",   2, 1);
    Set_page_label_create("Language",   2, 2);
    Set_page_label_create("MaxMinTime", 2, 3);
    Set_page_label_create("BassTime",   2, 4);
    Set_page_label_create("DBCTime",    2, 5);
    Set_page_label_create("eFrost",     2, 6);
    Brightness_slider();//背光调节滑块
    eFrost_switch();//强制结霜开关
    TempCail_Text();
}


static void scr_bg_set()
{
    scr = lv_scr_act();
    lv_style_init(&style_scr); // 初始化样式
    lv_style_reset(&style_scr); // 重置样式
    lv_style_set_bg_color(&style_scr, lv_color_make(0, 191, 255));
    lv_obj_add_style(scr, &style_scr, LV_STATE_DEFAULT);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);//禁止滑动

    Set_scr = lv_obj_create(NULL);
    lv_style_init(&style_set_scr); // 初始化样式
    lv_style_reset(&style_set_scr); // 重置样式
    lv_style_set_bg_color(&style_set_scr, lv_color_make(0, 191, 255));
    lv_obj_add_style(Set_scr, &style_set_scr, LV_STATE_DEFAULT);
    lv_obj_clear_flag(Set_scr, LV_OBJ_FLAG_SCROLLABLE);//禁止滑动
    Set_scr_Create();//创建设置页面
}
static void Main_line_set()
{
    /*Create an array for the points of the line*/
    static lv_point_t line_points[] = { {2, 2}, {2, 478},{798, 478} ,{798, 2},{2,2} };
    static lv_point_t line1_points[] = { {0, 320}, {800, 320} };
    static lv_point_t line2_points[] = { {425, 0}, {425, 320} };
    static lv_point_t line3_points[] = { {425, 105}, {800, 105} };
    static lv_point_t line4_points[] = { {425, 215}, {800, 215} };
    static lv_point_t line5_points[] = { {70, 20}, {70, 240}, {390, 240} };



    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 4);//设置宽度
    lv_style_set_line_color(&style_line, lv_color_make(255, 255, 255));
    lv_style_set_line_rounded(&style_line, true);

    /*Create a line and apply the new style*/
    lv_obj_t* line;
    line = lv_line_create(scr);
    lv_obj_set_pos(line, 0, 0); 
    lv_line_set_points(line, line_points, 5);     /*Set the points*/
    lv_obj_add_style(line, &style_line, LV_PART_MAIN);


    lv_obj_t* line2;
    line2 = lv_line_create(scr);
    lv_obj_set_pos(line2, 0, 0);
    lv_line_set_points(line2, line1_points, 2);     /*Set the points*/
    lv_obj_add_style(line2, &style_line, LV_PART_MAIN);

    lv_obj_t* line3;
    line3 = lv_line_create(scr);
    lv_obj_set_pos(line3, 0, 0);
    lv_line_set_points(line3, line2_points, 2);     /*Set the points*/
    lv_obj_add_style(line3, &style_line, LV_PART_MAIN);

    lv_obj_t* line4;
    line4 = lv_line_create(scr);
    lv_obj_set_pos(line4, 0, 0);
    lv_line_set_points(line4, line3_points, 2);     /*Set the points*/
    lv_obj_add_style(line4, &style_line, LV_PART_MAIN);

    lv_obj_t* line5;
    line5 = lv_line_create(scr);
    lv_obj_set_pos(line5, 0, 0);
    lv_line_set_points(line5, line4_points, 2);     /*Set the points*/
    lv_obj_add_style(line5, &style_line, LV_PART_MAIN);

    lv_obj_t* line6;
    line6 = lv_line_create(scr);
    lv_obj_set_pos(line6, 0, 0);
    lv_line_set_points(line6, line5_points, 3);     /*Set the points*/
    lv_obj_add_style(line6, &style_line, LV_PART_MAIN);

    static lv_point_t Set_line_points[] = { {2, 58}, {800, 58}};
    lv_obj_t* line7;
    line7 = lv_line_create(Set_scr);
    lv_obj_set_pos(line7, 0, 0);
    lv_line_set_points(line7, line_points, 5);     /*Set the points*/
    lv_obj_add_style(line7, &style_line, LV_PART_MAIN);

    lv_obj_t* line8;
    line8 = lv_line_create(Set_scr);
    lv_obj_set_pos(line8, 0, 0);
    lv_line_set_points(line8, Set_line_points, 2);     /*Set the points*/
    lv_obj_add_style(line8, &style_line, LV_PART_MAIN);






}

void main_label_creat()
{
    static lv_style_t style_main_label;

    lv_obj_t* scr = lv_scr_act();
    lv_style_init(&style_main_label); // 初始化按钮样式
    lv_style_set_text_color(&style_main_label, lv_color_white()); //设置字体颜色为白色

    lv_obj_t* Maxlabel = lv_label_create(scr); // 给按钮添加标签
    lv_obj_add_style(Maxlabel, &style_main_label, LV_STATE_DEFAULT);
    lv_label_set_text(Maxlabel, "Max:"); // 设置标签文本
    lv_obj_set_pos(Maxlabel, 670, 20); // 设置按钮对象的位置X和Y

    lv_obj_t* Minlabel = lv_label_create(scr); // 给按钮添加标签
    lv_obj_add_style(Minlabel, &style_main_label, LV_STATE_DEFAULT);
    lv_label_set_text(Minlabel, "Min:"); // 设置标签文本
    lv_obj_set_pos(Minlabel, 670, 40); // 设置按钮对象的位置X和Y

    lv_obj_t* Maxlabel_1 = lv_label_create(scr); // 给按钮添加标签
    lv_obj_add_style(Maxlabel_1, &style_main_label, LV_STATE_DEFAULT);
    lv_label_set_text(Maxlabel_1, "Max:"); // 设置标签文本
    lv_obj_set_pos(Maxlabel_1, 670, 125); // 设置按钮对象的位置X和Y

    lv_obj_t* Minlabel_1 = lv_label_create(scr); // 给按钮添加标签
    lv_obj_add_style(Minlabel_1, &style_main_label, LV_STATE_DEFAULT);
    lv_label_set_text(Minlabel_1, "Min:"); // 设置标签文本
    lv_obj_set_pos(Minlabel_1, 670, 145); // 设置按钮对象的位置X和Y

    lv_obj_t* Maxlabel_2 = lv_label_create(scr); // 给按钮添加标签
    lv_obj_add_style(Maxlabel_2, &style_main_label, LV_STATE_DEFAULT);
    lv_label_set_text(Maxlabel_2, "Max:"); // 设置标签文本
    lv_obj_set_pos(Maxlabel_2, 670, 235); // 设置按钮对象的位置X和Y

    lv_obj_t* Minlabel_2 = lv_label_create(scr); // 给按钮添加标签
    lv_obj_add_style(Minlabel_2, &style_main_label, LV_STATE_DEFAULT);
    lv_label_set_text(Minlabel_2, "Min:"); // 设置标签文本
    lv_obj_set_pos(Minlabel_2, 670, 255); // 设置按钮对象的位置X和Y
}

lv_color_t color_darken (const lv_color_filter_dsc_t* des , lv_color_t color, lv_opa_t opa)
{
    LV_UNUSED(des);

    return lv_color_darken(color, opa);
}

static void button_style_init()
{
    lv_style_init(&style_btn); // 初始化按钮样式
    
    lv_style_set_radius(&style_btn, 20); // 设置按钮样式圆角弧度
    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER); // 设置背景的透明度
    lv_style_set_bg_color(&style_btn, lv_color_make(0, 191, 255)); // 设置背景的颜色为背景色一样
    lv_style_set_border_color(&style_btn, lv_color_white()); // 设置边框颜色为白色
    lv_style_set_border_opa(&style_btn, LV_OPA_100); // 设置边框透明度为100%
    lv_style_set_border_width(&style_btn, 4); // 设置边框宽度为2
    lv_style_set_text_color(&style_btn, lv_color_white()); //设置字体颜色为白色
    lv_style_set_text_font(&style_btn,  &lv_font_montserrat_20);
    
    /*
     创建一个颜色过滤器，用于修改button对象按下时的颜色样式
    */
    static lv_color_filter_dsc_t color_filter;
    lv_color_filter_dsc_init(&color_filter, color_darken); // 初始化颜色过滤器，并添加回调函数 
    lv_style_init(&style_btn_pressed); // 初始化按钮按下的样式
    lv_style_set_color_filter_dsc(&style_btn_pressed, &color_filter); // 给当前样式设置颜色过滤器
    lv_style_set_color_filter_opa(&style_btn_pressed, LV_OPA_20); // 过滤颜色透明度为20%


    /*创建口香糖式的点击效果
    */
    /*Properties to transition*/
    static lv_style_prop_t props[] = {
            LV_STYLE_TRANSFORM_WIDTH, LV_STYLE_TRANSFORM_HEIGHT, LV_STYLE_TEXT_LETTER_SPACE, LV_STYLE_PROP_INV
    };

    /*Transition descriptor when going back to the default state.
     *Add some delay to be sure the press transition is visible even if the press was very short*/
    static lv_style_transition_dsc_t transition_dsc_def;
    lv_style_transition_dsc_init(&transition_dsc_def, props, lv_anim_path_overshoot, 250, 100, NULL);

    /*Transition descriptor when going to pressed state.
     *No delay, go to presses state immediately*/
    static lv_style_transition_dsc_t transition_dsc_pr;
    lv_style_transition_dsc_init(&transition_dsc_pr, props, lv_anim_path_ease_in_out, 250, 0, NULL);

    /*Add the transition and some transformation to the presses state.*/
    lv_style_init(&style_pr);
    lv_style_set_transform_width(&style_pr, 10);
    lv_style_set_transform_height(&style_pr, -10);
    lv_style_set_transition(&style_pr, &transition_dsc_pr);
}
//#define LV_FONT_CONSTOM_DECLARE	LV_FONT_DECLARE();


void main_btn_creat()
{
    lv_obj_t* label = NULL;
    static lv_style_t style_label;
    static lv_style_t my_style_label_image;
    /*创建button对象并使用新的样式*/
    Set_btn = lv_btn_create(lv_scr_act());
    if (Set_btn != NULL)
    {
        /*
         从当前主题移除所有样式
         注意：大小和位置也是样式属性，lv_obj_remove_style_all也会移除对象的大小和位置
        */
        lv_obj_remove_style_all(Set_btn);
        lv_obj_set_pos(Set_btn, 625, 340); // 设置按钮对象的位置X和Y
        lv_obj_set_size(Set_btn, 115, 115); // 设置按钮对象的宽度和高度
        lv_obj_add_event_cb(Set_btn, event_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_add_style(Set_btn, &style_btn, LV_STATE_DEFAULT); // 给按钮对象添加默认样式
        lv_obj_add_style(Set_btn, &style_pr, LV_STATE_PRESSED); // 给按钮对象添加按下状态的样式

        label = lv_label_create(Set_btn); // 给按钮添加标签
        if (label != NULL)
        {
            lv_label_set_text(label, "SET"); // 设置标签文本
            lv_obj_align_to(label, Set_btn, LV_ALIGN_CENTER, 0, 30);//标签在按钮居中对其向下偏移30
        }
        label = lv_label_create(Set_btn); // 给按钮添加标签
        if (label != NULL)
        {
            lv_style_init(&style_label); // 初始化按钮样式
            lv_style_set_text_font(&style_label, &lv_font_montserrat_40);
            lv_obj_add_style(label, &style_label, LV_STATE_DEFAULT);
            lv_label_set_text(label, LV_SYMBOL_SETTINGS); // 设置标签文本
            lv_obj_align_to(label, Set_btn, LV_ALIGN_CENTER, 0, -10);//标签在按钮居中对其向下偏移30
        }
    }

    
    DBC_btn = lv_btn_create(lv_scr_act());
    if (DBC_btn != NULL)
    {
        lv_obj_remove_style_all(DBC_btn); // 从当前主题移除所有样式
        lv_obj_set_pos(DBC_btn, 430, 340); // 设置按钮对象的位置X和Y
        lv_obj_set_size(DBC_btn, 115, 115); // 设置按钮对象的宽度和高度

        lv_obj_add_style(DBC_btn, &style_btn, LV_STATE_DEFAULT); // 添加对象的默认样式
        lv_obj_add_style(DBC_btn, &style_pr, LV_STATE_PRESSED); // 添加对象的按下状态样式
        lv_obj_set_style_radius(DBC_btn, LV_RADIUS_CIRCLE, 100);  // 添加按钮对象的圆角弧度样式

        label = lv_label_create(DBC_btn); // 给btn2对象创建标签
        if (label != NULL)
        {
            lv_label_set_text(label, "DBC"); // 设置标签文本
            lv_obj_align_to(label, DBC_btn, LV_ALIGN_CENTER, 0, 30);//标签在按钮居中对其向下偏移30
        }
        label = lv_label_create(DBC_btn); // 给按钮添加标签
        if (label != NULL)
        {
            lv_style_init(&style_label); // 初始化按钮样式
            lv_style_set_text_font(&style_label, &lv_font_montserrat_40);
            lv_obj_add_style(label, &style_label, LV_STATE_DEFAULT);
            lv_label_set_text(label, LV_SYMBOL_REFRESH); // 设置标签文本
            lv_obj_align_to(label, DBC_btn, LV_ALIGN_CENTER, 0, -10);//标签在按钮居中对其向下偏移30
        }

    }


    Fan_btn = lv_btn_create(lv_scr_act());
    if (Fan_btn != NULL)
    {
        lv_obj_remove_style_all(Fan_btn); // 从当前主题移除所有样式
        lv_obj_set_pos(Fan_btn, 250, 340); // 设置按钮对象的位置X和Y
        lv_obj_set_size(Fan_btn, 115, 115); // 设置按钮对象的宽度和高度
        lv_obj_add_state(Fan_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_style(Fan_btn, &style_btn, LV_STATE_DEFAULT); // 添加对象的默认样式
        lv_obj_add_style(Fan_btn, &style_btn, LV_STATE_PRESSED); // 默认样式和点击样式相同  点击没有显示效果
        lv_obj_set_style_radius(Fan_btn, LV_RADIUS_CIRCLE, 100);  // 添加按钮对象的圆角弧度样式

        label = lv_label_create(Fan_btn); // 给btn2对象创建标签
        if (label != NULL)
        {
            lv_label_set_text_fmt(label, "%d.%d%%",12,1); // 设置标签文本
            lv_obj_align_to(label, Fan_btn, LV_ALIGN_CENTER, 0, 30);//标签在按钮居中对其向下偏移30
        }
        label = lv_label_create(Fan_btn); // 给按钮添加标签
        if (label != NULL)
        {
            lv_style_init(&my_style_label_image); // 初始化按钮样式
            lv_style_set_text_font(&my_style_label_image, &my_font_image);
            lv_obj_add_style(label, &my_style_label_image, LV_STATE_DEFAULT);
            lv_label_set_text(label, MY_FANSHE); // 设置标签文本
            lv_obj_align_to(label, Fan_btn, LV_ALIGN_CENTER, 0, -10);//标签在按钮居中对其向下偏移30
        }
    }

    Cool_btn = lv_btn_create(lv_scr_act());
    if (Cool_btn != NULL)
    {
        lv_obj_remove_style_all(Cool_btn); // 从当前主题移除所有样式
        lv_obj_set_pos(Cool_btn, 75, 340); // 设置按钮对象的位置X和Y
        lv_obj_set_size(Cool_btn, 115, 115); // 设置按钮对象的宽度和高度

        lv_obj_add_style(Cool_btn, &style_btn, LV_STATE_DEFAULT); // 添加对象的默认样式
        lv_obj_add_style(Cool_btn, &style_btn, LV_STATE_PRESSED); // 添加对象的按下状态样式
        lv_obj_set_style_radius(Cool_btn, LV_RADIUS_CIRCLE, 100);  // 添加按钮对象的圆角弧度样式

        label = lv_label_create(Cool_btn); // 给btn2对象创建标签
        if (label != NULL)
        {
            lv_label_set_text_fmt(label, "%d.%d%%", 30, 1); // 设置标签文本
            lv_obj_align_to(label, Cool_btn, LV_ALIGN_CENTER, 0, 30);//标签在按钮居中对其向下偏移30
        }
        label = lv_label_create(Cool_btn); // 给按钮添加标签
        if (label != NULL)
        {
            lv_style_init(&my_style_label_image); // 初始化按钮样式
            lv_style_set_text_font(&my_style_label_image, &my_font_image);
            lv_obj_add_style(label, &my_style_label_image, LV_STATE_DEFAULT);
            lv_label_set_text(label, MY_jingmian); // 设置标签文本
            lv_obj_align_to(label, Cool_btn, LV_ALIGN_CENTER, 0, 10);//标签在按钮居中对其向下偏移30
        }
        label = lv_label_create(Cool_btn); // 给按钮添加标签
        if (label != NULL)
        {
            lv_style_init(&my_style_label_image); // 初始化按钮样式
            lv_style_set_text_font(&my_style_label_image, &my_font_image);
            lv_obj_add_style(label, &my_style_label_image, LV_STATE_DEFAULT);
            lv_label_set_text(label, MY_ZHILENG); // 设置标签文本
            lv_obj_align_to(label, DBC_btn, LV_ALIGN_CENTER, 5, -18);//标签在按钮居中对其向下偏移30
        }
        label = lv_label_create(Cool_btn); // 给按钮添加标签
        if (label != NULL)
        {
            lv_style_init(&my_style_label_image); // 初始化按钮样式
            lv_style_set_text_font(&my_style_label_image, &my_font_image);
            lv_obj_add_style(label, &my_style_label_image, LV_STATE_DEFAULT);
            lv_label_set_text(label, MY_Down_jiantou); // 设置标签文本
            lv_obj_align_to(label, Cool_btn, LV_ALIGN_CENTER, -25, -13);//标签在按钮居中对其向下偏移30
        }

    }
    main_label_creat();

    static lv_style_t style_mainVal_label;
    lv_style_init(&style_mainVal_label); // 初始化按钮样式
    lv_style_set_text_color(&style_mainVal_label, lv_color_white()); //设置字体颜色为白色
    lv_style_set_text_font(&style_mainVal_label, &lv_font_montserrat_20);

    TMP = lv_label_create(scr); // 给按钮添加标签
    lv_obj_add_style(TMP, &style_mainVal_label, LV_STATE_DEFAULT);
    lv_label_set_text(TMP, "Temperature"); // 设置标签文本
    lv_obj_align_to(TMP, DBC_btn, LV_ALIGN_LEFT_MID, 0, -380);//标签在按钮居中对其向下偏移30

    RH = lv_label_create(scr); // 给按钮添加标签
    lv_obj_add_style(RH, &style_mainVal_label, LV_STATE_DEFAULT);
    lv_label_set_text(RH, "Relative Humidity"); // 设置标签文本
    lv_obj_align_to(RH, DBC_btn, LV_ALIGN_LEFT_MID, 0, -270);//标签在按钮居中对其向下偏移30

    DEW = lv_label_create(scr); // 给按钮添加标签
    lv_obj_add_style(DEW, &style_mainVal_label, LV_STATE_DEFAULT);
    lv_label_set_text(DEW, "Dew"); // 设置标签文本
    lv_obj_align_to(DEW, DBC_btn, LV_ALIGN_LEFT_MID, 0, -160);//标签在按钮居中对其向下偏移30
}

//#define MY_suoding          "\xEE\x98\x80"
//#define MY_jiesuo           "\xEE\x98\x81"
//#define MY_UPjiantou        "\xEE\x98\xAF"
//#define MY_Down_jiantou     "\xEE\x98\xB0"
//#define MY_jingmian         "\xEE\x98\xB7"
//#define MY_HOME             "\xEE\xA3\xBF"
//#define MY_ZHILENG          "\xEE\x9A\x84"
//#define MY_JIARE            "\xEE\x9F\xAD"

/*三个数据栏的参数控件*/
lv_obj_t* main_val_1;
lv_obj_t* main_val_2;
lv_obj_t* main_val_3;

short main_num;

void main_val_creat()
{
    static lv_style_t style_mainVal;
    lv_style_init(&style_mainVal); // 初始化按钮样式
    lv_style_set_text_color(&style_mainVal, lv_color_white()); //设置字体颜色为白色
    lv_style_set_text_font(&style_mainVal, &lv_font_montserrat_40);

    lv_obj_t* scr = lv_scr_act();
    main_val_1 = lv_label_create(scr); // 添加标签
    main_val_2 = lv_label_create(scr); // 添加标签
    main_val_3 = lv_label_create(scr); // 添加标签

    lv_obj_add_style(main_val_1, &style_mainVal, LV_STATE_DEFAULT);
    lv_label_set_text_fmt(main_val_1, "%d.%d C",12,34); // 设置标签文本
    lv_obj_set_pos(main_val_1, 435, 40);

    lv_obj_add_style(main_val_2, &style_mainVal, LV_STATE_DEFAULT);
    lv_label_set_text_fmt(main_val_2, "%d.%d%%", 23, 45); // 设置标签文本
    lv_obj_set_pos(main_val_2, 435, 150);

    lv_obj_add_style(main_val_3, &style_mainVal, LV_STATE_DEFAULT);
    lv_label_set_text_fmt(main_val_3, "%d.%d C", 34, 56); // 设置标签文本
    lv_obj_set_pos(main_val_3, 435, 260);

}
/*曲线更新函数*/
#include "stdio.h"
#include "stdlib.h"
static lv_point_t curve_point[200] = {0 };
void curve_creat()
{
    uint8_t i = 0,m=3;
    int16_t j = 0, k = 72;
    /*Create style*/
    static lv_style_t style_curve;
    lv_style_init(&style_curve);
    lv_style_set_line_width(&style_curve, 2);//设置宽度
    lv_style_set_line_color(&style_curve, lv_color_make(255, 0, 255));


    /*Create a line and apply the new style*/
    lv_obj_t* curve;
    curve = lv_line_create(scr);

    for (i = 0; i < 200; i++)
    {
        j= 236-m;
        //j = 236 - m;

        k++;;
        if (i < 100)
        {
            m += rand() % 2; 
        }
        else
        {
            m -= rand() % 2; 
        }
        curve_point[i].x = k;
        curve_point[i].y = j;
    }
 //   lv_obj_set_pos(curve, 70+4, 240-4);
    lv_line_set_points(curve, curve_point, 200);     /*Set the points*/
    lv_obj_add_style(curve, &style_curve, LV_PART_MAIN);
}
/**
创建button对象，并添加样式
 */
void lv_test()
{
    button_style_init(); // 按钮样式初始化
    scr_bg_set();   //  设置屏幕背景色
    Main_line_set();//画线条
    main_btn_creat();//创建主页按钮
    main_val_creat();//创建主要参数值
    curve_creat();//创建曲线
}



int main()
{
    lv_init();

    if (!lv_win32_init(
        GetModuleHandleW(NULL),
        SW_SHOW,
        800,
        480,
        LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_LVGL))))
    {
        return -1;
    }

    lv_win32_add_all_input_devices_to_group(NULL);

    lv_win32_filesystem_driver_initialize();

    /*
     * Demos, benchmarks, and tests.
     *
     * Uncomment any one (and only one) of the functions below to run that
     * item.
     */

    // ----------------------------------
    // my application
    // ----------------------------------

    ///*Init freetype library
    // *Cache max 64 faces and 1 size*/
    //lv_freetype_init(64, 1, 0);

    ///*Create a font*/
    //static lv_ft_info_t info;
    //info.name = "./lv_lib_freetype/arial.ttf";
    //info.weight = 36;
    //info.style = FT_FONT_STYLE_NORMAL;
    //lv_ft_font_init(&info);

    ///*Create style with the new font*/
    //static lv_style_t style;
    //lv_style_init(&style);
    //lv_style_set_text_font(&style, info.font);

    ///*Create a label with the new style*/
    //lv_obj_t* label = lv_label_create(lv_scr_act());
    //lv_obj_add_style(label, &style, 0);
    //lv_label_set_text(label, "FreeType Arial Test");

    // ----------------------------------
    // Demos from lv_examples
    // ----------------------------------

    lv_fs_dir_t d;
    if (lv_fs_dir_open(&d, "/") == LV_FS_RES_OK)
    {
        char b[MAX_PATH];
        memset(b, 0, MAX_PATH);
        while (lv_fs_dir_read(&d, b) == LV_FS_RES_OK)
        {
            printf("%s\n", b);
        }

        lv_fs_dir_close(&d);
    }
  
    //lv_test();
     //lv_demo_widgets();           // ok
    // lv_demo_benchmark();
    // lv_demo_keypad_encoder();    // ok
    lv_demo_music();             // removed from repository
    // lv_demo_printer();           // removed from repository
    // lv_demo_stress();            // ok

    // ----------------------------------
    // LVGL examples
    // ----------------------------------

    /*
     * There are many examples of individual widgets found under the
     * lvgl\exampless directory.  Here are a few sample test functions.
     * Look in that directory to find all the rest.
     */

     //lv_ex_get_started_1();
    // lv_ex_get_started_2();
    // lv_ex_get_started_3();

    // lv_example_flex_1();
    // lv_example_flex_2();
    // lv_example_flex_3();
    // lv_example_flex_4();
    // lv_example_flex_5();
    // lv_example_flex_6();        // ok

    // lv_example_grid_1();
    // lv_example_grid_2();
    // lv_example_grid_3();
    // lv_example_grid_4();
    // lv_example_grid_5();
    // lv_example_grid_6();

    // lv_port_disp_template();
    // lv_port_fs_template();
    // lv_port_indev_template();

    // lv_example_scroll_1();
    // lv_example_scroll_2();
    // lv_example_scroll_3();

    // lv_example_style_1();
    // lv_example_style_2();
    // lv_example_style_3();
    // lv_example_style_4();        // ok
    // lv_example_style_6();        // file has no source code
    // lv_example_style_7();
    // lv_example_style_8();
    // lv_example_style_9();
    // lv_example_style_10();
    // lv_example_style_11();       // ok

    // ----------------------------------
    // LVGL widgets examples
    // ----------------------------------

    // lv_example_arc_1();
    // lv_example_arc_2();

    // lv_example_bar_1();          // ok
    // lv_example_bar_2();
    // lv_example_bar_3();
    // lv_example_bar_4();
    // lv_example_bar_5();
    // lv_example_bar_6();          // issues

    // lv_example_btn_1();
    // lv_example_btn_2();
    // lv_example_btn_3();

    // lv_example_btnmatrix_1();
    // lv_example_btnmatrix_2();
    // lv_example_btnmatrix_3();

    // lv_example_calendar_1();

    // lv_example_canvas_1();
    // lv_example_canvas_2();

    // lv_example_chart_1();        // ok
    // lv_example_chart_2();        // ok
    // lv_example_chart_3();        // ok
    // lv_example_chart_4();        // ok
    // lv_example_chart_5();        // ok
    // lv_example_chart_6();        // ok

    // lv_example_checkbox_1();

    // lv_example_colorwheel_1();   // ok

    // lv_example_dropdown_1();
    // lv_example_dropdown_2();
    // lv_example_dropdown_3();

    // lv_example_img_1();
    // lv_example_img_2();
    // lv_example_img_3();
    // lv_example_img_4();         // ok

    // lv_example_imgbtn_1();

    // lv_example_keyboard_1();    // ok

    // lv_example_label_1();
    // lv_example_label_2();       // ok

    // lv_example_led_1();

    // lv_example_line_1();

    // lv_example_list_1();

    // lv_example_meter_1();
    // lv_example_meter_2();
    // lv_example_meter_3();
    // lv_example_meter_4();       // ok

    // lv_example_msgbox_1();

    // lv_example_obj_1();         // ok

    // lv_example_roller_1();
    // lv_example_roller_2();      // ok

    // lv_example_slider_1();      // ok
    // lv_example_slider_2();      // issues
    // lv_example_slider_3();      // issues

    // lv_example_spinbox_1();

    // lv_example_spinner_1();     // ok

     //lv_example_switch_1();      // ok

    // lv_example_table_1();
    // lv_example_table_2();       // ok

    // lv_example_tabview_1();

    // lv_example_textarea_1();    // ok
    // lv_example_textarea_2();
    // lv_example_textarea_3();    // ok, but not all button have functions

    // lv_example_tileview_1();    // ok

     //lv_example_win_1();         // ok

    // ----------------------------------
    // Task handler loop
    // ----------------------------------

    while (!lv_win32_quit_signal)
    {
        lv_task_handler();
        Sleep(1);
    }

    return 0;
}
