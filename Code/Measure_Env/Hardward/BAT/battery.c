#include "battery.h" 

BATTERY bat;

void Battery_Start(void)
{
	
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)bat.BatAdc,2);//------启动ADC连续转换，DMA传输
}




void Battery_Conversion(void)
{
	float temp;

	// temp = bat.BatAdc[0];		//ADC通道2
	// bat.bat_i = (float)((temp/4096)*33/10);	

	temp = bat.BatAdc[1];		//现在的板子飞线是ADC通道3
	bat.bat_v = (float)((temp/4096)*33*2/10);

	bat.BAT_SOC = max17048.bat_soc;
	bat.BAT_MAX_VOL = max17048.bat_vol;

	if(HAL_GPIO_ReadPin(USB_PWR_GPIO_Port,USB_PWR_Pin)==GPIO_PIN_SET)//USB电源插入
	{
		bat.USB_PWR_Flag=1;
	}
	else 
	{
		bat.USB_PWR_Flag=0;
	}
	
}

