#ifndef __LCD_INIT_H
#define __LCD_INIT_H

//#include "sys.h"
#include "spi.h"
#include "main.h"

#define delay_ms(x)		HAL_Delay(x)
#define USE_HORIZONTAL 0  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#define LCD_W 240
#define LCD_H 240



//-----------------LCD�˿ڶ���---------------- 


#define LCD_RES_Clr()  HAL_GPIO_WritePin(RES_GPIO_Port,RES_Pin,GPIO_PIN_RESET)
#define LCD_RES_Set() HAL_GPIO_WritePin(RES_GPIO_Port,RES_Pin,GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_RESET)
#define LCD_DC_Set()   HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_SET)
 		     
#define LCD_CS_Clr()   HAL_GPIO_WritePin(OLED_CS_GPIO_Port,OLED_CS_Pin,GPIO_PIN_RESET)
#define LCD_CS_Set()   HAL_GPIO_WritePin(OLED_CS_GPIO_Port,OLED_CS_Pin,GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(BLK_GPIO_Port,BLK_Pin,GPIO_PIN_RESET)
#define LCD_BLK_Set()  HAL_GPIO_WritePin(BLK_GPIO_Port,BLK_Pin,GPIO_PIN_SET)



#define ZK_CS_Clr()			HAL_GPIO_WritePin(ZK_CS_GPIO_Port,ZK_CS_Pin,GPIO_PIN_RESET)
#define ZK_CS_Set()			HAL_GPIO_WritePin(ZK_CS_GPIO_Port,ZK_CS_Pin,GPIO_PIN_SET)




void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




