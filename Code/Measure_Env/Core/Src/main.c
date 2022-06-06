/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "sdio.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "system.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_port_fs.h"
#include "ui.h"
#include "ui_helpers.h"

#include  "DEBUG.h"

#include  "MAX17048.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
FATFS fs;
FIL fil;
	uint32_t total,mfree;                  // file objects
	uint32_t byteswritten;                /* File write counts */
	uint32_t bytesread;                   /* File read counts */
	uint8_t wtext[] = "This is STM32 working with FatFs"; /* File write buffer */
	uint8_t rtext[100];                     /* File read buffers */
	char filename[] = "STM32cube.txt";

u8 exf_getfree(u8 *drv,u32 *total,u32 *free)
{
	FATFS *fs1;
	u8 res;
    u32 fre_clust=0, fre_sect=0, tot_sect=0;
    res =(u32)f_getfree((const TCHAR*)drv, (DWORD*)&fre_clust, &fs1);
    if(res==0)
	{											   
	    tot_sect=(fs1->n_fatent-2)*fs1->csize;	
	    fre_sect=fre_clust*fs1->csize;				   
#if _MAX_SS!=512				  				
		tot_sect*=fs1->ssize/512;
		fre_sect*=fs1->ssize/512;
#endif	  
		*total=tot_sect>>1;	
		*free=fre_sect>>1;	
 	}
	return res;
}	
void Fatfs_RW_test(void)
{
	  Debug("\r\n ****** FatFs Example ******\r\n\r\n");
 
    /*##-1- Register the file system object to the FatFs module ##############*/
		
    retSD = f_mount(&fs, "P", 1);
		
		
		//f_mkdir("0:dxc");
    if(retSD)
    {
        Debug(" mount error : %d \r\n",retSD);
        Error_Handler();
    }
    else
        Debug(" mount sucess!!! \r\n");
     
    /*##-2- Create and Open new text file objects with write access ######*/
		retSD=exf_getfree("0:",&total,&mfree);
		if(retSD==0)
    {
      Debug(" total : %d MB,free : %d MB  \r\n",total>>10,mfree>>10);
      UI_Para.SD_size = total>>10;
    }
			
		else
			 Debug(" getfree error!!! \r\n");
   retSD = f_open(&fil, filename, FA_CREATE_ALWAYS | FA_WRITE);
   if(retSD)
       Debug(" open file error : %d\r\n",retSD);
   else
       Debug(" open file sucess!!! \r\n");
//     
//    /*##-3- Write data to the text files ###############################*/
//    retSD = f_write(&fil, wtext, sizeof(wtext), (void *)&byteswritten);
//    if(retSD)
//        Debug(" write file error : %d\r\n",retSD);
//    else
//    {
//        Debug(" write file sucess!!! \r\n");
//        Debug(" write Data : %s\r\n",wtext);
//    }
//     
//    /*##-4- Close the open text files ################################*/
//    retSD = f_close(&fil);
//    if(retSD)
//        Debug(" close error : %d\r\n",retSD);
//    else
//        Debug(" close sucess!!! \r\n");
//     
//    /*##-5- Open the text files object with read access ##############*/
//    retSD = f_open(&fil, filename, FA_READ);
//    if(retSD)
//        Debug(" open file error : %d\r\n",retSD);
//    else
//        Debug(" open file sucess!!! \r\n");
//     
//    /*##-6- Read data from the text files ##########################*/
//    retSD = f_read(&fil, rtext, sizeof(rtext), (UINT*)&bytesread);
//    if(retSD)
//        Debug(" read error!!! %d\r\n",retSD);
//    else
//    {
//        Debug(" read sucess!!! \r\n");
//        Debug(" read Data : %s\r\n",rtext);
//    }
//     
//    /*##-7- Close the open text files ############################*/
//    retSD = f_close(&fil);
//    if(retSD)  
//        Debug(" close error!!! %d\r\n",retSD);
//    else
//        Debug(" close sucess!!! \r\n");
//     
//    /*##-8- Compare read data with the expected data ############*/
//    if(bytesread == byteswritten)
//    { 
//        Debug(" FatFs is working well!!!\r\n");
//    }
	}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  MX_USART6_UART_Init();
  MX_ADC1_Init();
  MX_TIM5_Init();
  // MX_SDIO_SD_Init();
  // MX_FATFS_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

	// Fatfs_RW_test(); //如果不要SD卡屏蔽SDIO和FATFS初始化
  //关闭背光
  HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_4);

	LCD_Init();//LCD//	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
	lv_init();											//lvgl初始化
  lv_port_fs_init();              //lvgl文件系统初始化
	lv_port_disp_init();						//lvgl显示初始化
	lv_port_indev_init();						//lvgl输入初始化
  ui_init();											//UI

	System_Init();

  //打开背光
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);

  Debug("iENV Measure 初始化完成\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		System_Run();
		lv_task_handler();//LittleVGL
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		

			
		
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
