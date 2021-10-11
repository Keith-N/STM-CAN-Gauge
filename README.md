# STM-CAN-Gauge

An STM32F042 based CAN gauge for use with rusEFI ECUs.

CAN configuration:
1. Base ID = 512
1. CAN rate = 500k

Features:
1. Digital display
1. Bar graph
1. Timed Min/Max
1. Push button to cycle gauges
1. Timeout to alert if disconnected from ECU
1. 10 LED outer semi-ring (PCB, needs code)

Hardware for prototype:
1. STM32 Nucleo F042K6
1. CAN Transceiver
1. 1.3" OLED (SH1106, could use others such as ssd1306)
1. Push button

Pin Configuration for prototype:
1. PA12 : CAN_TX
1. PA11 : CAN_RX
1. PA10 : I2C_SDA
1. PA9  : I2C_SCL
1. PB13 : LED
1. PB4  : Button

