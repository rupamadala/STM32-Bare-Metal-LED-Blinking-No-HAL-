/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RCC_BASE				0x40021000
#define RCC_CLK_CTRL_REG		(*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_CLK_CFG_REG			(*(volatile uint32_t *)(RCC_BASE + 0x08))
#define RCC_AHB2ENR_REG 		(*(volatile uint32_t *)(RCC_BASE + 0x4C))


#define GPIOB_BASE 				0x48000400
#define GPIOB_MODE_REG 			(*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_OTYPE_REG 		(*(volatile uint32_t *)(GPIOB_BASE + 0x04))
#define GPIOB_OSPEED_REG 		(*(volatile uint32_t *)(GPIOB_BASE + 0x08))
#define GPIOB_PUPDR_REG 		(*(volatile uint32_t *)(GPIOB_BASE + 0x0C))
#define GPIOB_BSRR_REG 			(*(volatile uint32_t *)(GPIOB_BASE + 0x18))
#define GPIOB_BRR_REG 			(*(volatile uint32_t *)(GPIOB_BASE + 0x28))

#define SYSTCK_BASE 			0xE000E010
#define SYSTCK_CTRL_REG			(*(volatile uint32_t *)(SYSTCK_BASE + 0x00))
#define SYSTCK_LOAD_REG			(*(volatile uint32_t *)(SYSTCK_BASE + 0x04))
#define SYSTCK_VAL_REG			(*(volatile uint32_t *)(SYSTCK_BASE + 0x08))
#define SYSTCK_CALIB_REG		(*(volatile uint32_t *)(SYSTCK_BASE + 0x0C))
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void gpio_init(void);
void clk_config(void);
void systck_init(void);
void delay_ms(uint32_t count);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void gpio_init(void){
	RCC_AHB2ENR_REG |= (1<<1); //Enabling clk for GPIOB
	//Configurations for GPIOB Pin 7

	//Setting Output mode
	GPIOB_MODE_REG &= ~(3<<14);
	GPIOB_MODE_REG |= (1<<14);

	GPIOB_OTYPE_REG &= ~(1<<7); //Setting Output Push Pull

	//Setting Low Speed
	GPIOB_OSPEED_REG &= ~(3<<14);

	//Setting Pull Up
	GPIOB_PUPDR_REG &= ~(3<<14);
	GPIOB_PUPDR_REG |= (1<<14);

	GPIOB_BRR_REG = (1<<7); //Reset GPIO pin
}

void clk_config(void){
	RCC_CLK_CTRL_REG |= (1<<8); //HSION

	//Microcontroller clock output : HSI16 selected
	RCC_CLK_CFG_REG &= ~(0xF000000);
	RCC_CLK_CFG_REG |= (3<<24);
}

void systck_init(void){
	//Sys CLK Freq with HSI = 16MHz, For 1ms delay (16000000/1000) = 16000 clock cycles
	//Sys CLK Freq with MSI = 4MHz, For 1ms delay (4000000/1000) = 4000 clock cycles
	//So reload value = (clock_cycles - 1)
	SYSTCK_LOAD_REG = (16000 -1);
	SYSTCK_VAL_REG = 0x00000000; //Clear current counter value
	SYSTCK_CTRL_REG = 5; //select clock source as Processor clock (AHB) and enable counter

}

void delay_ms(uint32_t ms){
	while(ms--){
		while((SYSTCK_CTRL_REG & (1<<16))== 0); //loop till count flag = 1
	}
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
  //HAL_Init();

  /* USER CODE BEGIN Init */
	systck_init();
  /* USER CODE END Init */

  /* Configure the system clock */
  //SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	clk_config(); // configured clock to HSI clock (Optional: without this line delay_ms() will work but clock needs to be adjusted)
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
  gpio_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	GPIOB_BSRR_REG = (1<<7);
	delay_ms(500);
	GPIOB_BRR_REG = (1<<7);
	delay_ms(500);

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */

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
  //__disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
