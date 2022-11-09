/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "adc.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "../../MyLibrary/adc.h"
#include "../../MyLibrary/fft.h"
#include "../../MyLibrary/LCD.h"
#include "arm_math.h"
#include "arm_const_structs.h"

//bool flag;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define FFT_LENGTH 1024
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
	uint32_t freq = 0;
	uint16_t freq_flag = 0;
	float32_t ADC_In[FFT_LENGTH];
	float32_t Buff_In[FFT_LENGTH * 2];
	float32_t Buff_Out[FFT_LENGTH];

	uint16_t cnt = 0;
	uint16_t previous_state;
	uint16_t pin_flag;
	uint16_t comparatorFrequency = 0;
	uint16_t comparatorFlag = 0;
	int i = 0;
	int lastValue = 0;
	float32_t frequency = 0;
	uint16_t buttonState = 0;
	uint16_t previousState = 0;



/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
//uint16_t Get_Adc();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
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
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_RTC_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  //HAL_ADCEx_Calibration_Start(&hdac1);
  //HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_Value, FFT_LENGTH);
  //HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim3);
  int timer3Val = __HAL_TIM_GET_COUNTER(&htim3);

  	//LCD initialization
    Lcd_PortType ports[] = { GPIOC, GPIOB, GPIOA, GPIOA };
    Lcd_PinType pins[] = {GPIO_PIN_7, GPIO_PIN_6, GPIO_PIN_9, GPIO_PIN_6};
    Lcd_HandleTypeDef lcd;

    lcd = Lcd_create(ports, pins, GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, LCD_4_BIT_MODE);

    Lcd_cursor(&lcd, 0,1);
    Lcd_string(&lcd, "$$$$$$$$$$$$$$");
      for ( int x = 1; x <= 50 ; x++ )
      {
        Lcd_cursor(&lcd, 1,7);
        Lcd_int(&lcd, x);
        HAL_Delay (100);
      }

      Lcd_clear(&lcd);
      //ChangeUnit(&lcd);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(buttonState == 0){
		  if(buttonState != previousState){
			  Lcd_clear(&lcd);
		  	  previousState = buttonState;
		  }
		  Lcd_cursor(&lcd, 0, 5);
		  Lcd_string(&lcd, "WELCOME!");
	  }

	  //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ comparator code $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	  if(buttonState == 1){
		  if(buttonState != previousState){
			  Lcd_clear(&lcd);
		  	  previousState = buttonState;
		  }
	  	  while(__HAL_TIM_GET_COUNTER(&htim3) - timer3Val < 10000){
			  comparatorFlag = 1;
			  uint16_t current_state;
			  current_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);  //PB8

			  if(current_state != previous_state){
				  pin_flag = 1;
			  }
			  else
				  pin_flag = 0;

			  if(pin_flag == 1){
				  cnt ++;
				  previous_state = current_state;
			  }
			  else
				  previous_state = current_state;
	  	  }

	  	  printf("Comp Freq: %d\r\n", cnt/=2);
		  Lcd_cursor(&lcd, 0, 1);
		  Lcd_int(&lcd, (int)(cnt/=2));

	  	  cnt = 0;
	  	  timer3Val = __HAL_TIM_GET_COUNTER(&htim3);


	  }

	  //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ ADC code $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	  if(buttonState == 2){
		  if(buttonState != previousState){
			  Lcd_clear(&lcd);
			  previousState = buttonState;
		  }
	  	  for(int i = 0; i < FFT_LENGTH; i++){
	  		ADC_In[i] = Get_Adc();
	  	  }

	  	 // if(i == FFT_LENGTH){
	  		  comparatorFlag = 0;
	  		  cnt = 0;
	  		  //Initialize Buff_In
	  		  for (int i = 0; i < FFT_LENGTH; i++)
	  		  {
	  			  Buff_In[i * 2] = ADC_In[i]*3.3/4096;
	  			  Buff_In[i * 2 + 1] = 0;
	  		  }

	  		  //Perform FFT
	  		  arm_cfft_f32(&arm_cfft_sR_f32_len1024, Buff_In, 0, 1);
	  		  arm_cmplx_mag_f32(Buff_In, Buff_Out, FFT_LENGTH);

	  		  //FFT output regulation
	  		  Buff_Out[0] /= 1024;
	  		  for(int i = 0; i < FFT_LENGTH; i++){
	  			  Buff_Out[i] /= 512;
	  		  }

	  		  //Find the maximum magnitude and its index
	  		  uint32_t index = 0;
	  		  for(int i = 1; i < FFT_LENGTH; i++){
	  			 if(Buff_Out[i] > Buff_Out[index]){
	  			   index = i;
	  			 }
	  		  }
	  		  //printf("%.4f %d\r\n", Buff_Out[index], index);

	  		  frequency = index * 250000.0 / FFT_LENGTH / 2.5;

	  		  //Display frequency on LCD
	  		  if(frequency < 3000){
	  			  printf("FFT: %d    ||    ", (int)frequency);
	  			  Lcd_cursor(&lcd, 0, 1);
	  			  Lcd_int(&lcd, (int)frequency);
	  		  }


	  }//	end of FFT if

 }// end of while
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		buttonState++;
		if(buttonState > 2){
			buttonState = 0;
		}
}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim == (&htim2)){
//		if(i == FFT_LENGTH)
//		{
//			lastValue = 0;
//			return;
//		}
//		else
//		{
//			freq = 10000 * (i - lastValue);
//			lastValue = i;
//		}
//	}
//
//	if(htim == (&htim3)){
//		if(comparatorFlag == 1){
//			comparatorFrequency = 5 * cnt;
//			printf("%5\r\n", comparatorFrequency);
//			cnt = 0;
//		}
//	}
//}

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
