/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
static void vTaskP0(void *pvParameters);
static void vTaskP1(void *pvParameters);

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
	(void)xTask; (void)pcTaskName;
	__disable_irq();
	__BKPT(0);      /* debugger stops here */
	for (;;) { }
}
/* USER CODE END 4 */

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
  TaskHandle_t xTaskP0 = NULL;
  TaskHandle_t xTaskP1 = NULL;

  BaseType_t xRet_P0;
  BaseType_t xRet_P1;

  xRet_P0 = xTaskCreate(vTaskP0,    /* task function */
                     "P0",          /* name, for debug and vTaskList */
                     128,           /* stack depth in WORDS: 128 x 4 = 512 bytes */
                     NULL,          /* pvParameters */
                     26,            /* priority (configMAX_PRIORITIES is 56 with CMSIS_V2) */
                     &xTaskP0);     /* handle out, or NULL if you do not need it */
  configASSERT(xRet_P0 == pdPASS);

  xRet_P1 = xTaskCreate(vTaskP1,    /* task function */
                     "P1",          /* name, for debug and vTaskList */
                     128,           /* stack depth in WORDS: 128 x 4 = 512 bytes */
                     NULL,          /* pvParameters */
                     25,            /* priority (configMAX_PRIORITIES is 56 with CMSIS_V2) */
                     &xTaskP1);     /* handle out, or NULL if you do not need it */
  configASSERT(xRet_P1 == pdPASS);


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
  printf("rtos-30day: scheduler running\r\n");
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
static void vTaskP0(void *pvParameters)
{
	(void)pvParameters;                 /* not used here */
	for(;;){							/* A task never return */
		HAL_GPIO_TogglePin(P0_GPIO_Port, P0_Pin);

/*		Delay introduced to check the task priorities
 * 		TickType_t xStart = xTaskGetTickCount();
 *
 *		while ((xTaskGetTickCount() - xStart) < pdMS_TO_TICKS(15))
 *		{
 *		         spin: no block, the task stays Running
 *		}
*/

		vTaskDelay(pdMS_TO_TICKS(100)); /* blocked for 100ms */
	}
}

static void vTaskP1(void *pvParameters)
{
	(void)pvParameters;                 /* not used here */
	for(;;){							/* A task never return */
		HAL_GPIO_TogglePin(P1_GPIO_Port, P1_Pin);
		vTaskDelay(pdMS_TO_TICKS(250)); /* blocked for 250ms */
	}
}
/* USER CODE END Application */

