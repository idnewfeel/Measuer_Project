# �������

## Ӳ�� ##
* ���أ�STM32F411RE
* ��ʾ��LCD 240*240
* ��ʪ�ȴ�������SHT20(ʢ˼��)
* TVOC��������SGP40(ʢ˼��)ֻ�ܲ��Կ�������ָ������Ϊ����SGP30�ķ���û��ѡ����SGP30
* ������
* ���-�������·
* ����������·
* SD���ӿ�
* typc-C�ӿ�
* ���Ĳ���
----
## ���
* LVGL
* ʱ�������

---

----
# [V0.1]
* ע���Cubemx���ɵĴ��� SD������ ��Ҫ���������޸� 
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
* �ļ�ϵͳ�Ѿ���ֲ�����LVGL������Ե���,����ʾSD���е��ļ���
```
lv_img_set_src(ui_TVOC,"S:/pic/tvoc2.bin");
```
* �����Ҫ��Ļ�����������LCD_Init�Ĵ���
```
	LCD_WR_REG(0x36); 
	LCD_WR_DATA8(0x40); //������ʾ
```
* ���ڿ��Կ�����SD�����ϴ������ݵĹ���