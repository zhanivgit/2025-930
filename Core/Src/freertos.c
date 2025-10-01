/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Led.h"
#include "buzzer.h"
#include "Red_Avoid.h"
#include "Light_Sensor.h"
#include "OLED.h"
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
/* USER CODE BEGIN Variables */
int buzzer_count = 0;
 int led_count = 0;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
osThreadId_t OLED_ShowTaskHandle;
const osThreadAttr_t OLED_ShowTask_attributes = {
  .name = "OLED_ShowTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
void OLED_ShowTask(void *argument);
osThreadId_t Buzzer_TaskHandle;
const osThreadAttr_t buzzerTask_attributes = {
  .name = "buzzerTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
void buzzerTask(void *argument);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  OLED_ShowTaskHandle = osThreadNew(OLED_ShowTask, NULL, &OLED_ShowTask_attributes);
  Buzzer_TaskHandle = osThreadNew(buzzerTask, NULL, &buzzerTask_attributes);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET); // Add this line
  for(;;)
  {  
     led_test(); // 移除 led_test() 调用
      led_count++;
      if(led_count >= 10000) // 假设我们想让计数在10000后重置
      {
          led_count = 0;
      }
    osDelay(1); // 避免空循环占用CPU
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void OLED_ShowTask(void *argument)
{
  /* USER CODE BEGIN OLED_ShowTask */
  /* Infinite loop */
  // int count = 0; // 将 count 变量的声明和初始化移到循环外面
  for(;;)
  {
    OLED_ShowString(1, 1, "Hello, World!");
    OLED_ShowString(2, 1, "Li:");
    OLED_ShowString(3, 1, "Ra:");
    OLED_ShowNum(2, 4, Light_Sensor_dectect(), 1);
    OLED_ShowNum(3, 4, Red_Avoid_dectect(), 1);
    OLED_ShowNum(4, 1, buzzer_count, 4); // 直接显示 buzzer_count 的值
    OLED_ShowNum(4, 10, led_count, 4);
    // count++; // 每次循环递增 count
    osDelay(10); // 添加延时，以便观察计数变化
  }
  /* USER CODE END OLED_ShowTask */
}
void buzzerTask(void *argument)
{
  /* USER CODE BEGIN buzzerTask */
  /* Infinite loop */
  for(;;)
  {
    buzzer_test();
    buzzer_count++; // 每次蜂鸣器测试后递增计数
    led_on(); // 点亮LED
    osDelay(50); // 延时50ms
    led_off(); // 熄灭LED
    osDelay(10000 - 50); // 调整延时，使总周期保持5秒
  }
  /* USER CODE END buzzerTask */
}
/* USER CODE END Application */

