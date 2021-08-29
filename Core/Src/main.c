/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include <stdbool.h>
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
CAN_HandleTypeDef hcan;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

CAN_RxHeaderTypeDef rxHeader; 			//CAN Bus recieve header
uint8_t canRX[8] = {0,0,0,0,0,0,0,0};  	//CAN Bus Receive Buffer
CAN_FilterTypeDef canfilter; 			//CAN Bus Filter


// Format for data
// intVal    - 	Integer Value
// decVal    - 	Decimal Value
// scale     -  Inverse of scale, Ex : 0.002 = 200
// decScale  - 	Use to select decimal places, Ex : 10 will remove last digit, 100 -> up to 2 places
// max		 -	Maximum value for graph
// min		 - 	value for graph
// val		 -  Received value


struct rxData{
	int intVal, decVal, scale, decScale, max, min, val;
	int intMax, intMin, decMax, decMin, valMin, valMax;
};

struct minMaxData{
	int  intMax, intMin, decMax, decMin, valMin, valMax;
};

//[int] [dec] [scale] [dec scale] [max] [min] [val]
struct rxData afr = {0,0,1000,100,22,8,0};
struct rxData rpm = {0,0,1,1,7000,50,0};
struct rxData clt = {0,0,1,1,60,250,0};
struct rxData iat = {0,0,1,1,60,250,0};
struct rxData accel = {0,0,100,1,0,100,0};
struct rxData tps1 = {0,0,100,1,0,100,0};
struct rxData tps2 = {0,0,100,1,0,100,0};
struct rxData map = {0,0,300,100,0,100,0};
struct rxData timing = {0,0,200,100,0,50,0};
struct rxData injDuty = {0,0,200,1,0,100,0};
struct rxData battery = {0,0,1000,100,0,16,0};

struct minMaxData storedMinMax = {0 , 0, 0, 0, 0, 0};

// User button
int currentMs = 0;
int lastMs = 0;
int btnDebounce = 250;
int btnPress = 0;

// Gauges, adjust current for starting
int currentGauge = 0;
int totalNumGauge = 4;

//Test data
int b[] = {0,0,0,0,0,0,0};

// CAN IDs for Filters
const int filterID[] = {(512), (513), (514), (515), (516), (517)};
int currentFilter = 4;

int rxID;
int msgRXstatus = 0;
char buff[16];

int pMin = 0xFFFF;
int pMax = 0;
int p;
int vMax;
int vMin;
int lastTimeMax;
int lastTimeMin;
int lastTimeMaxP;
int lastTimeMinP;
int timerMinMax = 3500;

int lastCanMessage = 0;
int canWaitTime = 2000;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan1){
	// Receive CAN message interrupt
	HAL_CAN_GetRxMessage(hcan1, CAN_RX_FIFO0, &rxHeader, canRX);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
	msgRXstatus = 1;
	rxID = rxHeader.StdId;
}

void EXTI4_15_IRQHandler(){
	// Push button interrupt
	currentMs = HAL_GetTick();
	 if ((currentMs - lastMs > btnDebounce))
	  {
	    lastMs = currentMs;
	    btnPress=1;
	  }
	 HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

void canFilterInit(int hiID, int loID){
  	canfilter.FilterBank = 0;
  	canfilter.FilterMode = CAN_FILTERMODE_IDLIST;
  	canfilter.FilterFIFOAssignment = CAN_RX_FIFO0;
  	canfilter.FilterIdHigh = hiID<<5;
  	canfilter.FilterIdLow = loID<<5;
  	canfilter.FilterMaskIdHigh = 0;
  	canfilter.FilterMaskIdLow = 0;
  	canfilter.FilterScale = CAN_FILTERSCALE_32BIT;
  	canfilter.FilterActivation = ENABLE;
  	canfilter.SlaveStartFilterBank = 1;
  	HAL_CAN_ConfigFilter(&hcan,&canfilter);
}

int byte2Data(int b1, int b2){
	// combine two bytes into a single value
	uint32_t sensorVal = (canRX[b1] << 8)|(canRX[b2]);
	return sensorVal;
}

int getIntValue(struct rxData* data){
	 // Get the integer value
	 // Multiply by the inverse of the scale
	 data->intVal = data->val / data->scale;
	 return data->intVal;
}

int getDecValue(struct rxData* data){

	 // Get the decimal value
	 // Subtract the int value from the total
	 // Multiply by the inverse of the scale
	 // Scale and multiply to get number of desired decimal places
	 data->decVal = ((data->val  - (data->intVal*data->scale)) * (data->decScale)/(data->scale));
	 return data->decVal;
}

void getData(){


	switch(rxID){

	case (511):
		// Get test data
		 b[0] = canRX[0];
		 b[1] = canRX[1];
		 b[2] = canRX[2];
		 b[3] = canRX[3];
		 b[4] = canRX[4];
		 b[5] = canRX[5];
		 b[6] = canRX[6];
		 b[7] = canRX[7];

	case 512 :
		break;

	case 513 :
		rpm.val = byte2Data(1,0);		//RPM
		timing.val = byte2Data(3,2);	//Timing deg
		injDuty.val = byte2Data(4,5);	//Injector Duty %
		break;

	case 514 :
		tps1.val = byte2Data(3,2);		//TPS1 %
		break;

	case 515 :
		map.val = byte2Data(1,0);		//MAP kPa
		clt.val = canRX[2];				//Coolant Temp C
		iat.val = canRX[3];				//Intake Temp C
		break;

	case 516 :
		afr.val = byte2Data(1,0);		//AFR
		battery.val = byte2Data(7,6);	//Battery V
		break;

	case 517 :
		break;

	}
}

void printText( char* text, int X, int Y){
	// Set cursor and print 11x18 text
	ssd1306_SetCursor(X, Y);
	ssd1306_WriteString(text, Font_11x18, White);

}

void printTextLarge( char* text, int X, int Y){
	// Set cursor and print 16x26 text
	ssd1306_SetCursor(X, Y);
	ssd1306_WriteString(text, Font_11x18, White);

}

void printTextSmall( char* text, int X, int Y){
	// Set cursor and print 7x10 text
	ssd1306_SetCursor(X, Y);
	ssd1306_WriteString(text, Font_7x10, White);

}

void printDataDigitalLarge(struct rxData * data, int X, int Y){
	// Set cursor x/y location and print the selected data
	// If decimal value is 0 it will not be printed
	// This will print the maximum stored value
	ssd1306_SetCursor(X, Y);
	if (data->decVal > 0){
		snprintf(buff, sizeof(buff), "%d.%d", data->intVal,data->decVal);
		ssd1306_WriteString(buff, Font_16x26, White);
	}

	else {
		snprintf(buff, sizeof(buff), "%d", data->intVal);
		ssd1306_WriteString(buff, Font_16x26, White);
	}

}

void printDataDigital(struct rxData * data, int X, int Y){
	// Set cursor x/y location and print the selected data
	// If decimal value is 0 it will not be printed
	// This will print the maximum stored value
	ssd1306_SetCursor(X, Y);
	if (data->decVal > 0){
		snprintf(buff, sizeof(buff), "%d.%d", data->intVal,data->decVal);
		ssd1306_WriteString(buff, Font_11x18, White);
	}

	else {
		snprintf(buff, sizeof(buff), "%d", data->intVal);
		ssd1306_WriteString(buff, Font_11x18, White);
	}

}

void printDataDigitalSmall(struct rxData * data, int X, int Y){
	// Set cursor x/y location and print the selected data
	// If decimal value is 0 it will not be printed
	// This will print the current stored value
	ssd1306_SetCursor(X, Y);
	if (data->decVal > 0){
		snprintf(buff, sizeof(buff), "%d.%d", data->intVal,data->decVal);
		ssd1306_WriteString(buff, Font_7x10, White);
	}

	else {
		snprintf(buff, sizeof(buff), "%d", data->intVal);
		ssd1306_WriteString(buff, Font_7x10, White);
	}

}

void printDataMin(struct rxData * data, int X, int Y){
	// Set cursor x/y location and print the selected data
	// If decimal value is 0 it will not be printed
	// This will print the minimum stored value
	ssd1306_SetCursor(X, Y);
	if (data->decMin > 0){
		snprintf(buff, sizeof(buff), "%d.%d", data->intMin,data->decMin);
		ssd1306_WriteString(buff, Font_7x10, White);
	}

	else {
		snprintf(buff, sizeof(buff), "%d", data->intMin);
		ssd1306_WriteString(buff, Font_7x10, White);
	}

}

void printDataMax(struct rxData * data, int X, int Y){
	// Set cursor x/y location and print the selected data
	// If decimal value is 0 it will not be printed
	// This will print the maximum stored value
	ssd1306_SetCursor(X, Y);
	if (data->decMax > 0){
		snprintf(buff, sizeof(buff), "%d.%d", data->intMax,data->decMax);
		ssd1306_WriteString(buff, Font_7x10, White);
	}

	else {
		snprintf(buff, sizeof(buff), "%d", data->intMax);
		ssd1306_WriteString(buff, Font_7x10, White);
	}

}

void printValueSmall(int data, int X, int Y){
	ssd1306_SetCursor(X, Y);
	snprintf(buff, sizeof(buff), "%d", data);
			ssd1306_WriteString(buff, Font_7x10, White);
}

void printBarGraph(int X, int Y, int height, int width, int progress, int boarder){

	// Draw bar graph
	// setup location, provide a progress percent 0 -> 100, and a boarder spacing for the fill

	ssd1306_SetCursor(X,Y);

	//Draw boarder
	// Top
	for (int x = X; x<(X + width); x++){
		int y = Y;
		ssd1306_DrawPixel(x,y,White);
	}
	// Bottom
	for (int x =X; x<(X + width); x++){
		int y = Y + height;
		ssd1306_DrawPixel(x,y,White);
	}
	// Left
	for (int y = Y; y< (Y + height); y++){
		int x = X;
		ssd1306_DrawPixel(x,y,White);
	}
	// Right
	for (int y = Y; y<(Y + height); y++){
		int x = X + width;
		ssd1306_DrawPixel(x,y,White);
	}

	// Draw Fill
	for (int y = (Y+boarder); y<((Y + height)-boarder); y++){
		for (int x = (X+boarder) ; x< (((X + width)-boarder)*progress/100); x++){
			ssd1306_DrawPixel(x,y,White);
		}
	}
}

void printBarMinMax(int X, int Y, int height, int width, int min, int max){

	// Setup x location to draw max marker then draw a vertical line
	// width should be the same as the bar graph, but height can vary to extend beyond the bar graph boarder
	int x = (X+width)*max/100;
	for (int y = (Y- height); y< (Y + height); y++){
		ssd1306_DrawPixel(x,y,White);
	}

	// Setup x location to draw min marker then draw a vertical line
	x = (X+width)*min/100;
	for  (int y = (Y-height); y< (Y + height); y++){
			ssd1306_DrawPixel(x,y,White);
		}
}

int getPercent(struct rxData *data){
	// This returns a percentage of the current value vs the set limits for the data

	// Offset current and max values by min, then divide by the max to get the percentage
	int p = ((data->val-(data->min*data->scale))*100);
	p = p / ((data->max - data->min)*data->scale);

	// Limit percentage to 0 -> 100
	if (p > 100){
		p = 100;
	}
	if (p < 0){
		p = 0;
	}

	return p;
}

void getMinMax(struct rxData *data){
	// This stores the current minimum value and updates if necessary

	// Using the set time interval, set the current min/max so that the current value is the new min/max
	int currentTime = HAL_GetTick();
	 if (((currentTime - lastTimeMin) > timerMinMax)){
		lastTimeMin = currentTime;
		data->valMin = 0xFFFF;
		data->valMax = 0;
	}

	 // Update min/max if current value is exceeded
	if (data->val < data->valMin){
		data->valMin = data->val;
		data->intMin = data->val / data->scale;
		data->decMin = ((data->val  - (data->intVal*data->scale)) * (data->decScale)/(data->scale));
	}

	// Update min/max if current value is exceeded
	if (data->val > data->valMax){
		data->valMax = data->val;
		data->intMax = data->val / data->scale;
		data->decMax = ((data->val  - (data->intVal*data->scale)) * (data->decScale)/(data->scale));
	}
}

void printStartup(){

	ssd1306_Fill(Black);
	printText("CAN 500k",5,05);
	printText("Base ID 512 ",5,25);
	printText("Waiting ...",5,45);
	ssd1306_UpdateScreen();

}


void getPercentMinMax(int p, int *min, int *max){
	// This stores the current minimum percent value and updates if necessary

	// Using the set time interval, set the current min/max so that the current value is the new min/max
	int currentTime = HAL_GetTick();
	if (((currentTime - lastTimeMinP) > timerMinMax)){
		 lastTimeMinP = currentTime;
		 *min = 999;
		 *max = 0;
	}
	// Update min/max if current value is exceeded
	if (p < *min){
		*min = p;
	}
	if (p > *max){
		*max = p;
		}

}




void updateGauge(int gaugePrint){

	//Setup CAN filter with address for desired data
	//Print specified data to the display

	ssd1306_Fill(Black);
	switch (gaugePrint){

	case 0 : // Basic AFR
		currentFilter = 4;
		getIntValue(&afr);
		getDecValue(&afr);
		printText("AFR",5,2);
		printDataDigitalLarge(&afr,5,30);
		ssd1306_UpdateScreen();
		break;

	case 1 : // AFR with bar graph and min/max
		currentFilter = 4;
		getIntValue(&afr);
		getDecValue(&afr);
		getMinMax(&afr);
		p = getPercent(&afr);
		getPercentMinMax(p,&pMin,&pMax);
		printBarGraph(5,0,10,120,p,2);
		printBarMinMax(5,0,20,120,pMin,pMax);
		printTextSmall("AFR",2,45);
		printDataMin(&afr,2,25);
		printDataMax(&afr,2,35);

		printDataDigitalLarge(&afr,40,30);
		ssd1306_UpdateScreen();
		break;


	case 2 : // Basic RPM
		currentFilter = 1;
		getIntValue(&rpm);
		getDecValue(&rpm);
		printText("RPM",5,2);
		printDataDigitalLarge(&rpm,5,30);
		ssd1306_UpdateScreen();
		break;

	case 3 :
		currentFilter = 1;
		getIntValue(&rpm);
		getDecValue(&rpm);
		getMinMax(&rpm);
		p = getPercent(&rpm);
		getPercentMinMax(p,&pMin,&pMax);

		printBarGraph(5,0,10,120,p,2);
		printBarMinMax(5,0,20,120,pMin,pMax);
		printTextSmall("RPM",2,45);
		printDataMin(&rpm,2,25);
		printDataMax(&rpm,2,35);
		printDataDigitalLarge(&rpm,40,30);
		ssd1306_UpdateScreen();
		break;



	default : // If no gauge is available print something
		ssd1306_SetCursor(5, 30);
		ssd1306_WriteString("No Data", Font_11x18, White);
		ssd1306_SetCursor(5, 0);
		snprintf(buff, sizeof(buff), "%d", currentGauge);
		ssd1306_WriteString(buff, Font_11x18, White);
		ssd1306_UpdateScreen();
		break;


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
  MX_I2C1_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */

	// Setup CAN
	canFilterInit(filterID[currentFilter], filterID[currentFilter]);
	HAL_CAN_Start(&hcan);
	HAL_CAN_ActivateNotification(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING);

	// Initialize Display and clear
	ssd1306_Init();
	printStartup();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	// Print current gauge to display

	 if (lastCanMessage > 0 && ((HAL_GetTick() - lastCanMessage) > canWaitTime)){
		 	ssd1306_Fill(Black);
		 	printTextLarge("Lost CAN",5,5);
		 	printTextLarge("Connection",5,20);
		 	printTextLarge("!!!!!!!",20,40);
		 	ssd1306_UpdateScreen();
	 }

	// Get data from received CAN message
	 if (msgRXstatus == 1){
		 getData();
		 msgRXstatus = 0;
		 updateGauge(currentGauge);
		 lastCanMessage = HAL_GetTick();
	 }

	 // Cycle gauges if the button was pressed
	 if (btnPress == 1){

		 btnPress = 0;
		 // Reset min/max on gauge change
		 lastTimeMax=0;
		 lastTimeMin=0;
		 lastTimeMaxP=0;
		 lastTimeMinP=0;

		 currentGauge++;
		 if (currentGauge > totalNumGauge){
			 currentGauge = 0;
		 }
		 updateGauge(currentGauge);
		 canFilterInit(filterID[currentFilter], filterID[currentFilter]);
	 }

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN;
  hcan.Init.Prescaler = 2;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_3TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_4TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x0000020B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : button_Pin */
  GPIO_InitStruct.Pin = button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(button_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
