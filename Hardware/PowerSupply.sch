EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 6
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
L power:+3.3V #PWR0118
U 1 1 612F83E8
P 9460 3790
F 0 "#PWR0118" H 9460 3640 50  0001 C CNN
F 1 "+3.3V" H 9475 3963 50  0000 C CNN
F 2 "" H 9460 3790 50  0001 C CNN
F 3 "" H 9460 3790 50  0001 C CNN
	1    9460 3790
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R9
U 1 1 614FE23B
P 9460 4180
F 0 "R9" H 9528 4226 50  0000 L CNN
F 1 "1k" H 9528 4135 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9500 4170 50  0001 C CNN
F 3 "~" H 9460 4180 50  0001 C CNN
F 4 "C11702" H 9460 4180 50  0001 C CNN "LCSC"
F 5 "±1% 1/16W ±100ppm/℃ 1kΩ 0402 Chip Resistor - Surface Mount ROHS" H 9460 4180 50  0001 C CNN "Comments"
	1    9460 4180
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0138
U 1 1 614FE242
P 9460 4800
F 0 "#PWR0138" H 9460 4550 50  0001 C CNN
F 1 "GND" H 9465 4627 50  0000 C CNN
F 2 "" H 9460 4800 50  0001 C CNN
F 3 "" H 9460 4800 50  0001 C CNN
	1    9460 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D10
U 1 1 614FE24A
P 9460 4570
F 0 "D10" V 9499 4452 50  0000 R CNN
F 1 "LED" V 9408 4452 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 9460 4570 50  0001 C CNN
F 3 "~" H 9460 4570 50  0001 C CNN
F 4 "C2286" V 9460 4570 50  0001 C CNN "LCSC"
F 5 "Red 615~630nm 1.9~2.2V 0603 Light Emitting Diodes (LED) RoHS" V 9460 4570 50  0001 C CNN "Comments"
	1    9460 4570
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9460 4800 9460 4720
Wire Wire Line
	9460 4420 9460 4330
Wire Wire Line
	4480 1740 4480 1870
$Comp
L Device:D_Schottky D21
U 1 1 61545FD1
P 3920 1870
F 0 "D21" H 3920 1653 50  0000 C CNN
F 1 "SS16HE3_B/I" H 3920 1744 50  0000 C CNN
F 2 "Diode_SMD:D_SMA" H 3920 1870 50  0001 C CNN
F 3 "https://www.vishay.com/docs/88746/ss12.pdf" H 3920 1870 50  0001 C CNN
F 4 "Vishay" H 3920 1870 50  0001 C CNN "Manufacturer"
F 5 "SS16HE3_B/I" H 3920 1870 50  0001 C CNN "Part Number"
F 6 " C211772 " H 3920 1870 50  0001 C CNN "LCSC"
F 7 "60V 1A 700mV @ 1A SMA Schottky Barrier Diodes (SBD) ROHS" H 3920 1870 50  0001 C CNN "Comment"
	1    3920 1870
	-1   0    0    1   
$EndComp
Wire Wire Line
	3390 2220 3390 2320
$Comp
L power:GND #PWR0129
U 1 1 616169BD
P 3390 2320
F 0 "#PWR0129" H 3390 2070 50  0001 C CNN
F 1 "GND" H 3395 2147 50  0000 C CNN
F 2 "" H 3390 2320 50  0001 C CNN
F 3 "" H 3390 2320 50  0001 C CNN
	1    3390 2320
	1    0    0    -1  
$EndComp
Wire Wire Line
	3390 1870 3770 1870
Connection ~ 3390 1870
Wire Wire Line
	3390 1870 3390 1920
$Comp
L Device:C C9
U 1 1 615FB884
P 3390 2070
F 0 "C9" H 3505 2116 50  0000 L CNN
F 1 "10u" H 3505 2025 50  0000 L CNN
F 2 "Inductor_SMD:L_1206_3216Metric" H 3428 1920 50  0001 C CNN
F 3 "www.samsungsem.com/kr/support/product-search/mlcc/CL31A106MBHNNNE.jsp" H 3390 2070 50  0001 C CNN
F 4 "50V" H 3580 1930 50  0000 C CNN "Voltage"
F 5 "CL31A106MBHNNNE" H 3390 2070 50  0001 C CNN "Part Number"
F 6 "Samsung Electro-Mechanics" H 3390 2070 50  0001 C CNN "Manufactuer"
F 7 " C13585 " H 3390 2070 50  0001 C CNN "LCSC"
F 8 "X5R ±10% 50V 10uF 1206 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS" H 3390 2070 50  0001 C CNN "Comment"
	1    3390 2070
	1    0    0    -1  
$EndComp
Wire Wire Line
	2930 1870 3390 1870
Wire Wire Line
	2930 1870 2670 1870
Connection ~ 2930 1870
Wire Wire Line
	2930 1910 2930 1870
Wire Wire Line
	2930 2320 2930 2210
$Comp
L Device:D_TVS D22
U 1 1 615E88FE
P 2930 2060
F 0 "D22" V 2810 1800 50  0000 L CNN
F 1 "SMBJ16CD-M3/H" V 2940 1290 50  0001 L CNN
F 2 "Diode_SMD:D_SMB" H 2930 2060 50  0001 C CNN
F 3 "https://www.vishay.com/docs/87606/smbj5cdthrusmbj120cd.pdf" H 2930 2060 50  0001 C CNN
F 4 "Vishay" V 2930 2060 50  0001 C CNN "Manufacturer"
F 5 "SMBJ16CD-M3/H" V 2930 2060 50  0001 C CNN "Part Number"
F 6 "18.1V" V 3070 1740 50  0001 L CNN "Breakdown Min"
F 7 "16V" V 3150 1810 50  0001 L CNN "Stand-Off"
F 8 "C8830 " V 2910 1860 50  0001 C CNN "LCSC"
F 9 "Bidirectional 23.1A 26V 17.8V 16V SMB(DO-214AA) TVS" V 2930 2060 50  0001 C CNN "Comment"
	1    2930 2060
	0    1    1    0   
$EndComp
Text GLabel 2670 1870 0    50   Input ~ 0
12V_IN
$Comp
L power:+12V #PWR0119
U 1 1 615DF50E
P 4480 1740
F 0 "#PWR0119" H 4480 1590 50  0001 C CNN
F 1 "+12V" H 4495 1913 50  0000 C CNN
F 2 "" H 4480 1740 50  0001 C CNN
F 3 "" H 4480 1740 50  0001 C CNN
	1    4480 1740
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 612FB0D6
P 2930 2320
F 0 "#PWR0120" H 2930 2070 50  0001 C CNN
F 1 "GND" H 2935 2147 50  0000 C CNN
F 2 "" H 2930 2320 50  0001 C CNN
F 3 "" H 2930 2320 50  0001 C CNN
	1    2930 2320
	1    0    0    -1  
$EndComp
Wire Wire Line
	9460 3790 9460 4030
Text Notes 2840 1730 0    50   ~ 0
12V+ Voltage Source\nInput\n
Text Notes 9260 3410 0    50   ~ 0
Supply indicator
Wire Wire Line
	4070 1870 4480 1870
$Comp
L power:+12V #PWR0116
U 1 1 618B502C
P 5110 2080
F 0 "#PWR0116" H 5110 1930 50  0001 C CNN
F 1 "+12V" H 5125 2253 50  0000 C CNN
F 2 "" H 5110 2080 50  0001 C CNN
F 3 "" H 5110 2080 50  0001 C CNN
	1    5110 2080
	1    0    0    -1  
$EndComp
Wire Wire Line
	5110 2140 5110 2080
$Comp
L Device:C C10
U 1 1 618C9F5C
P 5110 2290
F 0 "C10" H 5225 2336 50  0000 L CNN
F 1 "10u" H 5225 2245 50  0000 L CNN
F 2 "Inductor_SMD:L_1206_3216Metric" H 5148 2140 50  0001 C CNN
F 3 "" H 5110 2290 50  0001 C CNN
F 4 "50v" H 5300 2150 50  0000 C CNN "Voltage"
F 5 "" H 5110 2290 50  0001 C CNN "Part Number"
F 6 "" H 5110 2290 50  0001 C CNN "Manufactuer"
F 7 "" H 5110 2290 50  0001 C CNN "LCSC"
F 8 "X5R ±10% 50V 10uF 1206 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS" H 5110 2290 50  0001 C CNN "Comment"
	1    5110 2290
	1    0    0    -1  
$EndComp
Connection ~ 5110 2140
$Comp
L power:GND #PWR0132
U 1 1 618CB4C9
P 5110 2440
F 0 "#PWR0132" H 5110 2190 50  0001 C CNN
F 1 "GND" H 5115 2267 50  0000 C CNN
F 2 "" H 5110 2440 50  0001 C CNN
F 3 "" H 5110 2440 50  0001 C CNN
	1    5110 2440
	1    0    0    -1  
$EndComp
Wire Wire Line
	5110 2140 5800 2140
$Comp
L power:GND #PWR0131
U 1 1 618C8F5E
P 7760 2700
F 0 "#PWR0131" H 7760 2450 50  0001 C CNN
F 1 "GND" H 7765 2527 50  0000 C CNN
F 2 "" H 7760 2700 50  0001 C CNN
F 3 "" H 7760 2700 50  0001 C CNN
	1    7760 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7760 2600 7760 2700
$Comp
L Device:C C11
U 1 1 618C8528
P 7760 2450
F 0 "C11" H 7875 2496 50  0000 L CNN
F 1 "120u" H 7875 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 7798 2300 50  0001 C CNN
F 3 "" H 7760 2450 50  0001 C CNN
F 4 "" H 7950 2310 50  0000 C CNN "Voltage"
F 5 "" H 7760 2450 50  0001 C CNN "Part Number"
F 6 "" H 7760 2450 50  0001 C CNN "Manufactuer"
F 7 "C15008 " H 7760 2450 50  0001 C CNN "LCSC"
F 8 "X5R 100uF 6.3V ±20% 1206 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS" H 7760 2450 50  0001 C CNN "Comments"
	1    7760 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7760 2140 7760 2300
Connection ~ 7760 2140
Wire Wire Line
	7760 2040 7760 2140
Wire Wire Line
	7600 2140 7540 2140
Connection ~ 7600 2140
Wire Wire Line
	7600 2240 7600 2140
Wire Wire Line
	6650 2240 7600 2240
Wire Wire Line
	7760 2140 7600 2140
$Comp
L Device:L L1
U 1 1 618C573E
P 7390 2140
F 0 "L1" V 7580 2140 50  0000 C CNN
F 1 "100uH" V 7489 2140 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 7390 2140 50  0001 C CNN
F 3 "~" H 7390 2140 50  0001 C CNN
F 4 "C68035 " V 7390 2140 50  0001 C CNN "LCSC"
F 5 "0805 Inductors (SMD) ROHS 100uH" V 7390 2140 50  0001 C CNN "Comments"
	1    7390 2140
	0    -1   -1   0   
$EndComp
Connection ~ 6960 2140
Wire Wire Line
	6960 2140 7240 2140
Wire Wire Line
	6960 2140 6960 2440
Wire Wire Line
	6650 2140 6960 2140
$Comp
L power:GND #PWR0130
U 1 1 618C39D6
P 6960 2740
F 0 "#PWR0130" H 6960 2490 50  0001 C CNN
F 1 "GND" H 6965 2567 50  0000 C CNN
F 2 "" H 6960 2740 50  0001 C CNN
F 3 "" H 6960 2740 50  0001 C CNN
	1    6960 2740
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N5817 D12
U 1 1 618BF451
P 6960 2590
F 0 "D12" V 6914 2670 50  0000 L CNN
F 1 "1N5817" V 7005 2670 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 6960 2415 50  0001 C CNN
F 3 "" H 6960 2590 50  0001 C CNN
	1    6960 2590
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR0128
U 1 1 6189D3DA
P 7760 2040
F 0 "#PWR0128" H 7760 1890 50  0001 C CNN
F 1 "+3.3V" H 7775 2213 50  0000 C CNN
F 2 "" H 7760 2040 50  0001 C CNN
F 3 "" H 7760 2040 50  0001 C CNN
	1    7760 2040
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 2590 6650 2730
$Comp
L power:GND #PWR0127
U 1 1 6189CA7A
P 6650 2730
F 0 "#PWR0127" H 6650 2480 50  0001 C CNN
F 1 "GND" H 6655 2557 50  0000 C CNN
F 2 "" H 6650 2730 50  0001 C CNN
F 3 "" H 6650 2730 50  0001 C CNN
	1    6650 2730
	1    0    0    -1  
$EndComp
Wire Wire Line
	5410 2240 5800 2240
Wire Wire Line
	5410 2240 5410 2450
$Comp
L power:GND #PWR0133
U 1 1 618CBB2F
P 5410 2450
F 0 "#PWR0133" H 5410 2200 50  0001 C CNN
F 1 "GND" H 5415 2277 50  0000 C CNN
F 2 "" H 5410 2450 50  0001 C CNN
F 3 "" H 5410 2450 50  0001 C CNN
	1    5410 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2590 5540 2590
NoConn ~ 5540 2590
Wire Wire Line
	5800 2490 5540 2490
NoConn ~ 5540 2490
Wire Wire Line
	5800 2390 5540 2390
NoConn ~ 5540 2390
$Comp
L custom:2594 U3
U 1 1 618B9E4A
P 5900 2690
F 0 "U3" H 6225 3555 50  0000 C CNN
F 1 "2594" H 6225 3464 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5950 3490 50  0001 C CNN
F 3 "" H 5950 3490 50  0001 C CNN
F 4 " C316691" H 5900 2690 50  0001 C CNN "LCSC"
F 5 "500mA 40V SOP-8 DC-DC Converters ROHS" H 5900 2690 50  0001 C CNN "Comments"
	1    5900 2690
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 61B7485F
P 2000 3540
AR Path="/615E5281/61B7485F" Ref="TP?"  Part="1" 
AR Path="/615E7CAC/61B7485F" Ref="TP3"  Part="1" 
F 0 "TP3" H 2058 3658 50  0000 L CNN
F 1 "TestPoint" H 2058 3567 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 2200 3540 50  0001 C CNN
F 3 "~" H 2200 3540 50  0001 C CNN
	1    2000 3540
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 61B74D64
P 2030 4050
AR Path="/615E5281/61B74D64" Ref="TP?"  Part="1" 
AR Path="/615E7CAC/61B74D64" Ref="TP4"  Part="1" 
F 0 "TP4" H 2088 4168 50  0000 L CNN
F 1 "TestPoint" H 2088 4077 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 2088 4031 50  0001 L CNN
F 3 "~" H 2230 4050 50  0001 C CNN
	1    2030 4050
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 61B7528A
P 2810 3460
AR Path="/615E5281/61B7528A" Ref="TP?"  Part="1" 
AR Path="/615E7CAC/61B7528A" Ref="TP5"  Part="1" 
F 0 "TP5" H 2868 3578 50  0000 L CNN
F 1 "TestPoint" H 2868 3487 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 3010 3460 50  0001 C CNN
F 3 "~" H 3010 3460 50  0001 C CNN
	1    2810 3460
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0165
U 1 1 61B75EAD
P 1740 3540
F 0 "#PWR0165" H 1740 3390 50  0001 C CNN
F 1 "+12V" H 1755 3713 50  0000 C CNN
F 2 "" H 1740 3540 50  0001 C CNN
F 3 "" H 1740 3540 50  0001 C CNN
	1    1740 3540
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0166
U 1 1 61B773FF
P 1670 4070
F 0 "#PWR0166" H 1670 3920 50  0001 C CNN
F 1 "+3.3V" H 1685 4243 50  0000 C CNN
F 2 "" H 1670 4070 50  0001 C CNN
F 3 "" H 1670 4070 50  0001 C CNN
	1    1670 4070
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0167
U 1 1 61B77EDD
P 2810 3690
F 0 "#PWR0167" H 2810 3440 50  0001 C CNN
F 1 "GND" H 2815 3517 50  0000 C CNN
F 2 "" H 2810 3690 50  0001 C CNN
F 3 "" H 2810 3690 50  0001 C CNN
	1    2810 3690
	1    0    0    -1  
$EndComp
Wire Wire Line
	2810 3460 2810 3580
Wire Wire Line
	2030 4050 2030 4190
Wire Wire Line
	2030 4190 1670 4190
Wire Wire Line
	1670 4190 1670 4070
Wire Wire Line
	2000 3540 2000 3690
Wire Wire Line
	2000 3690 1740 3690
Wire Wire Line
	1740 3690 1740 3540
$Comp
L Connector:TestPoint TP?
U 1 1 61B79F3B
P 2530 4060
AR Path="/615E5281/61B79F3B" Ref="TP?"  Part="1" 
AR Path="/615E7CAC/61B79F3B" Ref="TP7"  Part="1" 
F 0 "TP7" H 2588 4178 50  0000 L CNN
F 1 "TestPoint" H 2588 4087 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 2588 4041 50  0001 L CNN
F 3 "~" H 2730 4060 50  0001 C CNN
	1    2530 4060
	1    0    0    -1  
$EndComp
Wire Wire Line
	2530 4060 2530 4190
Wire Wire Line
	2530 4190 2030 4190
Connection ~ 2030 4190
$Comp
L Connector:TestPoint TP?
U 1 1 61B7B6C1
P 3350 3460
AR Path="/615E5281/61B7B6C1" Ref="TP?"  Part="1" 
AR Path="/615E7CAC/61B7B6C1" Ref="TP8"  Part="1" 
F 0 "TP8" H 3408 3578 50  0000 L CNN
F 1 "TestPoint" H 3408 3487 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 3550 3460 50  0001 C CNN
F 3 "~" H 3550 3460 50  0001 C CNN
	1    3350 3460
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3460 3350 3580
Wire Wire Line
	3350 3580 2810 3580
Connection ~ 2810 3580
Wire Wire Line
	2810 3580 2810 3690
$EndSCHEMATC
