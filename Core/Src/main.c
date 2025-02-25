/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "fatfs.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
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
uint8_t buffer[_MAX_SS]; /* a work buffer for the f_mkfs() */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_SPI1_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */

  FRESULT res;
  uint8_t tx[] = "This is STM32 working with FatFs using SD card as storage medium";
  uint8_t rx[100] = "0";

  UINT cnt;

  res = f_mount(&USERFatFS, (TCHAR const*) USERPath, 0);

  /*only first time*/
  //res = f_mkfs((TCHAR const*) USERPath, FM_ANY, 0, buffer, sizeof(buffer));
  res = f_open(&USERFile, "stm32.txt", FA_CREATE_ALWAYS | FA_WRITE);
  res = f_write(&USERFile, tx, sizeof(tx), &cnt);
  res = f_close(&USERFile);

  res = f_open(&USERFile, "stm32_1.txt", FA_CREATE_ALWAYS | FA_WRITE);
  res = f_write(&USERFile, tx, sizeof(tx), &cnt);
  res = f_close(&USERFile);

  res = f_open(&USERFile, "stm32_2.txt", FA_CREATE_ALWAYS | FA_WRITE);
  res = f_write(&USERFile, tx, sizeof(tx), &cnt);
  res = f_close(&USERFile);

  res = f_open(&USERFile, "stm32_3.txt", FA_CREATE_ALWAYS | FA_WRITE);
  res = f_write(&USERFile, tx, sizeof(tx), &cnt);
  res = f_close(&USERFile);

  res = f_open(&USERFile, "STM32_4.txt", FA_CREATE_ALWAYS | FA_WRITE);
  res = f_write(&USERFile, tx, sizeof(tx), &cnt);
  res = f_close(&USERFile);

  res = f_open(&USERFile, "stm32_5.txt", FA_CREATE_ALWAYS | FA_WRITE);
  res = f_write(&USERFile, tx, sizeof(tx), &cnt);
  res = f_close(&USERFile);

  res = f_open(&USERFile, "stm32_6.txt", FA_CREATE_ALWAYS | FA_WRITE);
  res = f_write(&USERFile, tx, sizeof(tx), &cnt);
  res = f_close(&USERFile);

  res = f_open(&USERFile, "stm32_7.txt", FA_CREATE_ALWAYS | FA_WRITE);
  res = f_write(&USERFile, tx, sizeof(tx), &cnt);
  res = f_close(&USERFile);



  ///////////////////////////////////////////////
  res = f_open(&USERFile, "stm32_2.txt", FA_READ);
  res = f_read(&USERFile, rx, sizeof(rx), &cnt);
  res = f_close(&USERFile);

  FATFS *fs;
  DWORD fre_clust, fre_sect, tot_sect;


  /* Get volume information and free clusters of drive 1 */
  res = f_getfree(USERPath, &fre_clust, &fs);

  /* Get total sectors and free sectors */
  tot_sect = (fs->n_fatent - 2) * fs->csize;
  fre_sect = fre_clust * fs->csize;

  /* Print the free space (assuming 512 bytes/sector) */
  char temp_buffer[100];
  sprintf(temp_buffer, "%10lu KiB total drive space.\n%10lu KiB available.\n", tot_sect / 2, fre_sect / 2);

  (void)res;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
