EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32F4:STM32F401RETx U6
U 1 1 623C448F
P 5000 4350
F 0 "U6" H 4950 6231 50  0000 C CNN
F 1 "STM32F401RETx" H 4950 6140 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 4400 2650 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00102166.pdf" H 5000 4350 50  0001 C CNN
	1    5000 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0163
U 1 1 623C6CEF
P 5000 6400
F 0 "#PWR0163" H 5000 6150 50  0001 C CNN
F 1 "GND" H 5005 6227 50  0000 C CNN
F 2 "" H 5000 6400 50  0001 C CNN
F 3 "" H 5000 6400 50  0001 C CNN
	1    5000 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 6150 5200 6300
Wire Wire Line
	5200 6300 5100 6300
Wire Wire Line
	5000 6300 5000 6400
Wire Wire Line
	5100 6150 5100 6300
Connection ~ 5100 6300
Wire Wire Line
	5100 6300 5000 6300
Wire Wire Line
	5000 6150 5000 6300
Connection ~ 5000 6300
Wire Wire Line
	4900 6150 4900 6300
Wire Wire Line
	4900 6300 5000 6300
Wire Wire Line
	4800 6150 4800 6300
Wire Wire Line
	4800 6300 4900 6300
Connection ~ 4900 6300
Text GLabel 5650 5450 2    50   Input ~ 0
SDA
Text GLabel 5650 5350 2    50   Input ~ 0
SCL
Wire Wire Line
	5650 5350 5600 5350
Wire Wire Line
	5600 5450 5650 5450
$Comp
L Switch:SW_Push_Dual SW3
U 1 1 623CDB6C
P 2150 2550
F 0 "SW3" H 2150 2835 50  0000 C CNN
F 1 "SW_Push_Dual" H 2150 2744 50  0000 C CNN
F 2 "" H 2150 2750 50  0001 C CNN
F 3 "~" H 2150 2750 50  0001 C CNN
	1    2150 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 2550 2600 2550
Wire Wire Line
	2350 2750 2600 2750
Wire Wire Line
	1950 2550 1700 2550
Wire Wire Line
	1950 2750 1700 2750
$Comp
L Device:C C15
U 1 1 623D003E
P 2150 3050
F 0 "C15" V 1898 3050 50  0000 C CNN
F 1 "100n" V 1989 3050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2188 2900 50  0001 C CNN
F 3 "~" H 2150 3050 50  0001 C CNN
	1    2150 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	1700 2550 1700 2750
Wire Wire Line
	1700 2750 1700 3050
Wire Wire Line
	1700 3050 2000 3050
Connection ~ 1700 2750
Wire Wire Line
	2300 3050 2600 3050
Wire Wire Line
	2600 3050 2600 2750
Wire Wire Line
	2600 2750 2600 2550
Connection ~ 2600 2750
Wire Wire Line
	2600 2550 2700 2550
Connection ~ 2600 2550
Text Label 2700 2550 0    50   ~ 0
RST
$Comp
L power:GND #PWR0164
U 1 1 623D2FD4
P 1700 3050
F 0 "#PWR0164" H 1700 2800 50  0001 C CNN
F 1 "GND" H 1705 2877 50  0000 C CNN
F 2 "" H 1700 3050 50  0001 C CNN
F 3 "" H 1700 3050 50  0001 C CNN
	1    1700 3050
	1    0    0    -1  
$EndComp
Connection ~ 1700 3050
Wire Wire Line
	4300 2850 4200 2850
Text Label 4200 2850 2    50   ~ 0
RST
$Comp
L Device:Crystal Y1
U 1 1 623D57DA
P 2050 4000
F 0 "Y1" V 2004 4131 50  0000 L CNN
F 1 "8MHz" V 2095 4131 50  0000 L CNN
F 2 "" H 2050 4000 50  0001 C CNN
F 3 "~" H 2050 4000 50  0001 C CNN
	1    2050 4000
	0    1    1    0   
$EndComp
$Comp
L Device:C C16
U 1 1 623D735C
P 1800 3750
F 0 "C16" V 1548 3750 50  0000 C CNN
F 1 "20p" V 1639 3750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1838 3600 50  0001 C CNN
F 3 "~" H 1800 3750 50  0001 C CNN
	1    1800 3750
	0    1    1    0   
$EndComp
$Comp
L Device:C C17
U 1 1 623D81B2
P 1800 4250
F 0 "C17" V 1548 4250 50  0000 C CNN
F 1 "20p" V 1639 4250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1838 4100 50  0001 C CNN
F 3 "~" H 1800 4250 50  0001 C CNN
	1    1800 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 3750 2050 3750
Wire Wire Line
	2050 3750 2050 3850
Wire Wire Line
	2050 4150 2050 4250
Wire Wire Line
	2050 4250 1950 4250
$Comp
L power:GND #PWR0165
U 1 1 623D990B
P 1550 4300
F 0 "#PWR0165" H 1550 4050 50  0001 C CNN
F 1 "GND" H 1555 4127 50  0000 C CNN
F 2 "" H 1550 4300 50  0001 C CNN
F 3 "" H 1550 4300 50  0001 C CNN
	1    1550 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 4250 1550 4250
Wire Wire Line
	1550 4250 1550 4300
Wire Wire Line
	1650 3750 1550 3750
Wire Wire Line
	1550 3750 1550 4250
Connection ~ 1550 4250
$Comp
L Device:R R16
U 1 1 623DB503
P 2550 3750
F 0 "R16" V 2343 3750 50  0000 C CNN
F 1 "N/A" V 2434 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2480 3750 50  0001 C CNN
F 3 "~" H 2550 3750 50  0001 C CNN
	1    2550 3750
	0    1    1    0   
$EndComp
$Comp
L Device:R R17
U 1 1 623DBAF7
P 2550 4250
F 0 "R17" V 2343 4250 50  0000 C CNN
F 1 "N/A" V 2434 4250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2480 4250 50  0001 C CNN
F 3 "~" H 2550 4250 50  0001 C CNN
	1    2550 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	2400 3750 2050 3750
Connection ~ 2050 3750
Wire Wire Line
	2400 4250 2050 4250
Connection ~ 2050 4250
Wire Wire Line
	2700 4250 2750 4250
Wire Wire Line
	2750 4250 2750 4050
Wire Wire Line
	2750 3950 2750 3750
Wire Wire Line
	2750 3750 2700 3750
Wire Wire Line
	7450 2350 7400 2350
$Comp
L power:GND #PWR0170
U 1 1 623F3BA5
P 7400 2350
F 0 "#PWR0170" H 7400 2100 50  0001 C CNN
F 1 "GND" V 7405 2222 50  0000 R CNN
F 2 "" H 7400 2350 50  0001 C CNN
F 3 "" H 7400 2350 50  0001 C CNN
	1    7400 2350
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR0171
U 1 1 623F452B
P 7400 2450
F 0 "#PWR0171" H 7400 2300 50  0001 C CNN
F 1 "+3.3V" V 7415 2578 50  0000 L CNN
F 2 "" H 7400 2450 50  0001 C CNN
F 3 "" H 7400 2450 50  0001 C CNN
	1    7400 2450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7400 2450 7450 2450
Wire Wire Line
	7450 2550 7400 2550
Wire Wire Line
	7450 2650 7400 2650
Wire Wire Line
	7450 2750 7400 2750
Wire Wire Line
	7450 2850 7400 2850
Wire Wire Line
	7450 2950 7400 2950
Wire Wire Line
	7450 3050 7400 3050
Text Label 7400 2550 2    50   ~ 0
RST
Text Label 7400 2650 2    50   ~ 0
MCO
Text Label 7400 2950 2    50   ~ 0
SW0
$Comp
L Connector_Generic:Conn_01x09 J7
U 1 1 62403923
P 7650 2750
F 0 "J7" H 7730 2792 50  0000 L CNN
F 1 "Conn_01x09" H 7730 2701 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x09_P2.54mm_Vertical" H 7650 2750 50  0001 C CNN
F 3 "~" H 7650 2750 50  0001 C CNN
	1    7650 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 3150 7400 3150
Text Label 7400 3050 2    50   ~ 0
TMS
Text Label 7400 3150 2    50   ~ 0
TCK
Text Label 2250 3450 2    50   ~ 0
MCO
Wire Wire Line
	2250 3450 2750 3450
Wire Wire Line
	2750 3450 2750 3750
Connection ~ 2750 3750
Text Label 5950 4800 0    50   ~ 0
SW0
Wire Wire Line
	5600 4150 5650 4150
Wire Wire Line
	5600 4250 5650 4250
Text Label 5650 4150 0    50   ~ 0
TMS
Text Label 5650 4250 0    50   ~ 0
TCK
Wire Wire Line
	5600 3050 5650 3050
Wire Wire Line
	5600 3150 5650 3150
Text Label 5650 3050 0    50   ~ 0
USART_TX
Text Label 5650 3150 0    50   ~ 0
USART_RX
Wire Wire Line
	2750 5450 2550 5450
Wire Wire Line
	2550 5450 2550 5750
Wire Wire Line
	2550 5750 1800 5750
Wire Wire Line
	1800 5750 1800 5350
$Comp
L Device:C C19
U 1 1 62420A64
P 2300 5200
F 0 "C19" H 2415 5246 50  0000 L CNN
F 1 "4,3p" H 2415 5155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2338 5050 50  0001 C CNN
F 3 "~" H 2300 5200 50  0001 C CNN
	1    2300 5200
	1    0    0    -1  
$EndComp
Connection ~ 2300 5350
Wire Wire Line
	2300 5350 2750 5350
$Comp
L Device:C C18
U 1 1 62420EEB
P 1800 5200
F 0 "C18" H 1550 5250 50  0000 L CNN
F 1 "4.3p" H 1550 5150 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1838 5050 50  0001 C CNN
F 3 "~" H 1800 5200 50  0001 C CNN
	1    1800 5200
	1    0    0    -1  
$EndComp
Connection ~ 1800 5350
$Comp
L power:GND #PWR0172
U 1 1 62421548
P 1700 4950
F 0 "#PWR0172" H 1700 4700 50  0001 C CNN
F 1 "GND" V 1705 4822 50  0000 R CNN
F 2 "" H 1700 4950 50  0001 C CNN
F 3 "" H 1700 4950 50  0001 C CNN
	1    1700 4950
	0    1    1    0   
$EndComp
Wire Wire Line
	1700 4950 1800 4950
Wire Wire Line
	1800 4950 1800 5050
Wire Wire Line
	1800 4950 2300 4950
Wire Wire Line
	2300 4950 2300 5050
Connection ~ 1800 4950
Text Label 7400 2750 2    50   ~ 0
USART_TX
Text Label 7400 2850 2    50   ~ 0
USART_RX
Text GLabel 4250 5150 0    50   Input ~ 0
LED_1
Text GLabel 5650 5550 2    50   Input ~ 0
LED_2
Wire Wire Line
	5650 5550 5600 5550
Text GLabel 5650 4950 2    50   Input ~ 0
LED_3
Text GLabel 5950 4850 2    50   Input ~ 0
LED_4
Wire Wire Line
	5950 4800 5900 4800
Wire Wire Line
	5900 4800 5900 4850
Wire Wire Line
	5600 4850 5900 4850
Wire Wire Line
	5950 4850 5900 4850
Connection ~ 5900 4850
Wire Wire Line
	5650 4950 5600 4950
Text GLabel 5650 3850 2    50   Input ~ 0
LED_5
Wire Wire Line
	5650 3850 5600 3850
Text GLabel 5650 3750 2    50   Input ~ 0
XSHUT_0
Wire Wire Line
	5650 3750 5600 3750
Text GLabel 5650 3650 2    50   Input ~ 0
XSHUT_1
Text GLabel 5650 3350 2    50   Input ~ 0
XSHUT_2
Wire Wire Line
	5650 3350 5600 3350
Wire Wire Line
	5600 3650 5650 3650
Text GLabel 5650 2850 2    50   Input ~ 0
GPIOI_0
Wire Wire Line
	5650 2850 5600 2850
Text GLabel 4250 4550 0    50   Input ~ 0
GPIOI_1
Wire Wire Line
	4250 4550 4300 4550
Text GLabel 4250 4450 0    50   Input ~ 0
GPIOI_2
Wire Wire Line
	4250 4450 4300 4450
NoConn ~ 5600 5250
NoConn ~ 5600 5150
NoConn ~ 5600 5050
NoConn ~ 5600 4750
NoConn ~ 5600 4650
NoConn ~ 5600 4550
NoConn ~ 5600 4350
NoConn ~ 5600 4050
NoConn ~ 5600 3950
NoConn ~ 5600 3550
NoConn ~ 5600 3450
NoConn ~ 5600 3250
NoConn ~ 5600 2950
NoConn ~ 4300 4250
NoConn ~ 4300 4650
NoConn ~ 4300 4750
NoConn ~ 4300 4850
NoConn ~ 4300 4950
NoConn ~ 4300 5050
NoConn ~ 4300 5250
NoConn ~ 4300 5350
NoConn ~ 4300 5450
NoConn ~ 4300 5550
NoConn ~ 4300 5650
NoConn ~ 4300 5750
NoConn ~ 5600 5950
NoConn ~ 5600 5850
NoConn ~ 5600 5750
NoConn ~ 5600 5650
$Comp
L Device:R R18
U 1 1 624A225F
P 3750 2750
F 0 "R18" V 3543 2750 50  0000 C CNN
F 1 "10k" V 3634 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3680 2750 50  0001 C CNN
F 3 "~" H 3750 2750 50  0001 C CNN
	1    3750 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	4300 3050 3950 3050
$Comp
L power:GND #PWR0173
U 1 1 624A5F0A
P 3600 2750
F 0 "#PWR0173" H 3600 2500 50  0001 C CNN
F 1 "GND" V 3605 2622 50  0000 R CNN
F 2 "" H 3600 2750 50  0001 C CNN
F 3 "" H 3600 2750 50  0001 C CNN
	1    3600 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	4250 5150 4300 5150
$Comp
L Device:C C22
U 1 1 62206499
P 4050 1650
F 0 "C22" H 4165 1696 50  0000 L CNN
F 1 "100n" H 4165 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4088 1500 50  0001 C CNN
F 3 "~" H 4050 1650 50  0001 C CNN
	1    4050 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0162
U 1 1 622070D1
P 4050 1900
F 0 "#PWR0162" H 4050 1650 50  0001 C CNN
F 1 "GND" H 4055 1727 50  0000 C CNN
F 2 "" H 4050 1900 50  0001 C CNN
F 3 "" H 4050 1900 50  0001 C CNN
	1    4050 1900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0166
U 1 1 62207B66
P 4050 1400
F 0 "#PWR0166" H 4050 1250 50  0001 C CNN
F 1 "+3.3V" H 4065 1573 50  0000 C CNN
F 2 "" H 4050 1400 50  0001 C CNN
F 3 "" H 4050 1400 50  0001 C CNN
	1    4050 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C25
U 1 1 6220A38D
P 4450 1650
F 0 "C25" H 4565 1696 50  0000 L CNN
F 1 "100n" H 4565 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4488 1500 50  0001 C CNN
F 3 "~" H 4450 1650 50  0001 C CNN
	1    4450 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C26
U 1 1 6220A578
P 4850 1650
F 0 "C26" H 4965 1696 50  0000 L CNN
F 1 "100n" H 4965 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4888 1500 50  0001 C CNN
F 3 "~" H 4850 1650 50  0001 C CNN
	1    4850 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C27
U 1 1 6220A809
P 5250 1650
F 0 "C27" H 5365 1696 50  0000 L CNN
F 1 "100n" H 5365 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5288 1500 50  0001 C CNN
F 3 "~" H 5250 1650 50  0001 C CNN
	1    5250 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 1800 4450 1850
Wire Wire Line
	4850 1800 4850 1850
Wire Wire Line
	5250 1800 5250 1850
Wire Wire Line
	4450 1500 4450 1450
Wire Wire Line
	4850 1500 4850 1450
Wire Wire Line
	5250 1500 5250 1450
Wire Wire Line
	4050 1800 4050 1850
Wire Wire Line
	4050 1400 4050 1450
Wire Wire Line
	4050 1850 4450 1850
Connection ~ 4050 1850
Wire Wire Line
	4050 1850 4050 1900
Wire Wire Line
	4450 1850 4850 1850
Connection ~ 4450 1850
Wire Wire Line
	4450 1450 4850 1450
Connection ~ 4450 1450
Wire Wire Line
	4050 1450 4450 1450
Connection ~ 4050 1450
Wire Wire Line
	4050 1450 4050 1500
Wire Wire Line
	4850 1450 5250 1450
Connection ~ 4850 1450
Wire Wire Line
	4850 1850 5250 1850
Connection ~ 4850 1850
$Comp
L power:+3.3V #PWR0167
U 1 1 6224242D
P 4200 3350
F 0 "#PWR0167" H 4200 3200 50  0001 C CNN
F 1 "+3.3V" V 4215 3478 50  0000 L CNN
F 2 "" H 4200 3350 50  0001 C CNN
F 3 "" H 4200 3350 50  0001 C CNN
	1    4200 3350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 3950 4250 3950
Wire Wire Line
	4300 4050 4250 4050
Text Label 2800 3950 0    50   ~ 0
OSM_IN
Text Label 2800 4050 0    50   ~ 0
OSM_OUT
Text Label 4250 3950 2    50   ~ 0
OSM_IN
Text Label 4250 4050 2    50   ~ 0
OSM_OUT
$Comp
L Device:C C20
U 1 1 6225EC10
P 3200 3200
F 0 "C20" H 3085 3154 50  0000 R CNN
F 1 "2,2µ" H 3085 3245 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3238 3050 50  0001 C CNN
F 3 "~" H 3200 3200 50  0001 C CNN
	1    3200 3200
	-1   0    0    1   
$EndComp
Wire Wire Line
	2200 5350 2300 5350
Wire Wire Line
	1800 5350 1900 5350
$Comp
L Device:Crystal_GND23 Y2
U 1 1 6241A745
P 2050 5350
F 0 "Y2" H 2200 5100 50  0000 R CNN
F 1 "32kHz" H 2250 5650 50  0000 R CNN
F 2 "" H 2050 5350 50  0001 C CNN
F 3 "~" H 2050 5350 50  0001 C CNN
	1    2050 5350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2750 4050 2800 4050
Wire Wire Line
	2750 3950 2800 3950
Text Label 2750 5350 0    50   ~ 0
OS_IN
Text Label 2750 5450 0    50   ~ 0
OS_OUT
Text Label 4250 5850 2    50   ~ 0
OS_IN
Text Label 4250 5950 2    50   ~ 0
OS_OUT
Wire Wire Line
	4250 5950 4300 5950
Wire Wire Line
	4300 5850 4250 5850
$Comp
L Device:C C21
U 1 1 6228F775
P 3600 3200
F 0 "C21" H 3715 3246 50  0000 L CNN
F 1 "2,2µ" H 3715 3155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3638 3050 50  0001 C CNN
F 3 "~" H 3600 3200 50  0001 C CNN
	1    3600 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3050 3950 2750
Wire Wire Line
	3950 2750 3900 2750
$Comp
L power:GND #PWR0168
U 1 1 622A2885
P 3600 3450
F 0 "#PWR0168" H 3600 3200 50  0001 C CNN
F 1 "GND" H 3605 3277 50  0000 C CNN
F 2 "" H 3600 3450 50  0001 C CNN
F 3 "" H 3600 3450 50  0001 C CNN
	1    3600 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3350 3200 3400
Wire Wire Line
	3200 3400 3600 3400
Wire Wire Line
	3600 3400 3600 3350
Wire Wire Line
	3900 3250 3900 3000
Wire Wire Line
	3200 3000 3200 3050
Wire Wire Line
	3600 3050 3600 3000
Connection ~ 3600 3000
Wire Wire Line
	3600 3000 3200 3000
Wire Wire Line
	3900 3250 4300 3250
Wire Wire Line
	3900 3000 3600 3000
Wire Wire Line
	3600 3450 3600 3400
Connection ~ 3600 3400
Wire Wire Line
	4200 3350 4300 3350
$Comp
L Device:C C28
U 1 1 622C7985
P 5650 1650
F 0 "C28" H 5765 1696 50  0000 L CNN
F 1 "100n" H 5765 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5688 1500 50  0001 C CNN
F 3 "~" H 5650 1650 50  0001 C CNN
	1    5650 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C29
U 1 1 622C7D87
P 6050 1650
F 0 "C29" H 6165 1696 50  0000 L CNN
F 1 "100n" H 6165 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6088 1500 50  0001 C CNN
F 3 "~" H 6050 1650 50  0001 C CNN
	1    6050 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C30
U 1 1 622C801D
P 6450 1650
F 0 "C30" H 6565 1696 50  0000 L CNN
F 1 "4.7µ" H 6565 1605 50  0000 L CNN
F 2 "" H 6488 1500 50  0001 C CNN
F 3 "~" H 6450 1650 50  0001 C CNN
	1    6450 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1500 5650 1450
Wire Wire Line
	5650 1450 5250 1450
Connection ~ 5250 1450
Wire Wire Line
	6050 1500 6050 1450
Wire Wire Line
	6050 1450 5650 1450
Connection ~ 5650 1450
Wire Wire Line
	6450 1500 6450 1450
Wire Wire Line
	6450 1450 6050 1450
Connection ~ 6050 1450
Wire Wire Line
	6450 1800 6450 1850
Wire Wire Line
	6450 1850 6050 1850
Wire Wire Line
	6050 1850 6050 1800
Wire Wire Line
	6050 1850 5650 1850
Wire Wire Line
	5650 1850 5650 1800
Connection ~ 6050 1850
Wire Wire Line
	5650 1850 5250 1850
Connection ~ 5650 1850
Connection ~ 5250 1850
$Comp
L power:+3.3V #PWR0169
U 1 1 622E3425
P 4950 2400
F 0 "#PWR0169" H 4950 2250 50  0001 C CNN
F 1 "+3.3V" H 4965 2573 50  0000 C CNN
F 2 "" H 4950 2400 50  0001 C CNN
F 3 "" H 4950 2400 50  0001 C CNN
	1    4950 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 2400 4950 2450
Wire Wire Line
	4950 2450 4900 2450
Wire Wire Line
	4800 2450 4800 2650
Wire Wire Line
	4900 2650 4900 2450
Connection ~ 4900 2450
Wire Wire Line
	4900 2450 4800 2450
Wire Wire Line
	5000 2650 5000 2450
Wire Wire Line
	5000 2450 4950 2450
Connection ~ 4950 2450
Wire Wire Line
	5100 2650 5100 2450
Wire Wire Line
	5100 2450 5000 2450
Connection ~ 5000 2450
Wire Wire Line
	5200 2650 5200 2450
Wire Wire Line
	5200 2450 5100 2450
Connection ~ 5100 2450
$EndSCHEMATC
