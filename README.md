# STM-CAN-Gauge

An STM32F042 based CAN gauge for use with rusEFI ECUs.

Hardware for prototype:
STM32 Nucleo F042K6
CAN Transceiver
1.3" OLED (SH1106, could use others such as ssd1306)
Push button

CAN configuration:
Base ID = 512
CAN rate = 500k

Features:
Simple digital display
Bar graph
Timed Min/Max
Push button to cycle gauges
Timeout to alert if disconnected from CAN
Startup screen showing CAN rate and Base ID, immediatly switches to gauge when data is received.

Pin Configuration :
PA12 : CAN_TX
PA11 : CAN_RX
PA10 : I2C_SDA
PA9  : I2C_SCL
PB13 : LED
PB4  : Button

