# Measuer_Project

# �?境监�?

## �?�? ##
* 主控：STM32F411RE
* 显示：LCD 240*240
* 温湿度传感器：SHT20(盛思瑞)
* TVOC传感�?：SGP40(盛思瑞)�?能测试空气质量指数，因为考虑SGP30的发�?没有选择用SGP30
* 蜂鸣�?
* 电池-充电管理电路
* 按键开机电�?
* SD卡接�?
* typc-C接口
* 功耗测�?
## �?�?
* LVGL
* 时间管理框架
* 后期考虑用加入更多功能，让环境测量仪成为一�?更好的�?�面摆件，小伙伴�?�?以�?��?�提出意见�?
* �?前通过SD卡储存UI图片的方式，刷屏还是容易卡顿不太理想


# [V0.1]
* 注意从Cubemx生成的代�? SD卡部�? 需要做出下�?�?�? 
```
uint8_t	BSP_PlatformIsDetected(void) {
    uint8_t status = SD_PRESENT;
    /* Check SD card detect pin */
//    if(HAL_GPIO_ReadPin(SD_DETECT_GPIO_PORT, SD_DETECT_PIN) != GPIO_PIN_RESET)
//    {
//        status = SD_NOT_PRESENT;
//    }
    /* USER CODE BEGIN 1 */
    /* user code can be inserted here */
    /* USER CODE END 1 */
    return status;
}
```
* 文件系统已经移�?�完成在LVGL里面�?以调�?,来显示SD卡中的文件�?
```
lv_img_set_src(ui_TVOC,"S:/pic/tvoc2.bin");
```
* 如果需要屏幕镜像可以屏蔽LCD_Init的代�?
```
	LCD_WR_REG(0x36); 
	LCD_WR_DATA8(0x40); //镜像显示
```
* 后期�?以考虑在SD卡加上储存数�?的功�?


# 模型

重新上传左壳和右底座，太高电�?板，防�?�充电或运�?�发�?影响温湿度传感器测量


