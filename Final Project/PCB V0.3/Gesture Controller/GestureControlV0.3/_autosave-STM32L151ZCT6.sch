EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 5 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 12200 7600
Text GLabel 12800 6550 2    50   Input ~ 0
SDA
Text GLabel 12800 6450 2    50   Input ~ 0
SCL
$Comp
L Switch:SW_Push_Dual SW4
U 1 1 623CDB6C
P 1500 2450
AR Path="/623BE0FF/623CDB6C" Ref="SW4"  Part="1" 
AR Path="/623BC61F/623CDB6C" Ref="SW?"  Part="1" 
AR Path="/623C233F/623CDB6C" Ref="SW?"  Part="1" 
F 0 "SW?" H 1500 2735 50  0000 C CNN
F 1 "RST" H 1500 2644 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_Push_1P1T_NO_6x6mm_H9.5mm" H 1500 2650 50  0001 C CNN
F 3 "~" H 1500 2650 50  0001 C CNN
	1    1500 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2450 1950 2450
Wire Wire Line
	1700 2650 1950 2650
Wire Wire Line
	1300 2450 1050 2450
Wire Wire Line
	1300 2650 1050 2650
$Comp
L Device:C C21
U 1 1 623D003E
P 1500 2950
AR Path="/623BE0FF/623D003E" Ref="C21"  Part="1" 
AR Path="/623BC61F/623D003E" Ref="C?"  Part="1" 
AR Path="/623C233F/623D003E" Ref="C?"  Part="1" 
F 0 "C?" V 1248 2950 50  0000 C CNN
F 1 "100n" V 1339 2950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1538 2800 50  0001 C CNN
F 3 "~" H 1500 2950 50  0001 C CNN
	1    1500 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	1050 2450 1050 2650
Wire Wire Line
	1050 2650 1050 2950
Wire Wire Line
	1050 2950 1350 2950
Connection ~ 1050 2650
Wire Wire Line
	1650 2950 1950 2950
Wire Wire Line
	1950 2950 1950 2650
Wire Wire Line
	1950 2650 1950 2450
Connection ~ 1950 2650
Wire Wire Line
	1950 2450 2050 2450
Connection ~ 1950 2450
Text Label 2050 2450 0    50   ~ 0
RST
$Comp
L power:GND #PWR068
U 1 1 623D2FD4
P 1050 2950
AR Path="/623BE0FF/623D2FD4" Ref="#PWR068"  Part="1" 
AR Path="/623BC61F/623D2FD4" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/623D2FD4" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1050 2700 50  0001 C CNN
F 1 "GND" H 1055 2777 50  0000 C CNN
F 2 "" H 1050 2950 50  0001 C CNN
F 3 "" H 1050 2950 50  0001 C CNN
	1    1050 2950
	1    0    0    -1  
$EndComp
Connection ~ 1050 2950
Wire Wire Line
	11500 4150 11400 4150
Text Label 11400 4150 2    50   ~ 0
RST
$Comp
L Device:Crystal Y1
U 1 1 623D57DA
P 1400 3900
AR Path="/623BE0FF/623D57DA" Ref="Y1"  Part="1" 
AR Path="/623BC61F/623D57DA" Ref="Y?"  Part="1" 
AR Path="/623C233F/623D57DA" Ref="Y?"  Part="1" 
F 0 "Y?" V 1354 4031 50  0000 L CNN
F 1 "8MHz" V 1445 4031 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_HC49-SD" H 1400 3900 50  0001 C CNN
F 3 "~" H 1400 3900 50  0001 C CNN
	1    1400 3900
	0    1    1    0   
$EndComp
$Comp
L Device:C C17
U 1 1 623D735C
P 1150 3650
AR Path="/623BE0FF/623D735C" Ref="C17"  Part="1" 
AR Path="/623BC61F/623D735C" Ref="C?"  Part="1" 
AR Path="/623C233F/623D735C" Ref="C?"  Part="1" 
F 0 "C?" V 898 3650 50  0000 C CNN
F 1 "20p" V 989 3650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1188 3500 50  0001 C CNN
F 3 "~" H 1150 3650 50  0001 C CNN
	1    1150 3650
	0    1    1    0   
$EndComp
$Comp
L Device:C C18
U 1 1 623C6A25
P 1150 4150
AR Path="/623BE0FF/623C6A25" Ref="C18"  Part="1" 
AR Path="/623BC61F/623C6A25" Ref="C?"  Part="1" 
AR Path="/623C233F/623C6A25" Ref="C?"  Part="1" 
F 0 "C?" V 898 4150 50  0000 C CNN
F 1 "20p" V 989 4150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1188 4000 50  0001 C CNN
F 3 "~" H 1150 4150 50  0001 C CNN
	1    1150 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	1300 3650 1400 3650
Wire Wire Line
	1400 3650 1400 3750
Wire Wire Line
	1400 4050 1400 4150
Wire Wire Line
	1400 4150 1300 4150
$Comp
L power:GND #PWR066
U 1 1 623C6A26
P 900 4200
AR Path="/623BE0FF/623C6A26" Ref="#PWR066"  Part="1" 
AR Path="/623BC61F/623C6A26" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/623C6A26" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 900 3950 50  0001 C CNN
F 1 "GND" H 905 4027 50  0000 C CNN
F 2 "" H 900 4200 50  0001 C CNN
F 3 "" H 900 4200 50  0001 C CNN
	1    900  4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 4150 900  4150
Wire Wire Line
	900  4150 900  4200
Wire Wire Line
	1000 3650 900  3650
Wire Wire Line
	900  3650 900  4150
Connection ~ 900  4150
$Comp
L Device:R R18
U 1 1 623C6A27
P 1900 3650
AR Path="/623BE0FF/623C6A27" Ref="R18"  Part="1" 
AR Path="/623BC61F/623C6A27" Ref="R?"  Part="1" 
AR Path="/623C233F/623C6A27" Ref="R?"  Part="1" 
F 0 "R?" V 1693 3650 50  0000 C CNN
F 1 "N/A" V 1784 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1830 3650 50  0001 C CNN
F 3 "~" H 1900 3650 50  0001 C CNN
	1    1900 3650
	0    1    1    0   
$EndComp
$Comp
L Device:R R19
U 1 1 623C6A28
P 1900 4150
AR Path="/623BE0FF/623C6A28" Ref="R19"  Part="1" 
AR Path="/623BC61F/623C6A28" Ref="R?"  Part="1" 
AR Path="/623C233F/623C6A28" Ref="R?"  Part="1" 
F 0 "R?" V 1693 4150 50  0000 C CNN
F 1 "N/A" V 1784 4150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 1830 4150 50  0001 C CNN
F 3 "~" H 1900 4150 50  0001 C CNN
	1    1900 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	1750 3650 1400 3650
Connection ~ 1400 3650
Wire Wire Line
	1750 4150 1400 4150
Connection ~ 1400 4150
Wire Wire Line
	2050 4150 2100 4150
Wire Wire Line
	2100 4150 2100 3950
Wire Wire Line
	2100 3850 2100 3650
Wire Wire Line
	2100 3650 2050 3650
$Comp
L power:GND #PWR078
U 1 1 623C6A29
P 14500 2100
AR Path="/623BE0FF/623C6A29" Ref="#PWR078"  Part="1" 
AR Path="/623BC61F/623C6A29" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/623C6A29" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 14500 1850 50  0001 C CNN
F 1 "GND" V 14505 1972 50  0000 R CNN
F 2 "" H 14500 2100 50  0001 C CNN
F 3 "" H 14500 2100 50  0001 C CNN
	1    14500 2100
	0    1    1    0   
$EndComp
Text Label 14500 2600 2    50   ~ 0
FTDI_RTS
Text Label 14500 3100 2    50   ~ 0
SWDAT
Text Label 14500 3200 2    50   ~ 0
SWCLK
Text Label 1600 3350 2    50   ~ 0
MCO
Wire Wire Line
	1600 3350 2100 3350
Wire Wire Line
	2100 3350 2100 3650
Connection ~ 2100 3650
Text Label 14500 3300 2    50   ~ 0
SW0
Text Label 12800 5450 0    50   ~ 0
SWDAT
Text Label 12800 5550 0    50   ~ 0
SWCLK
Wire Wire Line
	2100 5350 1900 5350
Wire Wire Line
	1900 5350 1900 5650
Wire Wire Line
	1900 5650 1150 5650
Wire Wire Line
	1150 5650 1150 5250
$Comp
L Device:C C22
U 1 1 623C6A2B
P 1650 5100
AR Path="/623BE0FF/623C6A2B" Ref="C22"  Part="1" 
AR Path="/623BC61F/623C6A2B" Ref="C?"  Part="1" 
AR Path="/623C233F/623C6A2B" Ref="C?"  Part="1" 
F 0 "C?" H 1765 5146 50  0000 L CNN
F 1 "20p" H 1765 5055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1688 4950 50  0001 C CNN
F 3 "~" H 1650 5100 50  0001 C CNN
	1    1650 5100
	1    0    0    -1  
$EndComp
Connection ~ 1650 5250
Wire Wire Line
	1650 5250 2100 5250
$Comp
L Device:C C19
U 1 1 623C6A2C
P 1150 5100
AR Path="/623BE0FF/623C6A2C" Ref="C19"  Part="1" 
AR Path="/623BC61F/623C6A2C" Ref="C?"  Part="1" 
AR Path="/623C233F/623C6A2C" Ref="C?"  Part="1" 
F 0 "C?" H 900 5150 50  0000 L CNN
F 1 "20p" H 900 5050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1188 4950 50  0001 C CNN
F 3 "~" H 1150 5100 50  0001 C CNN
	1    1150 5100
	1    0    0    -1  
$EndComp
Connection ~ 1150 5250
$Comp
L power:GND #PWR069
U 1 1 62421548
P 1050 4850
AR Path="/623BE0FF/62421548" Ref="#PWR069"  Part="1" 
AR Path="/623BC61F/62421548" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/62421548" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1050 4600 50  0001 C CNN
F 1 "GND" V 1055 4722 50  0000 R CNN
F 2 "" H 1050 4850 50  0001 C CNN
F 3 "" H 1050 4850 50  0001 C CNN
	1    1050 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	1050 4850 1150 4850
Wire Wire Line
	1150 4850 1150 4950
Wire Wire Line
	1150 4850 1650 4850
Wire Wire Line
	1650 4850 1650 4950
Connection ~ 1150 4850
Text Label 14500 2400 2    50   ~ 0
FTDI_TXD
Text Label 14500 2500 2    50   ~ 0
FTDI_RXD
Text GLabel 12800 4150 2    50   Input ~ 0
LED_1
Text GLabel 12800 4250 2    50   Input ~ 0
LED_2
Text GLabel 12800 4350 2    50   Input ~ 0
LED_3
Text GLabel 12800 4450 2    50   Input ~ 0
LED_4
Text GLabel 12800 4750 2    50   Input ~ 0
LED_5
Text GLabel 11500 5850 0    50   Input ~ 0
XSHUT_0
Text GLabel 11500 5950 0    50   Input ~ 0
XSHUT_1
Text GLabel 11500 6050 0    50   Input ~ 0
XSHUT_2
Text GLabel 11500 6150 0    50   Input ~ 0
GPIOI_0
Text GLabel 11500 6250 0    50   Input ~ 0
GPIOI_1
Text GLabel 11500 6350 0    50   Input ~ 0
GPIOI_2
Wire Wire Line
	11500 4350 11150 4350
$Comp
L Device:C C24
U 1 1 62206499
P 11250 2950
AR Path="/623BE0FF/62206499" Ref="C24"  Part="1" 
AR Path="/623BC61F/62206499" Ref="C?"  Part="1" 
AR Path="/623C233F/62206499" Ref="C?"  Part="1" 
F 0 "C?" H 11365 2996 50  0000 L CNN
F 1 "100n" H 11365 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 11288 2800 50  0001 C CNN
F 3 "~" H 11250 2950 50  0001 C CNN
	1    11250 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR074
U 1 1 622070D1
P 11250 3200
AR Path="/623BE0FF/622070D1" Ref="#PWR074"  Part="1" 
AR Path="/623BC61F/622070D1" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/622070D1" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 11250 2950 50  0001 C CNN
F 1 "GND" H 11255 3027 50  0000 C CNN
F 2 "" H 11250 3200 50  0001 C CNN
F 3 "" H 11250 3200 50  0001 C CNN
	1    11250 3200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR073
U 1 1 623C6A07
P 11250 2700
AR Path="/623BE0FF/623C6A07" Ref="#PWR073"  Part="1" 
AR Path="/623BC61F/623C6A07" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/623C6A07" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 11250 2550 50  0001 C CNN
F 1 "+3.3V" H 11265 2873 50  0000 C CNN
F 2 "" H 11250 2700 50  0001 C CNN
F 3 "" H 11250 2700 50  0001 C CNN
	1    11250 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C25
U 1 1 623C6A08
P 11650 2950
AR Path="/623BE0FF/623C6A08" Ref="C25"  Part="1" 
AR Path="/623BC61F/623C6A08" Ref="C?"  Part="1" 
AR Path="/623C233F/623C6A08" Ref="C?"  Part="1" 
F 0 "C?" H 11765 2996 50  0000 L CNN
F 1 "100n" H 11765 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 11688 2800 50  0001 C CNN
F 3 "~" H 11650 2950 50  0001 C CNN
	1    11650 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C26
U 1 1 623C6A09
P 12050 2950
AR Path="/623BE0FF/623C6A09" Ref="C26"  Part="1" 
AR Path="/623BC61F/623C6A09" Ref="C?"  Part="1" 
AR Path="/623C233F/623C6A09" Ref="C?"  Part="1" 
F 0 "C?" H 12165 2996 50  0000 L CNN
F 1 "100n" H 12165 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 12088 2800 50  0001 C CNN
F 3 "~" H 12050 2950 50  0001 C CNN
	1    12050 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C27
U 1 1 623C6A0A
P 12450 2950
AR Path="/623BE0FF/623C6A0A" Ref="C27"  Part="1" 
AR Path="/623BC61F/623C6A0A" Ref="C?"  Part="1" 
AR Path="/623C233F/623C6A0A" Ref="C?"  Part="1" 
F 0 "C?" H 12565 2996 50  0000 L CNN
F 1 "100n" H 12565 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 12488 2800 50  0001 C CNN
F 3 "~" H 12450 2950 50  0001 C CNN
	1    12450 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	11650 3100 11650 3150
Wire Wire Line
	12050 3100 12050 3150
Wire Wire Line
	12450 3100 12450 3150
Wire Wire Line
	11650 2800 11650 2750
Wire Wire Line
	12050 2800 12050 2750
Wire Wire Line
	12450 2800 12450 2750
Wire Wire Line
	11250 3100 11250 3150
Wire Wire Line
	11250 2700 11250 2750
Wire Wire Line
	11250 3150 11650 3150
Connection ~ 11250 3150
Wire Wire Line
	11250 3150 11250 3200
Wire Wire Line
	11650 3150 12050 3150
Connection ~ 11650 3150
Wire Wire Line
	11650 2750 12050 2750
Connection ~ 11650 2750
Wire Wire Line
	11250 2750 11650 2750
Connection ~ 11250 2750
Wire Wire Line
	11250 2750 11250 2800
Wire Wire Line
	12050 2750 12450 2750
Connection ~ 12050 2750
Wire Wire Line
	12050 3150 12450 3150
Connection ~ 12050 3150
Text Label 2150 3850 0    50   ~ 0
OSM_IN
Text Label 2150 3950 0    50   ~ 0
OSM_OUT
Wire Wire Line
	1550 5250 1650 5250
Wire Wire Line
	1150 5250 1250 5250
$Comp
L Device:Crystal_GND23 Y2
U 1 1 623C6A2A
P 1400 5250
AR Path="/623BE0FF/623C6A2A" Ref="Y2"  Part="1" 
AR Path="/623BC61F/623C6A2A" Ref="Y?"  Part="1" 
AR Path="/623C233F/623C6A2A" Ref="Y?"  Part="1" 
F 0 "Y?" H 1550 5000 50  0000 R CNN
F 1 "32kHz" H 1600 5550 50  0000 R CNN
F 2 "Crystal:Crystal_SMD_SeikoEpson_MC306-4Pin_8.0x3.2mm" H 1400 5250 50  0001 C CNN
F 3 "~" H 1400 5250 50  0001 C CNN
	1    1400 5250
	-1   0    0    1   
$EndComp
Wire Wire Line
	2100 3950 2150 3950
Wire Wire Line
	2100 3850 2150 3850
Text Label 2100 5250 0    50   ~ 0
OS32_IN
Text Label 2100 5350 0    50   ~ 0
OS32_OUT
$Comp
L Device:C C29
U 1 1 623C6A16
P 12850 2950
AR Path="/623BE0FF/623C6A16" Ref="C29"  Part="1" 
AR Path="/623BC61F/623C6A16" Ref="C?"  Part="1" 
AR Path="/623C233F/623C6A16" Ref="C?"  Part="1" 
F 0 "C?" H 12965 2996 50  0000 L CNN
F 1 "100n" H 12965 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 12888 2800 50  0001 C CNN
F 3 "~" H 12850 2950 50  0001 C CNN
	1    12850 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C31
U 1 1 622C7D87
P 13250 2950
AR Path="/623BE0FF/622C7D87" Ref="C31"  Part="1" 
AR Path="/623BC61F/622C7D87" Ref="C?"  Part="1" 
AR Path="/623C233F/622C7D87" Ref="C?"  Part="1" 
F 0 "C?" H 13365 2996 50  0000 L CNN
F 1 "100n" H 13365 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 13288 2800 50  0001 C CNN
F 3 "~" H 13250 2950 50  0001 C CNN
	1    13250 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C32
U 1 1 622C801D
P 13650 2950
AR Path="/623BE0FF/622C801D" Ref="C32"  Part="1" 
AR Path="/623BC61F/622C801D" Ref="C?"  Part="1" 
AR Path="/623C233F/622C801D" Ref="C?"  Part="1" 
F 0 "C?" H 13765 2996 50  0000 L CNN
F 1 "4.7??" H 13765 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 13688 2800 50  0001 C CNN
F 3 "~" H 13650 2950 50  0001 C CNN
	1    13650 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	12850 2800 12850 2750
Wire Wire Line
	12850 2750 12450 2750
Connection ~ 12450 2750
Wire Wire Line
	13250 2800 13250 2750
Wire Wire Line
	13250 2750 12850 2750
Connection ~ 12850 2750
Wire Wire Line
	13650 2800 13650 2750
Wire Wire Line
	13650 2750 13250 2750
Connection ~ 13250 2750
Wire Wire Line
	13650 3100 13650 3150
Wire Wire Line
	13650 3150 13250 3150
Wire Wire Line
	13250 3150 13250 3100
Wire Wire Line
	13250 3150 12850 3150
Wire Wire Line
	12850 3150 12850 3100
Connection ~ 13250 3150
Wire Wire Line
	12850 3150 12450 3150
Connection ~ 12850 3150
Connection ~ 12450 3150
$Comp
L power:+3.3V #PWR075
U 1 1 623C6A19
P 12150 3700
AR Path="/623BE0FF/623C6A19" Ref="#PWR075"  Part="1" 
AR Path="/623BC61F/623C6A19" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/623C6A19" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 12150 3550 50  0001 C CNN
F 1 "+3.3V" H 12165 3873 50  0000 C CNN
F 2 "" H 12150 3700 50  0001 C CNN
F 3 "" H 12150 3700 50  0001 C CNN
	1    12150 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	12150 3700 12150 3750
Wire Wire Line
	12150 3750 12100 3750
Connection ~ 12100 3750
Wire Wire Line
	12100 3750 12000 3750
Wire Wire Line
	12200 3750 12150 3750
Connection ~ 12150 3750
Wire Wire Line
	12300 3750 12200 3750
Connection ~ 12200 3750
Wire Wire Line
	12200 7600 12300 7600
Wire Wire Line
	12000 7600 12100 7600
Wire Wire Line
	12300 7550 12300 7600
Wire Wire Line
	12200 7550 12200 7600
Wire Wire Line
	12100 7550 12100 7600
Connection ~ 12100 7600
Wire Wire Line
	12100 7600 12200 7600
Wire Wire Line
	12000 7550 12000 7600
$Comp
L power:+3.3V #PWR077
U 1 1 6218460E
P 12650 3500
AR Path="/623BE0FF/6218460E" Ref="#PWR077"  Part="1" 
AR Path="/623BC61F/6218460E" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/6218460E" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 12650 3350 50  0001 C CNN
F 1 "+3.3V" H 12665 3673 50  0000 C CNN
F 2 "" H 12650 3500 50  0001 C CNN
F 3 "" H 12650 3500 50  0001 C CNN
	1    12650 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	12650 3500 12650 3550
Wire Wire Line
	12650 3550 12400 3550
$Comp
L Device:C C28
U 1 1 6218AC21
P 12650 3750
AR Path="/623BE0FF/6218AC21" Ref="C28"  Part="1" 
AR Path="/623BC61F/6218AC21" Ref="C?"  Part="1" 
AR Path="/623C233F/6218AC21" Ref="C?"  Part="1" 
F 0 "C?" H 12765 3796 50  0000 L CNN
F 1 "100n" H 12765 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 12688 3600 50  0001 C CNN
F 3 "~" H 12650 3750 50  0001 C CNN
	1    12650 3750
	1    0    0    -1  
$EndComp
Connection ~ 12650 3550
$Comp
L Device:C C30
U 1 1 6218B05F
P 13050 3750
AR Path="/623BE0FF/6218B05F" Ref="C30"  Part="1" 
AR Path="/623BC61F/6218B05F" Ref="C?"  Part="1" 
AR Path="/623C233F/6218B05F" Ref="C?"  Part="1" 
F 0 "C?" H 13165 3796 50  0000 L CNN
F 1 "1??" H 13165 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 13088 3600 50  0001 C CNN
F 3 "~" H 13050 3750 50  0001 C CNN
	1    13050 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	12650 3600 12650 3550
Wire Wire Line
	13050 3600 13050 3550
Wire Wire Line
	13050 3550 12650 3550
Wire Wire Line
	12650 3900 12650 3950
Wire Wire Line
	12650 3950 13050 3950
Wire Wire Line
	13050 3900 13050 3950
Connection ~ 13050 3950
Wire Wire Line
	12400 7550 12400 7600
Wire Wire Line
	12400 7600 12550 7600
Wire Wire Line
	13050 3950 13700 3950
$Comp
L power:GND #PWR076
U 1 1 621A892A
P 12550 7650
AR Path="/623BE0FF/621A892A" Ref="#PWR076"  Part="1" 
AR Path="/623BC61F/621A892A" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/621A892A" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 12550 7400 50  0001 C CNN
F 1 "GND" H 12555 7477 50  0000 C CNN
F 2 "" H 12550 7650 50  0001 C CNN
F 3 "" H 12550 7650 50  0001 C CNN
	1    12550 7650
	1    0    0    -1  
$EndComp
Wire Wire Line
	12550 7650 12550 7600
Wire Wire Line
	12550 7600 13700 7600
Wire Wire Line
	12300 7600 12400 7600
Connection ~ 12300 7600
$Comp
L Device:C C23
U 1 1 623C6A02
P 11200 4750
AR Path="/623BE0FF/623C6A02" Ref="C23"  Part="1" 
AR Path="/623BC61F/623C6A02" Ref="C?"  Part="1" 
AR Path="/623C233F/623C6A02" Ref="C?"  Part="1" 
F 0 "C?" H 11315 4796 50  0000 L CNN
F 1 "100n" H 11315 4705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 11238 4600 50  0001 C CNN
F 3 "~" H 11200 4750 50  0001 C CNN
	1    11200 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	11150 4550 11200 4550
Wire Wire Line
	11200 4550 11200 4600
Wire Wire Line
	11200 4550 11500 4550
Connection ~ 11200 4550
$Comp
L power:GND #PWR072
U 1 1 623C6A03
P 11200 4900
AR Path="/623BE0FF/623C6A03" Ref="#PWR072"  Part="1" 
AR Path="/623BC61F/623C6A03" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/623C6A03" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 11200 4650 50  0001 C CNN
F 1 "GND" H 11205 4727 50  0000 C CNN
F 2 "" H 11200 4900 50  0001 C CNN
F 3 "" H 11200 4900 50  0001 C CNN
	1    11200 4900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR071
U 1 1 623C6A04
P 11150 4550
AR Path="/623BE0FF/623C6A04" Ref="#PWR071"  Part="1" 
AR Path="/623BC61F/623C6A04" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/623C6A04" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 11150 4400 50  0001 C CNN
F 1 "+3.3V" H 11165 4723 50  0000 C CNN
F 2 "" H 11150 4550 50  0001 C CNN
F 3 "" H 11150 4550 50  0001 C CNN
	1    11150 4550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	12400 3550 12400 3950
Wire Wire Line
	12300 3950 12300 3750
Wire Wire Line
	12200 3950 12200 3750
Wire Wire Line
	12100 3950 12100 3750
Wire Wire Line
	12000 3750 12000 3950
$Comp
L MCU_ST_STM32L1:STM32L151RETx U6
U 1 1 62156717
P 12200 5750
AR Path="/623BE0FF/62156717" Ref="U6"  Part="1" 
AR Path="/623BC61F/62156717" Ref="U?"  Part="1" 
AR Path="/623C233F/62156717" Ref="U?"  Part="1" 
F 0 "U?" H 12150 7731 50  0000 C CNN
F 1 "STM32L151RETx" H 12150 7640 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 11600 4050 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00098321.pdf" H 12200 5750 50  0001 C CNN
	1    12200 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	13700 3950 13700 7600
Connection ~ 12400 7600
Connection ~ 12550 7600
$Comp
L Connector_Generic:Conn_01x06 J7
U 1 1 62248104
P 14700 2300
AR Path="/623BE0FF/62248104" Ref="J7"  Part="1" 
AR Path="/623BC61F/62248104" Ref="J?"  Part="1" 
AR Path="/623C233F/62248104" Ref="J?"  Part="1" 
F 0 "J?" H 14780 2292 50  0000 L CNN
F 1 "FTDI" H 14780 2201 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Horizontal" H 14700 2300 50  0001 C CNN
F 3 "~" H 14700 2300 50  0001 C CNN
	1    14700 2300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J8
U 1 1 6224D166
P 14700 3100
AR Path="/623BE0FF/6224D166" Ref="J8"  Part="1" 
AR Path="/623BC61F/6224D166" Ref="J?"  Part="1" 
AR Path="/623C233F/6224D166" Ref="J?"  Part="1" 
F 0 "J?" H 14780 3142 50  0000 L CNN
F 1 "Serial Wire" H 14780 3051 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Horizontal" H 14700 3100 50  0001 C CNN
F 3 "~" H 14700 3100 50  0001 C CNN
	1    14700 3100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR081
U 1 1 62250606
P 14500 3000
AR Path="/623BE0FF/62250606" Ref="#PWR081"  Part="1" 
AR Path="/623BC61F/62250606" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/62250606" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 14500 2850 50  0001 C CNN
F 1 "+3.3V" V 14515 3128 50  0000 L CNN
F 2 "" H 14500 3000 50  0001 C CNN
F 3 "" H 14500 3000 50  0001 C CNN
	1    14500 3000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR080
U 1 1 62250AF9
P 14500 2900
AR Path="/623BE0FF/62250AF9" Ref="#PWR080"  Part="1" 
AR Path="/623BC61F/62250AF9" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/62250AF9" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 14500 2650 50  0001 C CNN
F 1 "GND" V 14505 2772 50  0000 R CNN
F 2 "" H 14500 2900 50  0001 C CNN
F 3 "" H 14500 2900 50  0001 C CNN
	1    14500 2900
	0    1    1    0   
$EndComp
Text Label 12800 6150 0    50   ~ 0
SW0
Text Label 11500 7250 2    50   ~ 0
OS32_IN
Text Label 11500 7350 2    50   ~ 0
OS32_OUT
Text Label 11500 5350 2    50   ~ 0
OSM_IN
Text Label 11500 5450 2    50   ~ 0
OSM_OUT
$Comp
L Connector_Generic:Conn_01x04 J9
U 1 1 62257EF1
P 14700 3700
AR Path="/623BE0FF/62257EF1" Ref="J9"  Part="1" 
AR Path="/623BC61F/62257EF1" Ref="J?"  Part="1" 
AR Path="/623C233F/62257EF1" Ref="J?"  Part="1" 
F 0 "J?" H 14780 3692 50  0000 L CNN
F 1 "USB" H 14780 3601 50  0000 L CNN
F 2 "" H 14700 3700 50  0001 C CNN
F 3 "~" H 14700 3700 50  0001 C CNN
	1    14700 3700
	1    0    0    -1  
$EndComp
Text Label 12800 5350 0    50   ~ 0
USB_DP
Text Label 12800 5250 0    50   ~ 0
USB_DN
Text Label 14500 3800 2    50   ~ 0
USB_DN
Text Label 14500 3700 2    50   ~ 0
USB_DP
$Comp
L power:GND #PWR083
U 1 1 6225BA70
P 14500 3900
AR Path="/623BE0FF/6225BA70" Ref="#PWR083"  Part="1" 
AR Path="/623BC61F/6225BA70" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/6225BA70" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 14500 3650 50  0001 C CNN
F 1 "GND" V 14505 3772 50  0000 R CNN
F 2 "" H 14500 3900 50  0001 C CNN
F 3 "" H 14500 3900 50  0001 C CNN
	1    14500 3900
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR082
U 1 1 623C6A11
P 14500 3600
AR Path="/623BE0FF/623C6A11" Ref="#PWR082"  Part="1" 
AR Path="/623BC61F/623C6A11" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/623C6A11" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 14500 3450 50  0001 C CNN
F 1 "+5V" V 14515 3728 50  0000 L CNN
F 2 "" H 14500 3600 50  0001 C CNN
F 3 "" H 14500 3600 50  0001 C CNN
	1    14500 3600
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push_Dual SW3
U 1 1 6225EE9C
P 1500 1300
AR Path="/623BE0FF/6225EE9C" Ref="SW3"  Part="1" 
AR Path="/623BC61F/6225EE9C" Ref="SW?"  Part="1" 
AR Path="/623C233F/6225EE9C" Ref="SW?"  Part="1" 
F 0 "SW?" H 1500 1585 50  0000 C CNN
F 1 "BOOT" H 1500 1494 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_Push_1P1T_NO_6x6mm_H9.5mm" H 1500 1500 50  0001 C CNN
F 3 "~" H 1500 1500 50  0001 C CNN
	1    1500 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 1300 1950 1300
Wire Wire Line
	1700 1500 1950 1500
Wire Wire Line
	1300 1300 1050 1300
Wire Wire Line
	1300 1500 1050 1500
$Comp
L Device:C C20
U 1 1 6225EEA6
P 1500 1800
AR Path="/623BE0FF/6225EEA6" Ref="C20"  Part="1" 
AR Path="/623BC61F/6225EEA6" Ref="C?"  Part="1" 
AR Path="/623C233F/6225EEA6" Ref="C?"  Part="1" 
F 0 "C?" V 1248 1800 50  0000 C CNN
F 1 "100n" V 1339 1800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1538 1650 50  0001 C CNN
F 3 "~" H 1500 1800 50  0001 C CNN
	1    1500 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	1050 1300 1050 1500
Wire Wire Line
	1050 1500 1050 1800
Wire Wire Line
	1050 1800 1350 1800
Connection ~ 1050 1500
Wire Wire Line
	1650 1800 1950 1800
Wire Wire Line
	1950 1800 1950 1500
Wire Wire Line
	1950 1500 1950 1300
Connection ~ 1950 1500
Wire Wire Line
	1950 1300 2050 1300
Connection ~ 1950 1300
Text Label 2050 1300 0    50   ~ 0
BOOT
Text Label 11150 4350 2    50   ~ 0
BOOT
Wire Wire Line
	11150 4050 11100 4050
Wire Wire Line
	11150 4350 11150 4050
$Comp
L Device:R R20
U 1 1 624A225F
P 10950 4050
AR Path="/623BE0FF/624A225F" Ref="R20"  Part="1" 
AR Path="/623BC61F/624A225F" Ref="R?"  Part="1" 
AR Path="/623C233F/624A225F" Ref="R?"  Part="1" 
F 0 "R?" V 10743 4050 50  0000 C CNN
F 1 "10k" V 10834 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 10880 4050 50  0001 C CNN
F 3 "~" H 10950 4050 50  0001 C CNN
	1    10950 4050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR070
U 1 1 624A5F0A
P 10800 4050
AR Path="/623BE0FF/624A5F0A" Ref="#PWR070"  Part="1" 
AR Path="/623BC61F/624A5F0A" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/624A5F0A" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 10800 3800 50  0001 C CNN
F 1 "GND" V 10805 3922 50  0000 R CNN
F 2 "" H 10800 4050 50  0001 C CNN
F 3 "" H 10800 4050 50  0001 C CNN
	1    10800 4050
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR067
U 1 1 623C6A14
P 1050 1300
AR Path="/623BE0FF/623C6A14" Ref="#PWR067"  Part="1" 
AR Path="/623BC61F/623C6A14" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/623C6A14" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1050 1150 50  0001 C CNN
F 1 "+3.3V" H 1065 1473 50  0000 C CNN
F 2 "" H 1050 1300 50  0001 C CNN
F 3 "" H 1050 1300 50  0001 C CNN
	1    1050 1300
	1    0    0    -1  
$EndComp
Connection ~ 1050 1300
Text Label 14500 2200 2    50   ~ 0
FTDI_CTS
$Comp
L power:+5V #PWR079
U 1 1 623C6A15
P 14500 2300
AR Path="/623BE0FF/623C6A15" Ref="#PWR079"  Part="1" 
AR Path="/623BC61F/623C6A15" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/623C6A15" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 14500 2150 50  0001 C CNN
F 1 "+5V" V 14515 2428 50  0000 L CNN
F 2 "" H 14500 2300 50  0001 C CNN
F 3 "" H 14500 2300 50  0001 C CNN
	1    14500 2300
	0    -1   -1   0   
$EndComp
Text Label 12800 6850 0    50   ~ 0
FTDI_TXD
Text Label 12800 6950 0    50   ~ 0
FTDI_RXD
Text Label 12800 7250 0    50   ~ 0
FTDI_RTS
Text Label 12800 7150 0    50   ~ 0
FTDI_CTS
$Comp
L Connector:TestPoint TP1
U 1 1 62379EC2
P 14250 4300
AR Path="/623BE0FF/62379EC2" Ref="TP1"  Part="1" 
AR Path="/623BC61F/62379EC2" Ref="TP?"  Part="1" 
AR Path="/623C233F/62379EC2" Ref="TP?"  Part="1" 
F 0 "TP?" V 14204 4488 50  0000 L CNN
F 1 "SDA_TEST" V 14295 4488 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_1.0x1.0mm" H 14450 4300 50  0001 C CNN
F 3 "~" H 14450 4300 50  0001 C CNN
	1    14250 4300
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP2
U 1 1 6237AA99
P 14250 4500
AR Path="/623BE0FF/6237AA99" Ref="TP2"  Part="1" 
AR Path="/623BC61F/6237AA99" Ref="TP?"  Part="1" 
AR Path="/623C233F/6237AA99" Ref="TP?"  Part="1" 
F 0 "TP?" V 14204 4688 50  0000 L CNN
F 1 "SCL_TEST" V 14295 4688 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_1.0x1.0mm" H 14450 4500 50  0001 C CNN
F 3 "~" H 14450 4500 50  0001 C CNN
	1    14250 4500
	0    1    1    0   
$EndComp
Text GLabel 14250 4500 0    50   Input ~ 0
SCL
Text GLabel 14250 4300 0    50   Input ~ 0
SDA
$Comp
L MCU_ST_STM32L1:STM32L151ZCTx U7
U 1 1 6238C2F0
P 7500 6050
AR Path="/623BE0FF/6238C2F0" Ref="U7"  Part="1" 
AR Path="/623BC61F/6238C2F0" Ref="U?"  Part="1" 
AR Path="/623C233F/6238C2F0" Ref="U?"  Part="1" 
F 0 "U?" H 7500 9831 50  0000 C CNN
F 1 "STM32L151ZCTx" H 7500 9740 50  0000 C CNN
F 2 "Package_QFP:LQFP-144_20x20mm_P0.5mm" H 6600 2650 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00111457.pdf" H 7500 6050 50  0001 C CNN
	1    7500 6050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 623C6A1A
P 1400 5450
AR Path="/623BE0FF/623C6A1A" Ref="#PWR0101"  Part="1" 
AR Path="/623BC61F/623C6A1A" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/623C6A1A" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1400 5200 50  0001 C CNN
F 1 "GND" H 1550 5300 50  0000 R CNN
F 2 "" H 1400 5450 50  0001 C CNN
F 3 "" H 1400 5450 50  0001 C CNN
	1    1400 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 623C6A1B
P 1400 5050
AR Path="/623BE0FF/623C6A1B" Ref="#PWR0102"  Part="1" 
AR Path="/623BC61F/623C6A1B" Ref="#PWR?"  Part="1" 
AR Path="/623C233F/623C6A1B" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1400 4800 50  0001 C CNN
F 1 "GND" H 1405 4877 50  0000 C CNN
F 2 "" H 1400 5050 50  0001 C CNN
F 3 "" H 1400 5050 50  0001 C CNN
	1    1400 5050
	-1   0    0    1   
$EndComp
$EndSCHEMATC
