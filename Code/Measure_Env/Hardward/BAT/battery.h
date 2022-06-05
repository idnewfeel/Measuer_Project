#ifndef  _BAT_H_
#define  _BAT_H_

#include "TIM_Management.h"
#include "adc.h"
#include "MAX17048.h"

#define BAT_ADC_UINT16		uint16_t

//采用DMA传输不需要调用
typedef struct Battery_Device
{
	
	BAT_ADC_UINT16	BatAdc[2];
	float						bat_v;
	uint16_t					BAT_MAX_VOL;
	uint16_t					BAT_SOC;
	uint8_t						USB_PWR_Flag;
}BATTERY;
extern BATTERY bat;

void Battery_Start(void);
void Battery_Conversion(void);
#endif

