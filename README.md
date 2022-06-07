# Measuer_Project
# 环境监测

## 硬件 ##
* 主控：STM32F411RE
* 显示：LCD 240*240
* 温湿度传感器：SHT31(盛思瑞)
* TVOC传感器：SGP40(盛思瑞)只能测试空气质量指数，因为考虑SGP30的发热没有选择用SGP30
* 蜂鸣器
* 电池-充电管理电路
* 按键开机电路
* SD卡接口
* typc-C接口
* 功耗测量
----
## 软件
* LVGL
* 时间管理框架


----
# [V0.1]
* 注意从Cubemx生成的代码 SD卡部分 需要做出下面修改 
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
* 文件系统已经移植完成在LVGL里面可以调用,来显示SD卡中的文件。
```
lv_img_set_src(ui_TVOC,"S:/pic/tvoc2.bin");
```
* 如果需要屏幕镜像可以屏蔽LCD_Init的代码
```
	LCD_WR_REG(0x36); 
	LCD_WR_DATA8(0x40); //镜像显示
```
* 后期可以考虑在SD卡加上储存数据的功能


## 模型 ##
左壳儿V3是最新修改后的模型，

将传感器板子的位置往下移，并将MCU主板垫高，优化充电发热时直接接触模型，将热量传给传感器

根据我的观察电池充电发热，如果不需要电池的同学可以不要电池，去掉这部分电路，将电池充电IC短起来，或者调高RB1的阻值，减小充电电流也是没有问题的

个人感觉只有传感器板真正的远离发热源才能测量准确，对精度要求不高的同学其实不比太过纠结，室内各个地方的温度不一样，人体温度都有36度左右的样子，很容易给传感器板传递上热量。

建议有钱的直接用铝合金
