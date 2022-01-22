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

//#define startupInfo
#define CANtimeout
//#define DEBUG
#define LEDstartup


// Format for data
// intVal    - 	Integer Value
// decVal    - 	Decimal Value
// MultA     -  Multiplier for integer of scale, eg. use 3 for 0.03
// MultB  	 - 	Multiplier for decimal places of scale, eg. use 100 for 0.01
// max		 -	Maximum value for graph/LEDs
// min		 - 	value for graph/LEDs
// val		 -  Received value


struct rxData{
	int intVal;
	int decVal, multA, multB, max, min, val;
	int intMax, intMin, decMax, decMin, valMin, valMax;
};



struct minMaxData{
	int  intMax, intMin, decMax, decMin, valMin, valMax;
};

//[int] [dec] [MultiplierA] [MultiplierB] [max] [min] [val]

// 0
int warningCount = 0;
int lastError = 0;
int revLimit = 0;
int mainRelay = 0;
int fuelPump = 0;
int CEL = 0;
int egoHeater = 0;
int stoich = 14.7;

// 1					{int	dec		A		B	 	max		min		val
struct rxData rpm = 	{0,		0,		1,		1,		7000,	50,		0};
struct rxData timing = 	{0,		0,	 	1,		1,		50,		-50,	0};
struct rxData injDuty = {0,		0,		1,		1,		100,	0,		0};
struct rxData vss = 	{0,		0,		1,		1,		1,		300,	0};

// 2					{int	dec		A		B		max		min		val
struct rxData accel = 	{0,		0,		1,		1,		100,	0,		0};
struct rxData tps1 = 	{0,		0,		1,		1,		100,	0,		0};
struct rxData tps2 = 	{0,		0,		1,		1,		100,	1,		0};

// 3					{int	dec		A		B		max		min		val
struct rxData map = 	{0,		0,		3,		100,	120,	0,		0};
struct rxData mapPSI = 	{0,		0,	 	3,		100,	30,		0,		0};
struct rxData clt = 	{0,		0,		1,		1,		200,	0,		0};
struct rxData cltF = 	{0,		0,		1,		1,		300,	0,		0};
struct rxData iat = 	{0,		0,		1,		1,		100,	0,		0};
struct rxData iatF = 	{0,		0,		1,		1,		200,	0,		0};
struct rxData auxT1 = 	{0,		0,		1,		1,		250,	0,		0};
struct rxData auxT2 = 	{0,		0,		1,		1,		250,	0,		0};
struct rxData mcuT = 	{0,		0,		1,		1,		250,	0,		0};
struct rxData fuel = 	{0,		0,		1,		1,		100,	0,		0};

// 4					{int	dec		A		B		max		min		val
struct rxData afr = 	{0,		0,		1,		100,	18,		8,		0};
struct rxData afrl = 	{0,		0,		1,		100,	2,		0,		0};
struct rxData oilPress= {0,		0,	  	1,		10,		100,	0,		0};
struct rxData vvtPos = 	{0,		0,		1,		1,		50,		-50,	0};
struct rxData battery = {0,		0,		1,		1000,		0,		16,		0};

// 5						{int	dec		A		B		max		min		val
struct rxData cylAirMass =	{0,		0,		1,		1,		100,	0,		0};
struct rxData estAir =		{0,		0,		1,		10,		100,	0,		0};
struct rxData injPW = 		{0,		0,	 	1,		10,		100,	0,		0};

struct minMaxData storedMinMax = {0, 0, 0, 0, 0, 0};

// User button
int currentMs = 0;
int lastMs = 0;
int btnDebounce = 250;
int btnPress = 0;

// Gauges, adjust current for starting
int currentGauge = 0;
int totalNumGauge = 8;

//Test data
#ifdef DEBUG
int b[] = {0,0,0,0,0,0,0};
#endif

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

int idleLED = 0;
int config = 0;
int LEDconfig = 0;


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
		LEDconfig = 1;
	}
	if (HAL_GPIO_ReadPin(GPIOB, config2_Pin) == 0){
		config = 1;

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

int getIntValue(struct rxData* data){
	 // Get the integer value
	 // Scale Value
	 data->intVal = data->val * data->multA/data->multB;
	 return data->intVal;
}


int getDecValue(struct rxData* data){

	 // Get the decimal value
	 // Subtract the int value from the total
	 // Multiply by the inverse of the scale
	 // Scale and multiply to get number of desired decimal places
	 data->decVal = (data->val  - (data->intVal*data->multB));
	 return data->decVal;
}

int C2F ( int c){
	int f = ((c * 9)/5)+32;
	return f;
}

int kpa2psi (int kpa){

	int psi = ((kpa * 1450)/10000);
	return psi;
}

void getData(){


	switch(rxID){

#ifdef DEBUG
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
#endif

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
		break;

	case 514 :
		accel.val = byte2Data(1,0);		//Accelerator Position
		tps1.val = byte2Data(3,2);		//TPS 1 Position
		tps2.val = byte2Data(5,4);		//TPS 1 Position
		break;

	case 515 :
		map.val = byte2Data(1,0);		//MAP kPa
		map.val = (map.val/.3);

		clt.val = canRX[2];				//Coolant Temp C
		iat.val = canRX[3];				//Intake Temp C
		auxT1.val = canRX[4];			//Aux Temp 1 C
		auxT2.val = canRX[5];			//Aux Temp 2 C
		mcuT.val = canRX[6];			//MCU Temp C
		fuel.val = canRX[7];			//Fuel Level %
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

void printValue(int data, int X, int Y){
	ssd1306_SetCursor(X, Y);
	snprintf(buff, sizeof(buff), "%d", data);
			ssd1306_WriteString(buff, Font_11x18, White);
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
	int p = ((data->val-(data->min*data->multB/data->multA))*100);
	p = p / ((data->max - data->min)*data->multB/data->multA);

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
		data->intMin = data->val * data->multA/data->multB;
		data->decMin = ((data->val  - (data->intVal*data->multB/data->multA)) * data->multB/data->multA);
	}

	// Update min/max if current value is exceeded
	if (data->val > data->valMax){
		data->valMax = data->val;
		data->intMin = data->val * data->multA/data->multB;
		data->decMin = ((data->val  - (data->intVal*data->multB/data->multA)) * data->multB/data->multA);
	}
}


void printStartup(){

//#ifdef startupInfo
	if (config == 0){
	ssd1306_Fill(Black);
	printText("CAN 500k",5,05);
	printText("Base ID 512 ",5,25);
	printText("Config ",5,45);
	printValue(config, 80, 45);
	printValue(LEDconfig, 95, 45);
	ssd1306_UpdateScreen();
	}
//#else
	else{
	ssd1306_Fill(Black);
	printText("Waiting",5,05);
	ssd1306_UpdateScreen();

//#endif

}
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
		break;

		}
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


void printGauge(char *t, struct rxData *data2){
//
	getIntValue(data2);
	getDecValue(data2);
	p = getPercent(data2);
//
//	// Print Text Only
//	if (config==0){
	printText(t,5,2);
	printDataDigitalLarge(data2,5,30);
	ssd1306_UpdateScreen();
//	}
//
//	// Print Text and Bar
//	else{
//	getPercentMinMax(p,&pMin,&pMax);
//	printBarGraph(5,0,10,120,p,2);
//	printBarMinMax(5,0,20,120,pMin,pMax);
//	printTextSmall(t,2,45);
//	printDataMin(data2,2,25);
//	printDataMax(&afr,2,35);
//	printDataDigitalLarge(data2,40,30);
//	ssd1306_UpdateScreen();
//	}
//
	p = p /10;
	// Set LEDs
	if (LEDconfig == 1){
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
		currentFilter = 4;
		printGauge("AFR",&afr);
		break;


	case 2 : // Intake Temp C
		currentFilter = 3;
		printGauge("IAT C",&iat);
		break;


	case 4 : // clt C
		currentFilter = 3;
		printGauge("CLT C",&clt);
		break;


	case 6 : // map kpa
		currentFilter = 3;
		printGauge("MAP kPa",&map);
		break;


	case 8 : //RPM
		currentFilter = 1;
		printGauge("RPM",&rpm);
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

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */

	// Setup CAN
	canFilterInit(filterID[currentFilter], filterID[currentFilter]);
	HAL_CAN_Start(&hcan);
	HAL_CAN_ActivateNotification(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING);

	// Initialize Display and clear
	ssd1306_Init();
	checkConfig();
	printStartup();

#ifdef LEDstartup
	int cycle = 0;
	while (cycle  < 10){
	LEDsingle(cycle);
	cycle ++;
	HAL_Delay(50);
	}
	HAL_Delay(100);
	LEDprogress(0);
	HAL_Delay(100);
	LEDprogress(9);
	HAL_Delay(500);
	LEDprogress(0);
#endif

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	// Print current gauge to display

#ifdef CANtimeout
	 if (lastCanMessage > 0 && ((HAL_GetTick() - lastCanMessage) > canWaitTime)){
		 	ssd1306_Fill(Black);
		 	printTextLarge("Lost",5,5);
		 	printTextLarge("Data",5,20);
		 	printTextLarge("Connection",5,35);
		 	ssd1306_UpdateScreen();
		 	LEDsingle(999);
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
