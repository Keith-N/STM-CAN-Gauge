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

/* USER CODE BEGIN PV */

CAN_RxHeaderTypeDef rxHeader; 			//CAN Bus receive header
uint8_t canRX[8] = {0,0,0,0,0,0,0,0};  	//CAN Bus Receive Buffer
CAN_FilterTypeDef canfilter; 			//CAN Bus Filter


/* Define -------------------------------------------------------------*/
#define startupInfo
#define CANtimeout
#define LEDstartup
#define OLEDstartup
//#define DEBUG


/* Configuration Variables -------------------------------------------------------------*/

//Displays on startup screen
int buildDate = 220409;

// CAN
const int baseCANid = 512;
const int tempOffset = 40;

//Gauges, adjust for total # and desired starting gauge
int currentGauge = 0;
int totalNumGauge = 8;

// Time out for CAN
int canWaitTime = 2000;

// Startup initialization stuff
int startupDelay = 100;
int OLEDreinit = 10;

// User button
int currentMs = 0;
int lastMs = 0;
int btnDebounce = 250;
int btnPress = 0;


/* CAN Data -------------------------------------------------------------*/

// Format for data
// multi     -  Scaling Multiplier
// div  	 - 	Scaling Divider
// max		 -	Maximum value for LEDs
// min		 - 	value for LEDs
// ID		 -  Selects filter ID, adder from base ID
// dec       -  Use decimals? 0 for no


struct rxData{

	float multi, div, max, min;
	int ID;
	int dec;
	float scaled;
	int val;
};


// 0
int warningCount = 0;
int lastError = 0;
int revLimit = 0;
int mainRelay = 0;
int fuelPump = 0;
int CEL = 0;
int egoHeater = 0;

//[Multiplier] [Divider] [max] [min] [ID] [Decimal]

// 1					{multi	div	 	max		min		ID	  dec}
struct rxData rpm = 	{1,		1,		7000,	50,		1,		0};
struct rxData vss = 	{1,		1,		1,		180,	1,		0};
struct rxData mph = 	{62,	100,	1,		180,	1,		0};
struct rxData timing =  {1,		1,		50,		-50,	1,		0};
struct rxData injDuty = {1,		1,		100,	0,		1,		0};

// 2					{multi	div	 	max		min		ID	  dec}
struct rxData accel = 	{1,		1,		100,	0,		2,		0};
struct rxData tps1 = 	{1,		1,		100,	0,		2,		0};
struct rxData tps2 = 	{1,		1,		100,	0,		2,		0};

// 3					{multi	div		max		min		ID		dec
struct rxData map = 	{1,		30,		120,	0,		3, 		1};
struct rxData clt = 	{1,		1,		200,	0,		3,		0};
struct rxData iat = 	{1,		1,		100,	0,		3,		0};
struct rxData auxT1 = 	{1,		1,		250,	0,		3,		0};
struct rxData auxT2 = 	{1,		1,		250,	0,		3,		0};
struct rxData mcuT = 	{1,		1,		250,	0,		3,		0};
struct rxData fuel = 	{1,		1,		100,	0,		3,		0};

// 4					{multi	div		max		min		ID		dec
struct rxData afr = 	{1,		100,	18,		8,		4,		1};
struct rxData oilPress= {1,		10,		100,	0,		4,		0};
struct rxData vvtPos = 	{1,		1,		50,		-50,	4,		0};
struct rxData battery = {1,		1000,	15,		5,		4,		1};

// 5						{multi	div		max		min		ID		Dec
struct rxData cylAirMass =	{1,		1,		100,	0,		5,		0};
struct rxData estAir =		{1,		10,		100,	0,		5,		0};
struct rxData injPW = 		{1,		10,		100,	0,		5,		0};


/* Misc Variables -------------------------------------------------------------*/

// CAN IDs for Filters
const int filterID[] = {(baseCANid), (baseCANid +1), (baseCANid +2), (baseCANid +3), (baseCANid +4), (baseCANid +5)};
int currentFilter = 4;
int rxID;
int msgRXstatus = 0;
char buff[16];
int p;
int lastCanMessage = 0;
int config = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
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

void checkConfig(){

	if (HAL_GPIO_ReadPin(GPIOB, config1_Pin) == 0){
		config++;
	}
	if (HAL_GPIO_ReadPin(GPIOB, config2_Pin) == 0){
		config++;
		config++;

	}
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

void scaleData(struct rxData* data){
	float scaled =  (data->val * (data->multi/data->div));
	data->scaled = scaled;

}

void getData(){


	switch(rxID){

	case 512 :
		// counts or enabled status
		warningCount = byte2Data(1,0);
		lastError = byte2Data(3,2);
		revLimit = (canRX[4]) & 1;
		mainRelay = (canRX[4]) & (1<<1);
		fuelPump = (canRX[4]) & (1<<2);
		CEL = (canRX[4]) & (1<<3);
		egoHeater = (canRX[4]) & (1<<4);
		break;


	case 513 :
		rpm.val = byte2Data(1,0);		//RPM
		timing.val = byte2Data(3,2);	//Timing deg
		injDuty.val = byte2Data(5,4);	//Injector Duty %
		injDuty.val = injDuty.val;
		vss.val = canRX[6];				//Vehicle Speed kph
		mph.val = vss.val;
		break;

	case 514 :
		accel.val = byte2Data(1,0);		//Accelerator Position
		tps1.val = byte2Data(3,2);		//TPS 1 Position
		tps2.val = byte2Data(5,4);		//TPS 1 Position
		break;

	case 515 :
		map.val = byte2Data(1,0);			//MAP kPa
		clt.val = canRX[2] - tempOffset; 	//Coolant Temp C
		iat.val = canRX[3] - tempOffset;	//Intake Temp C
		auxT1.val = canRX[4];				//Aux Temp 1 C
		auxT2.val = canRX[5];				//Aux Temp 2 C
		//mcuT.val = canRX[6];				//MCU Temp C
		fuel.val = canRX[7];				//Fuel Level %
		break;

	case 516 :
		afr.val = byte2Data(1,0);		//AFR
		afr.val = afr.val/10;

		oilPress.val = byte2Data(3,2);	//Oil Pressure kPa

		vvtPos.val = byte2Data(5,4);	//VVT Position deg

		battery.val = byte2Data(7,6);	//Battery mV
		break;

	case 517 :
		cylAirMass.val = byte2Data(1,0);	//Cylinder Air Mass mg

		estAir.val = byte2Data(3,2);		//Estimated Air Flow kg/h

		injPW.val = byte2Data(5,4);			//Injector Pulse Width ms

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
	ssd1306_WriteString(text, Font_16x26, White);

}

void printDataDigitalLarge(struct rxData * data, int X, int Y){

	// Set cursor x/y location and print the selected data
	// If decimal value is 0 it will not be printed
	// This will print the maximum stored value
	ssd1306_SetCursor(X, Y);

	int A = data->scaled;
	int B = (data->scaled - A) * 100;

	if ((data->dec == 0)) {
		snprintf(buff, sizeof(buff), "%d", A);

	}
	else{
		if (B < 10){
			snprintf(buff, sizeof(buff), "%d.0%d", A, B);
		}
		else{
		snprintf(buff, sizeof(buff), "%d.%d", A, B);
		}
	}

	ssd1306_WriteString(buff, Font_16x26, White);

}

void printValue(int data, int X, int Y){
	ssd1306_SetCursor(X, Y);
	snprintf(buff, sizeof(buff), "%d", data);
			ssd1306_WriteString(buff, Font_11x18, White);
}

int getPercent(struct rxData *data){
	// This returns a percentage of the current value vs the set limits for the data

	// Offset current and max values by min, then divide by the max to get the percentage
	int p = ((data->val-(data->min*data->div/data->multi))*100);
	p = p / ((data->max - data->min)*data->div/data->multi);

	// Limit percentage to 0 -> 100
	if (p > 100){
		p = 100;
	}
	if (p < 0){
		p = 0;
	}

	return p;
}

void printStartup(){

#ifdef startupInfo
	ssd1306_Fill(Black);
	printValue(buildDate,5,05);
	printValue(config,100,05);
	printText("CAN 500k",5,25);
	printText("ID 512",5,45);
	ssd1306_UpdateScreen();

#else

	ssd1306_Fill(Black);
	printText("Waiting",5,05);
	ssd1306_UpdateScreen();

#endif

}

void LEDprogress(int l){


	// Set all LED outputs off
				HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin|LED8_Pin|LED9_Pin|LED10_Pin, GPIO_PIN_RESET);


	// Set 1 - 10 LEDs on
	switch(l){

	case 0 :
		 HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin|LED8_Pin|LED9_Pin|LED10_Pin, GPIO_PIN_RESET);
		 break;

	case 1 :
	 	 HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
		 break;

	case 2 :
	 	 HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin, GPIO_PIN_SET);
		 break;

	case 3 :
		HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_SET);
		break;

	case 4 :
		HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin, GPIO_PIN_SET);
		break;

	case 5 :
		HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin, GPIO_PIN_SET);
		break;

	case 6 :
		HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin, GPIO_PIN_SET);
		break;

	case 7 :
		HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin, GPIO_PIN_SET);
		break;

	case 8 :
		HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin|LED8_Pin, GPIO_PIN_SET);
		break;

	case 9 :
	 	 HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin|LED8_Pin|LED9_Pin, GPIO_PIN_SET);
	 	 break;

	case 10 :
		HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin|LED8_Pin|LED9_Pin|LED10_Pin, GPIO_PIN_SET);
	 	break;

	default:
		break;
	}


}

void LEDsingle(int l){

	// Set all LED outputs off
				HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin|LED8_Pin|LED9_Pin|LED10_Pin, GPIO_PIN_RESET);


	// Set single LED 1-10 on
	switch(l){

	case 1:
		 HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
				 break;
	case 2:
		 HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_SET);
				 break;
	case 3:
		 HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_SET);
				 break;
	case 4:
		 HAL_GPIO_WritePin(GPIOA, LED4_Pin, GPIO_PIN_SET);
				 break;
	case 5:
		 HAL_GPIO_WritePin(GPIOA, LED5_Pin, GPIO_PIN_SET);
				 break;
	case 6:
		 HAL_GPIO_WritePin(GPIOA, LED6_Pin, GPIO_PIN_SET);
				 break;
	case 7:
		 HAL_GPIO_WritePin(GPIOA, LED7_Pin, GPIO_PIN_SET);
				 break;
	case 8:
		 HAL_GPIO_WritePin(GPIOA, LED8_Pin, GPIO_PIN_SET);
				 break;
	case 9:
		 HAL_GPIO_WritePin(GPIOA, LED9_Pin, GPIO_PIN_SET);
				 break;
	case 10:
		 HAL_GPIO_WritePin(GPIOA, LED10_Pin, GPIO_PIN_SET);
				 break;
	default:
		HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin|LED8_Pin|LED9_Pin|LED10_Pin, GPIO_PIN_RESET);
		break;

		}
}

void printGauge(char *t, struct rxData *data2){
//
	currentFilter = data2->ID;
	scaleData(data2);
	p = getPercent(data2);
	printText(t,5,2);
	printDataDigitalLarge(data2,5,30);
	ssd1306_UpdateScreen();

	// Set LEDs
	p = p /10;
	if (config == 1 || config == 3){
		LEDsingle(p);
	}
	else {
		LEDprogress(p);
	}
//
}

void updateGauge(int gaugePrint){

	//Setup CAN filter with address for desired data
	//Print specified data to the display



	ssd1306_Fill(Black);
	switch (gaugePrint){

	case 0 : // AFR
		printGauge("AFR",&afr);
		break;

	case 1 : // Intake Temp C
		printGauge("IAT C",&iat);
		break;

	case 2 : // clt C
		printGauge("CLT C",&clt);
		break;

	case 3 : // map kpa
		printGauge("MAP kPa",&map);
		break;

	case 4 : //Battery
		printGauge("Voltage",&battery);
		break;

	case 5 : //RPM
		printGauge("RPM",&rpm);
		break;

	case 6 : //MPH
		printGauge("Speed MPH",&mph);
		break;

	case 7 : //MPH
		printGauge("Speed KPH",&vss);
		break;


	default : // If no gauge is available move to next

		btnPress=1;
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
  HAL_Delay(startupDelay);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */

	// Check config jumpers
	checkConfig();

	// Initialize Display
	for (int OLEDInit = 0; OLEDInit<OLEDreinit ; OLEDInit++){
	ssd1306_Init();
	HAL_Delay(10);
	};

#ifdef OLEDstartup
	// Print startup info on OLED
	printStartup();
#endif

#ifdef LEDstartup
	// Startup test for all LEDs
	int cycle = 0;
	while (cycle  < 11){
	LEDsingle(cycle);
	cycle ++;
	HAL_Delay(50);
	}
	HAL_Delay(100);
	LEDprogress(0);
	HAL_Delay(100);
	LEDprogress(10);
	HAL_Delay(500);
	LEDprogress(0);
#endif


// Setup CAN
canFilterInit(filterID[currentFilter], filterID[currentFilter]);
HAL_CAN_Start(&hcan);
HAL_CAN_ActivateNotification(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	#ifdef CANtimeout
		  // If no CAN messages are received for the specified wait time alert on OLED
		 if (lastCanMessage > 0 && ((HAL_GetTick() - lastCanMessage) > canWaitTime)){
				ssd1306_Fill(Black);
				printText("Lost",5,5);
				printText("Data",5,20);
				printText("Connection",5,35);
				ssd1306_UpdateScreen();
				LEDprogress(999);
		 	 }
	#endif

	// Get data from received CAN message
	 if (msgRXstatus == 1){
		 getData();
		 msgRXstatus = 0;
		 updateGauge(currentGauge);
		 lastCanMessage = HAL_GetTick();
	 }

	 // Cycle gauges if the button was pressed
	 if (btnPress == 1){

		 // Reset button pressed status
		 btnPress = 0;

		 //Advance to next gauge, cycle back to 1st if at last
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
  HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin
                          |LED5_Pin|LED6_Pin|LED7_Pin|LED8_Pin
                          |LED9_Pin|LED10_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin LED4_Pin
                           LED5_Pin LED6_Pin LED7_Pin LED8_Pin
                           LED9_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin
                          |LED5_Pin|LED6_Pin|LED7_Pin|LED8_Pin
                          |LED9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : config1_Pin config2_Pin */
  GPIO_InitStruct.Pin = config1_Pin|config2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LED10_Pin */
  GPIO_InitStruct.Pin = LED10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED10_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : button_Pin */
  GPIO_InitStruct.Pin = button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPARE_1_Pin SPARE_2_Pin */
  GPIO_InitStruct.Pin = SPARE_1_Pin|SPARE_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
