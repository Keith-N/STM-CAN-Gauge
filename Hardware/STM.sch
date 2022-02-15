EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 6
Title "CAN Gauge F103"
Date "2021-10-10"
Rev "A"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R_US R13
U 1 1 615A83B3
P 9880 5010
F 0 "R13" H 9812 4964 50  0000 R CNN
F 1 "10k" H 9812 5055 50  0000 R CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9920 5000 50  0001 C CNN
F 3 "~" H 9880 5010 50  0001 C CNN
F 4 "" H 9740 5140 50  0000 C CNN "Populate"
	1    9880 5010
	-1   0    0    1   
$EndComp
Wire Wire Line
	8070 5340 8580 5340
Wire Wire Line
	8080 5240 8850 5240
Wire Wire Line
	3970 5690 4250 5690
Wire Wire Line
	3970 5590 4250 5590
Wire Wire Line
	3970 4890 4260 4890
$Comp
L Device:R_US R10
U 1 1 6156EBBB
P 8730 5340
F 0 "R10" V 8617 5340 50  0000 C CNN
F 1 "10k" V 8526 5340 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8770 5330 50  0001 C CNN
F 3 "~" H 8730 5340 50  0001 C CNN
F 4 "" V 8435 5340 50  0000 C CNN "Populate"
	1    8730 5340
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10680 1790 9770 1790
Wire Wire Line
	10680 1590 10680 1790
Wire Wire Line
	10340 1590 10340 1640
Wire Wire Line
	2670 5490 1920 5490
$Comp
L power:+3V3 #PWR0101
U 1 1 61590847
P 10680 1290
F 0 "#PWR0101" H 10680 1140 50  0001 C CNN
F 1 "+3V3" H 10695 1463 50  0000 C CNN
F 2 "" H 10680 1290 50  0001 C CNN
F 3 "" H 10680 1290 50  0001 C CNN
	1    10680 1290
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0102
U 1 1 6157BA01
P 10340 1290
F 0 "#PWR0102" H 10340 1140 50  0001 C CNN
F 1 "+3V3" H 10355 1463 50  0000 C CNN
F 2 "" H 10340 1290 50  0001 C CNN
F 3 "" H 10340 1290 50  0001 C CNN
	1    10340 1290
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R25
U 1 1 614D3D3A
P 10680 1440
F 0 "R25" H 10612 1394 50  0000 R CNN
F 1 "10k" H 10612 1485 50  0000 R CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 10720 1430 50  0001 C CNN
F 3 "~" H 10680 1440 50  0001 C CNN
	1    10680 1440
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R24
U 1 1 614D3D34
P 10340 1440
F 0 "R24" H 10272 1394 50  0000 R CNN
F 1 "10k" H 10272 1485 50  0000 R CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 10380 1430 50  0001 C CNN
F 3 "~" H 10340 1440 50  0001 C CNN
	1    10340 1440
	-1   0    0    1   
$EndComp
Wire Wire Line
	3970 4990 4250 4990
$Comp
L power:GND #PWR0103
U 1 1 61632951
P 10040 5890
F 0 "#PWR0103" H 10040 5640 50  0001 C CNN
F 1 "GND" H 10045 5717 50  0000 C CNN
F 2 "" H 10040 5890 50  0001 C CNN
F 3 "" H 10040 5890 50  0001 C CNN
	1    10040 5890
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 6162A851
P 9810 5880
F 0 "#PWR0104" H 9810 5630 50  0001 C CNN
F 1 "GND" H 9815 5707 50  0000 C CNN
F 2 "" H 9810 5880 50  0001 C CNN
F 3 "" H 9810 5880 50  0001 C CNN
	1    9810 5880
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0105
U 1 1 61621FE5
P 10490 4770
F 0 "#PWR0105" H 10490 4620 50  0001 C CNN
F 1 "+3V3" H 10505 4943 50  0000 C CNN
F 2 "" H 10490 4770 50  0001 C CNN
F 3 "" H 10490 4770 50  0001 C CNN
	1    10490 4770
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0106
U 1 1 6161966B
P 9880 4720
F 0 "#PWR0106" H 9880 4570 50  0001 C CNN
F 1 "+3V3" H 9895 4893 50  0000 C CNN
F 2 "" H 9880 4720 50  0001 C CNN
F 3 "" H 9880 4720 50  0001 C CNN
	1    9880 4720
	1    0    0    -1  
$EndComp
Wire Wire Line
	9880 4860 9880 4720
Wire Wire Line
	10490 4890 10490 4770
Wire Wire Line
	10040 5780 10040 5890
Wire Wire Line
	9810 5780 9810 5880
Wire Wire Line
	10040 5480 10040 5350
Wire Wire Line
	9810 5240 9810 5480
Wire Wire Line
	9810 5240 9880 5240
Connection ~ 9810 5240
Wire Wire Line
	9150 5240 9810 5240
Wire Wire Line
	8880 5340 10040 5340
Wire Wire Line
	10490 5190 10490 5350
Wire Wire Line
	9880 5160 9880 5240
$Comp
L Device:R_US R14
U 1 1 615BEC5E
P 10040 5630
F 0 "R14" H 9972 5584 50  0000 R CNN
F 1 "10k" H 9972 5675 50  0000 R CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 10080 5620 50  0001 C CNN
F 3 "~" H 10040 5630 50  0001 C CNN
F 4 "" H 9900 5760 50  0000 C CNN "Populate"
	1    10040 5630
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R15
U 1 1 615B76D1
P 10490 5040
F 0 "R15" H 10422 4994 50  0000 R CNN
F 1 "10k" H 10422 5085 50  0000 R CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 10530 5030 50  0001 C CNN
F 3 "~" H 10490 5040 50  0001 C CNN
F 4 "" H 10360 5170 50  0000 C CNN "Populate"
	1    10490 5040
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R12
U 1 1 615AFE63
P 9810 5630
F 0 "R12" H 9877 5584 50  0000 L CNN
F 1 "10k" H 9877 5675 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9850 5620 50  0001 C CNN
F 3 "~" H 9810 5630 50  0001 C CNN
F 4 "" H 9950 5760 50  0000 C CNN "Populate"
	1    9810 5630
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R11
U 1 1 615600C1
P 9000 5240
F 0 "R11" V 9295 5240 50  0000 C CNN
F 1 "10k" V 9204 5240 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9040 5230 50  0001 C CNN
F 3 "~" H 9000 5240 50  0001 C CNN
F 4 "" V 9113 5240 50  0000 C CNN "Populate"
	1    9000 5240
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3970 5490 4250 5490
Wire Wire Line
	3970 5390 4250 5390
Wire Wire Line
	3970 5290 4250 5290
Wire Wire Line
	3970 5190 4250 5190
Wire Wire Line
	3970 5090 4250 5090
Wire Wire Line
	3620 3110 3970 3110
Wire Wire Line
	3620 3060 3620 3110
Wire Wire Line
	3270 2760 3620 2760
Connection ~ 3270 2760
Wire Wire Line
	3270 2760 3270 2660
Connection ~ 3620 3110
Wire Wire Line
	970  2230 1520 2230
Wire Wire Line
	970  2130 970  2230
Connection ~ 970  2230
Wire Wire Line
	970  2280 970  2230
Wire Wire Line
	8440 1240 8440 1490
Wire Wire Line
	8440 1490 8940 1490
Wire Wire Line
	8440 1790 8440 1840
Wire Wire Line
	3970 6290 5270 6290
Wire Wire Line
	3970 6190 5270 6190
Wire Wire Line
	1550 4400 1550 4450
$Comp
L power:GND #PWR0109
U 1 1 6131058C
P 1550 4450
F 0 "#PWR0109" H 1550 4200 50  0001 C CNN
F 1 "GND" H 1555 4277 50  0000 C CNN
F 2 "" H 1550 4450 50  0001 C CNN
F 3 "" H 1550 4450 50  0001 C CNN
	1    1550 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 6130DE36
P 1550 4250
F 0 "R1" H 1618 4296 50  0000 L CNN
F 1 "10k" H 1618 4205 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1590 4240 50  0001 C CNN
F 3 "~" H 1550 4250 50  0001 C CNN
	1    1550 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3970 6090 4720 6090
Wire Wire Line
	3970 5990 4720 5990
Wire Wire Line
	2670 3790 2140 3790
$Comp
L power:VDDA #PWR0110
U 1 1 612C834C
P 3970 2710
F 0 "#PWR0110" H 3970 2560 50  0001 C CNN
F 1 "VDDA" H 3985 2883 50  0000 C CNN
F 2 "" H 3970 2710 50  0001 C CNN
F 3 "" H 3970 2710 50  0001 C CNN
	1    3970 2710
	1    0    0    -1  
$EndComp
Wire Wire Line
	3970 2710 3970 3110
$Comp
L power:VDD #PWR0111
U 1 1 612E9EF6
P 970 2130
F 0 "#PWR0111" H 970 1980 50  0001 C CNN
F 1 "VDD" H 985 2303 50  0000 C CNN
F 2 "" H 970 2130 50  0001 C CNN
F 3 "" H 970 2130 50  0001 C CNN
	1    970  2130
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 612CC15A
P 8940 1940
F 0 "#PWR0112" H 8940 1690 50  0001 C CNN
F 1 "GND" H 8945 1767 50  0000 C CNN
F 2 "" H 8940 1940 50  0001 C CNN
F 3 "" H 8940 1940 50  0001 C CNN
	1    8940 1940
	1    0    0    -1  
$EndComp
Wire Wire Line
	8940 1840 8940 1940
Wire Wire Line
	8940 1790 8940 1840
Connection ~ 8940 1840
Wire Wire Line
	8940 1840 8440 1840
$Comp
L Device:C C4
U 1 1 612CA3D1
P 8940 1640
F 0 "C4" H 9055 1686 50  0000 L CNN
F 1 "1u" H 9055 1595 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8978 1490 50  0001 C CNN
F 3 "~" H 8940 1640 50  0001 C CNN
F 4 "C389008" H 8940 1640 50  0001 C CNN "LCSC"
F 5 "X5R ±10% 10V 1uF 0402 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS" H 8940 1640 50  0001 C CNN "Comments"
	1    8940 1640
	1    0    0    -1  
$EndComp
Connection ~ 8440 1490
$Comp
L Device:C C3
U 1 1 612C9F65
P 8440 1640
F 0 "C3" H 8555 1686 50  0000 L CNN
F 1 "0.1u" H 8555 1595 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8478 1490 50  0001 C CNN
F 3 "~" H 8440 1640 50  0001 C CNN
F 4 "C2655418" H 8440 1640 50  0001 C CNN "LCSC"
F 5 "0402 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS" H 8440 1640 50  0001 C CNN "Comments"
	1    8440 1640
	1    0    0    -1  
$EndComp
Wire Wire Line
	3020 2660 3270 2660
Connection ~ 3270 2660
Wire Wire Line
	3270 2660 3270 2560
Wire Wire Line
	3020 2560 3020 2660
$Comp
L power:VDD #PWR0113
U 1 1 612D6606
P 3020 2560
F 0 "#PWR0113" H 3020 2410 50  0001 C CNN
F 1 "VDD" H 3035 2733 50  0000 C CNN
F 2 "" H 3020 2560 50  0001 C CNN
F 3 "" H 3020 2560 50  0001 C CNN
	1    3020 2560
	1    0    0    -1  
$EndComp
Wire Wire Line
	970  2680 1520 2680
Wire Wire Line
	1520 2730 1520 2680
Connection ~ 1520 2680
Wire Wire Line
	1520 2580 1520 2680
Wire Wire Line
	970  2580 970  2680
$Comp
L Device:C C2
U 1 1 612D4B72
P 970 2430
F 0 "C2" H 1085 2476 50  0000 L CNN
F 1 "1u" H 1085 2385 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1008 2280 50  0001 C CNN
F 3 "~" H 970 2430 50  0001 C CNN
F 4 "C389008" H 970 2430 50  0001 C CNN "LCSC"
F 5 "X5R ±10% 10V 1uF 0402 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS" H 970 2430 50  0001 C CNN "Comment"
	1    970  2430
	1    0    0    -1  
$EndComp
Wire Wire Line
	1520 2280 1520 2230
$Comp
L power:GND #PWR0114
U 1 1 612D4205
P 1520 2730
F 0 "#PWR0114" H 1520 2480 50  0001 C CNN
F 1 "GND" H 1525 2557 50  0000 C CNN
F 2 "" H 1520 2730 50  0001 C CNN
F 3 "" H 1520 2730 50  0001 C CNN
	1    1520 2730
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 612CF94B
P 1520 2430
F 0 "C1" H 1635 2476 50  0000 L CNN
F 1 "0.1u" H 1635 2385 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1558 2280 50  0001 C CNN
F 3 "~" H 1520 2430 50  0001 C CNN
F 4 "C2655418" H 1520 2430 50  0001 C CNN "LCSC"
F 5 "0402 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS" H 1520 2430 50  0001 C CNN "Comments"
	1    1520 2430
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0115
U 1 1 612CE5B7
P 3270 2560
F 0 "#PWR0115" H 3270 2410 50  0001 C CNN
F 1 "+3V3" H 3285 2733 50  0000 C CNN
F 2 "" H 3270 2560 50  0001 C CNN
F 3 "" H 3270 2560 50  0001 C CNN
	1    3270 2560
	1    0    0    -1  
$EndComp
Text Notes 10300 950  0    50   ~ 0
I2C pullups\n
$Comp
L power:VDDA #PWR0117
U 1 1 612EADE6
P 8440 1240
F 0 "#PWR0117" H 8440 1090 50  0001 C CNN
F 1 "VDDA" H 8455 1413 50  0000 C CNN
F 2 "" H 8440 1240 50  0001 C CNN
F 3 "" H 8440 1240 50  0001 C CNN
	1    8440 1240
	1    0    0    -1  
$EndComp
Text GLabel 4250 4990 2    50   Input ~ 0
LED2
Text GLabel 4260 4890 2    50   Input ~ 0
LED1
Text GLabel 4250 5090 2    50   Input ~ 0
LED3
Text GLabel 4250 5190 2    50   Input ~ 0
LED4
Text GLabel 4250 5290 2    50   Input ~ 0
LED5
Text GLabel 4250 5390 2    50   Input ~ 0
LED6
Text GLabel 4250 5490 2    50   Input ~ 0
LED7
Text GLabel 4250 5590 2    50   Input ~ 0
LED8
Text GLabel 4250 5690 2    50   Input ~ 0
LED9
Text GLabel 1920 5490 0    50   Input ~ 0
I2C1_SCL
Text GLabel 1920 5590 0    50   Input ~ 0
I2C1_SDA
Wire Wire Line
	2670 5590 1920 5590
Text GLabel 4720 5990 2    50   Input ~ 0
CAN_RX
Text GLabel 4720 6090 2    50   Input ~ 0
CAN_TX
Text GLabel 5270 6190 2    50   Input ~ 0
SWDIO
Text GLabel 5270 6290 2    50   Input ~ 0
SWCLK
Text GLabel 4250 5790 2    50   Input ~ 0
LED10
Text GLabel 1480 3990 0    50   Input ~ 0
BOOT0
Text GLabel 4160 6390 2    50   Input ~ 0
USER_INPUT
Text GLabel 2570 5190 0    50   Input ~ 0
SPARE_1_IN
Text GLabel 2570 5290 0    50   Input ~ 0
SPARE_2_IN
Text GLabel 9750 1640 0    50   Input ~ 0
I2C1_SCL
Text GLabel 9750 1790 0    50   Input ~ 0
I2C1_SDA
Text GLabel 8080 5240 0    50   Input ~ 0
SPARE_1_IN
Text GLabel 8070 5340 0    50   Input ~ 0
SPARE_2_IN
Text GLabel 10490 5340 2    50   Input ~ 0
SPARE_2
Text GLabel 9880 5230 2    50   Input ~ 0
SPARE_1
Wire Wire Line
	10040 5350 10490 5350
Connection ~ 10040 5350
Wire Wire Line
	10040 5350 10040 5340
Text GLabel 2070 3790 0    50   Input ~ 0
NRST
Text Notes 8300 4690 0    50   ~ 0
Spare I/O to board connector\n
$Comp
L Device:L L2
U 1 1 61355A03
P 3620 2910
F 0 "L2" H 3688 2956 50  0000 L CNN
F 1 "30" H 3688 2865 50  0001 L CNN
F 2 "Inductor_SMD:L_0402_1005Metric" V 3660 2900 50  0001 C CNN
F 3 "https://www.murata.com/products/productdata/8796743696414/QNFA9103.pdf" H 3620 2910 50  0001 C CNN
F 4 "" H 3620 2910 50  0001 C CNN "Part Number"
F 5 "Murata Electronics" H 3620 2910 50  0001 C CNN "Manufacturer"
F 6 "C76886" H 3620 2910 50  0001 C CNN "LCSC"
F 7 "600Ω @ 100MHz 1 500mA 340mΩ 0402 Ferrite Beads ROHS" H 3620 2910 50  0001 C CNN "Comments"
	1    3620 2910
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 4890 2670 4890
Wire Wire Line
	2100 4990 2670 4990
Text Label 2190 4890 0    50   ~ 0
CONFIG_1
Text Label 2190 4990 0    50   ~ 0
CONFIG_2
Text Label 2210 1680 0    50   ~ 0
CONFIG_1
Text Label 2240 820  0    50   ~ 0
CONFIG_2
Wire Wire Line
	2240 820  2240 950 
Wire Wire Line
	2210 1680 2210 1910
Wire Wire Line
	2210 2210 2210 2300
Wire Wire Line
	2240 1250 2240 1330
$Comp
L power:GND #PWR0107
U 1 1 616CEB78
P 2240 1330
F 0 "#PWR0107" H 2240 1080 50  0001 C CNN
F 1 "GND" H 2245 1157 50  0000 C CNN
F 2 "" H 2240 1330 50  0001 C CNN
F 3 "" H 2240 1330 50  0001 C CNN
	1    2240 1330
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 616D0EB9
P 2210 2300
F 0 "#PWR0108" H 2210 2050 50  0001 C CNN
F 1 "GND" H 2215 2127 50  0000 C CNN
F 2 "" H 2210 2300 50  0001 C CNN
F 3 "" H 2210 2300 50  0001 C CNN
	1    2210 2300
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP1
U 1 1 61B59AAD
P 9850 1390
F 0 "TP1" H 9908 1508 50  0000 L CNN
F 1 "TestPoint" H 9908 1417 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 10050 1390 50  0001 C CNN
F 3 "~" H 10050 1390 50  0001 C CNN
	1    9850 1390
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP2
U 1 1 61B5F660
P 9850 2160
F 0 "TP2" H 9908 2278 50  0000 L CNN
F 1 "TestPoint" H 9908 2187 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 10050 2160 50  0001 C CNN
F 3 "~" H 10050 2160 50  0001 C CNN
	1    9850 2160
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 1390 9850 1640
Wire Wire Line
	9750 1640 9850 1640
Connection ~ 9850 1640
Wire Wire Line
	9850 1640 10340 1640
Wire Wire Line
	9850 2160 9770 2160
Wire Wire Line
	9770 2160 9770 1790
Connection ~ 9770 1790
Wire Wire Line
	9770 1790 9750 1790
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 61BBD276
P 2210 2060
AR Path="/615E795E/61BBD276" Ref="JP?"  Part="1" 
AR Path="/615E5281/61BBD276" Ref="JP2"  Part="1" 
F 0 "JP2" V 2164 2128 50  0000 L CNN
F 1 "SolderJumper_2_Open" V 2255 2128 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 2210 2060 50  0001 C CNN
F 3 "~" H 2210 2060 50  0001 C CNN
	1    2210 2060
	0    1    1    0   
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 61BBFC2A
P 2240 1100
AR Path="/615E795E/61BBFC2A" Ref="JP?"  Part="1" 
AR Path="/615E5281/61BBFC2A" Ref="JP3"  Part="1" 
AR Path="/615E8210/61BBFC2A" Ref="JP3"  Part="1" 
F 0 "JP3" V 2194 1168 50  0000 L CNN
F 1 "SolderJumper_2_Open" V 2285 1168 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 2240 1100 50  0001 C CNN
F 3 "~" H 2240 1100 50  0001 C CNN
	1    2240 1100
	0    1    1    0   
$EndComp
Wire Wire Line
	3970 5790 4250 5790
Wire Wire Line
	3570 3110 3620 3110
Wire Wire Line
	3270 2760 3270 3410
Wire Wire Line
	3370 3590 3370 3410
Wire Wire Line
	3370 3410 3270 3410
Connection ~ 3270 3410
Wire Wire Line
	3270 3410 3270 3590
Wire Wire Line
	3470 3590 3470 3410
Wire Wire Line
	3470 3410 3370 3410
Connection ~ 3370 3410
Wire Wire Line
	3570 3110 3570 3590
Wire Wire Line
	1480 3990 1550 3990
Wire Wire Line
	1550 3990 1550 4100
Connection ~ 1550 3990
Wire Wire Line
	1550 3990 2670 3990
Wire Wire Line
	3170 6590 3170 6740
Wire Wire Line
	3170 6740 3270 6740
Wire Wire Line
	3270 6590 3270 6740
Connection ~ 3270 6740
Wire Wire Line
	3270 6740 3370 6740
Wire Wire Line
	3370 6590 3370 6740
Connection ~ 3370 6740
Wire Wire Line
	3370 6740 3470 6740
Wire Wire Line
	3470 6590 3470 6740
Wire Wire Line
	3470 6740 3520 6740
$Comp
L power:GND #PWR0164
U 1 1 618EEC65
P 3520 6740
F 0 "#PWR0164" H 3520 6490 50  0001 C CNN
F 1 "GND" H 3525 6567 50  0000 C CNN
F 2 "" H 3520 6740 50  0001 C CNN
F 3 "" H 3520 6740 50  0001 C CNN
	1    3520 6740
	1    0    0    -1  
$EndComp
Connection ~ 3470 6740
Wire Wire Line
	2570 5190 2670 5190
Wire Wire Line
	2570 5290 2670 5290
Wire Wire Line
	4160 6390 3970 6390
Wire Wire Line
	1580 6190 1580 6200
Wire Wire Line
	2670 6290 1680 6290
Wire Wire Line
	2670 6390 1680 6390
Text Label 1700 6190 0    50   ~ 0
CONFIG_3
Text Label 1820 6290 0    50   ~ 0
CONFIG_4
Text Label 1820 6390 0    50   ~ 0
CONFIG_5
Wire Wire Line
	1580 6190 2670 6190
$Comp
L Device:C C6
U 1 1 6203C81B
P 2420 3230
F 0 "C6" H 2535 3276 50  0000 L CNN
F 1 "0.1u" H 2535 3185 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 2458 3080 50  0001 C CNN
F 3 "~" H 2420 3230 50  0001 C CNN
F 4 "C2655418" H 2420 3230 50  0001 C CNN "LCSC"
F 5 "0402 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS" H 2420 3230 50  0001 C CNN "Comments"
	1    2420 3230
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0139
U 1 1 6203F879
P 2420 3460
F 0 "#PWR0139" H 2420 3210 50  0001 C CNN
F 1 "GND" H 2425 3287 50  0000 C CNN
F 2 "" H 2420 3460 50  0001 C CNN
F 3 "" H 2420 3460 50  0001 C CNN
	1    2420 3460
	1    0    0    -1  
$EndComp
Wire Wire Line
	2420 3380 2420 3460
Wire Wire Line
	2140 3790 2140 3070
Wire Wire Line
	2420 3070 2420 3080
Connection ~ 2140 3790
Wire Wire Line
	2140 3790 2070 3790
Text Label 3500 820  0    50   ~ 0
CONFIG_3
Wire Wire Line
	3500 820  3500 950 
Wire Wire Line
	3500 1250 3500 1330
$Comp
L power:GND #PWR0158
U 1 1 620B457B
P 3500 1330
F 0 "#PWR0158" H 3500 1080 50  0001 C CNN
F 1 "GND" H 3505 1157 50  0000 C CNN
F 2 "" H 3500 1330 50  0001 C CNN
F 3 "" H 3500 1330 50  0001 C CNN
	1    3500 1330
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 620B4581
P 3500 1100
AR Path="/615E795E/620B4581" Ref="JP?"  Part="1" 
AR Path="/615E5281/620B4581" Ref="JP4"  Part="1" 
AR Path="/615E8210/620B4581" Ref="JP?"  Part="1" 
F 0 "JP4" V 3454 1168 50  0000 L CNN
F 1 "SolderJumper_2_Open" V 3545 1168 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 3500 1100 50  0001 C CNN
F 3 "~" H 3500 1100 50  0001 C CNN
	1    3500 1100
	0    1    1    0   
$EndComp
Text Label 4610 820  0    50   ~ 0
CONFIG_4
Wire Wire Line
	4610 820  4610 950 
Wire Wire Line
	4610 1250 4610 1330
$Comp
L power:GND #PWR0168
U 1 1 620B7EB6
P 4610 1330
F 0 "#PWR0168" H 4610 1080 50  0001 C CNN
F 1 "GND" H 4615 1157 50  0000 C CNN
F 2 "" H 4610 1330 50  0001 C CNN
F 3 "" H 4610 1330 50  0001 C CNN
	1    4610 1330
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 620B7EBC
P 4610 1100
AR Path="/615E795E/620B7EBC" Ref="JP?"  Part="1" 
AR Path="/615E5281/620B7EBC" Ref="JP5"  Part="1" 
AR Path="/615E8210/620B7EBC" Ref="JP?"  Part="1" 
F 0 "JP5" V 4564 1168 50  0000 L CNN
F 1 "SolderJumper_2_Open" V 4655 1168 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 4610 1100 50  0001 C CNN
F 3 "~" H 4610 1100 50  0001 C CNN
	1    4610 1100
	0    1    1    0   
$EndComp
Text Label 5810 840  0    50   ~ 0
CONFIG_5
Wire Wire Line
	5810 840  5810 970 
Wire Wire Line
	5810 1270 5810 1350
$Comp
L power:GND #PWR0169
U 1 1 620BB988
P 5810 1350
F 0 "#PWR0169" H 5810 1100 50  0001 C CNN
F 1 "GND" H 5815 1177 50  0000 C CNN
F 2 "" H 5810 1350 50  0001 C CNN
F 3 "" H 5810 1350 50  0001 C CNN
	1    5810 1350
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 620BB98E
P 5810 1120
AR Path="/615E795E/620BB98E" Ref="JP?"  Part="1" 
AR Path="/615E5281/620BB98E" Ref="JP6"  Part="1" 
AR Path="/615E8210/620BB98E" Ref="JP?"  Part="1" 
F 0 "JP6" V 5764 1188 50  0000 L CNN
F 1 "SolderJumper_2_Open" V 5855 1188 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 5810 1120 50  0001 C CNN
F 3 "~" H 5810 1120 50  0001 C CNN
	1    5810 1120
	0    1    1    0   
$EndComp
$Comp
L Device:C C12
U 1 1 6211116B
P 1710 3230
F 0 "C12" H 1825 3276 50  0000 L CNN
F 1 "0.1u" H 1825 3185 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1748 3080 50  0001 C CNN
F 3 "~" H 1710 3230 50  0001 C CNN
F 4 "C2655418" H 1710 3230 50  0001 C CNN "LCSC"
F 5 "0402 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS" H 1710 3230 50  0001 C CNN "Comments"
	1    1710 3230
	1    0    0    -1  
$EndComp
Wire Wire Line
	1710 3080 1710 3070
Wire Wire Line
	1710 3070 2140 3070
Connection ~ 2140 3070
Wire Wire Line
	2140 3070 2420 3070
$Comp
L power:GND #PWR0170
U 1 1 62118F19
P 1710 3430
F 0 "#PWR0170" H 1710 3180 50  0001 C CNN
F 1 "GND" H 1715 3257 50  0000 C CNN
F 2 "" H 1710 3430 50  0001 C CNN
F 3 "" H 1710 3430 50  0001 C CNN
	1    1710 3430
	1    0    0    -1  
$EndComp
Wire Wire Line
	1710 3430 1710 3380
$Comp
L MCU_ST_STM32F1:STM32F103C8Tx U1
U 1 1 61EF6A0E
P 3370 5090
F 0 "U1" H 3670 3640 50  0000 C CNN
F 1 "STM32F103C8Tx" H 3920 3560 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 2770 3690 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 3370 5090 50  0001 C CNN
F 4 "C8734 " H 3370 5090 50  0001 C CNN "LCSC"
F 5 "LQFP48 " H 3370 5090 50  0001 C CNN "Package"
	1    3370 5090
	1    0    0    -1  
$EndComp
NoConn ~ 2670 5690
NoConn ~ 2670 5790
NoConn ~ 2670 5890
NoConn ~ 2670 5990
NoConn ~ 2670 6090
NoConn ~ 3970 5890
NoConn ~ 2670 4290
NoConn ~ 2670 4190
NoConn ~ 2670 4490
NoConn ~ 2670 4590
NoConn ~ 2670 4690
NoConn ~ 2670 5390
NoConn ~ 2670 5090
$EndSCHEMATC
