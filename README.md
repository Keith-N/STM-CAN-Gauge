# STM-CAN-Gauge

An STM32F042 based CAN gauge for use with rusEFI ECUs. <br/>
CAN is configured for 500k with a base ID of 512. <br/>
Input voltage tested at 5V and 12V. <br/>

Flash 'CAN Gauge.bin' through STM32CubeProgrammer using STLink and TC2030. <br/>

The only required connections for operation are supply voltage/ground and CAN High/Low. <br/>


![GaugeC_Front](https://user-images.githubusercontent.com/1296009/149627086-46108ad4-7d22-489c-a9e3-0201da568f41.jpg)
![GaugeC_Back](https://user-images.githubusercontent.com/1296009/149627088-e8e37369-0fb0-4910-8a13-caf8e3aafa1a.jpg)

Pinout from the back of connector.
![Pinout](https://user-images.githubusercontent.com/1296009/149626676-be45cae3-4d1d-48f3-84fe-673821d73003.png)


