EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
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
L VL53L3CX:VL53L3CXV0DH_1 U3
U 1 1 6239ED1D
P 4250 3600
AR Path="/6239ED1D" Ref="U3"  Part="1" 
AR Path="/62398514/6239ED1D" Ref="U3"  Part="1" 
F 0 "U3" H 5250 3987 60  0000 C CNN
F 1 "VL53L3CXV0DH_CENTER" H 5250 3881 60  0000 C CNN
F 2 "VL53L3CX:VL53L3CXV0DH&slash_1" H 5250 3840 60  0001 C CNN
F 3 "" H 4250 3600 60  0000 C CNN
	1    4250 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR025
U 1 1 6239ED38
P 4250 3800
F 0 "#PWR025" H 4250 3550 50  0001 C CNN
F 1 "GND" V 4255 3672 50  0000 R CNN
F 2 "" H 4250 3800 50  0001 C CNN
F 3 "" H 4250 3800 50  0001 C CNN
	1    4250 3800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR026
U 1 1 6239ED3E
P 4250 3900
F 0 "#PWR026" H 4250 3650 50  0001 C CNN
F 1 "GND" V 4255 3772 50  0000 R CNN
F 2 "" H 4250 3900 50  0001 C CNN
F 3 "" H 4250 3900 50  0001 C CNN
	1    4250 3900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR027
U 1 1 6239ED44
P 4250 4100
F 0 "#PWR027" H 4250 3850 50  0001 C CNN
F 1 "GND" V 4255 3972 50  0000 R CNN
F 2 "" H 4250 4100 50  0001 C CNN
F 3 "" H 4250 4100 50  0001 C CNN
	1    4250 4100
	0    1    1    0   
$EndComp
Text GLabel 4250 4000 0    50   Input ~ 0
XSHUT_4
$Comp
L power:GND #PWR024
U 1 1 6239ED4B
P 4250 3700
F 0 "#PWR024" H 4250 3450 50  0001 C CNN
F 1 "GND" V 4255 3572 50  0000 R CNN
F 2 "" H 4250 3700 50  0001 C CNN
F 3 "" H 4250 3700 50  0001 C CNN
	1    4250 3700
	0    1    1    0   
$EndComp
$Comp
L Device:C C9
U 1 1 6239ED5C
P 7500 3750
F 0 "C9" H 7615 3796 50  0000 L CNN
F 1 "100n" H 7615 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 7538 3600 50  0001 C CNN
F 3 "~" H 7500 3750 50  0001 C CNN
	1    7500 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 6239ED62
P 7950 3750
F 0 "C10" H 8065 3796 50  0000 L CNN
F 1 "4.7µ" H 8065 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7988 3600 50  0001 C CNN
F 3 "~" H 7950 3750 50  0001 C CNN
	1    7950 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR031
U 1 1 6239ED74
P 7500 3950
F 0 "#PWR031" H 7500 3700 50  0001 C CNN
F 1 "GND" H 7505 3777 50  0000 C CNN
F 2 "" H 7500 3950 50  0001 C CNN
F 3 "" H 7500 3950 50  0001 C CNN
	1    7500 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR033
U 1 1 6239ED7A
P 7950 3950
F 0 "#PWR033" H 7950 3700 50  0001 C CNN
F 1 "GND" H 7955 3777 50  0000 C CNN
F 2 "" H 7950 3950 50  0001 C CNN
F 3 "" H 7950 3950 50  0001 C CNN
	1    7950 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 6239ED80
P 9050 3800
F 0 "R13" V 8843 3800 50  0000 C CNN
F 1 "10k" V 8934 3800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8980 3800 50  0001 C CNN
F 3 "~" H 9050 3800 50  0001 C CNN
	1    9050 3800
	0    1    1    0   
$EndComp
$Comp
L Device:R R12
U 1 1 6239ED86
P 9050 3500
F 0 "R12" V 8843 3500 50  0000 C CNN
F 1 "10k" V 8934 3500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8980 3500 50  0001 C CNN
F 3 "~" H 9050 3500 50  0001 C CNN
	1    9050 3500
	0    1    1    0   
$EndComp
Text GLabel 8850 3500 0    50   Input ~ 0
GPIOI_1
Text GLabel 8900 3800 0    50   Input ~ 0
XSHUT_1
$Comp
L power:+3.3V #PWR034
U 1 1 6239ED8E
P 9250 3500
F 0 "#PWR034" H 9250 3350 50  0001 C CNN
F 1 "+3.3V" V 9265 3628 50  0000 L CNN
F 2 "" H 9250 3500 50  0001 C CNN
F 3 "" H 9250 3500 50  0001 C CNN
	1    9250 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	7500 3950 7500 3900
Wire Wire Line
	7500 3600 7500 3550
Wire Wire Line
	7950 3550 7950 3600
Wire Wire Line
	7950 3900 7950 3950
Wire Wire Line
	8850 3500 8900 3500
Wire Wire Line
	9200 3500 9250 3500
Wire Wire Line
	9250 3800 9200 3800
$Comp
L Device:C C8
U 1 1 6239EDA2
P 3500 3750
F 0 "C8" H 3615 3796 50  0000 L CNN
F 1 "100n" H 3615 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3538 3600 50  0001 C CNN
F 3 "~" H 3500 3750 50  0001 C CNN
	1    3500 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 6239EDAE
P 3500 3950
F 0 "#PWR022" H 3500 3700 50  0001 C CNN
F 1 "GND" H 3505 3777 50  0000 C CNN
F 2 "" H 3500 3950 50  0001 C CNN
F 3 "" H 3500 3950 50  0001 C CNN
	1    3500 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3950 3500 3900
Wire Wire Line
	3500 3600 3500 3550
$Comp
L VL53L3CX:VL53L3CXV0DH_1 U?
U 1 1 6228C6A4
P 4250 4750
AR Path="/6228C6A4" Ref="U?"  Part="1" 
AR Path="/62398514/6228C6A4" Ref="U12"  Part="1" 
F 0 "U12" H 5250 5137 60  0000 C CNN
F 1 "VL53L3CXV0DH_CENTER" H 5250 5031 60  0000 C CNN
F 2 "VL53L3CX:VL53L3CXV0DH&slash_1" H 5250 4990 60  0001 C CNN
F 3 "" H 4250 4750 60  0000 C CNN
	1    4250 4750
	1    0    0    -1  
$EndComp
$Comp
L VL53L3CX:VL53L3CXV0DH_1 U?
U 1 1 6228CC20
P 4250 2450
AR Path="/6228CC20" Ref="U?"  Part="1" 
AR Path="/62398514/6228CC20" Ref="U13"  Part="1" 
F 0 "U13" H 5250 2837 60  0000 C CNN
F 1 "VL53L3CXV0DH_CENTER" H 5250 2731 60  0000 C CNN
F 2 "VL53L3CX:VL53L3CXV0DH&slash_1" H 5250 2690 60  0001 C CNN
F 3 "" H 4250 2450 60  0000 C CNN
	1    4250 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C36
U 1 1 622A7B51
P 7500 4700
F 0 "C36" H 7615 4746 50  0000 L CNN
F 1 "100n" H 7615 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 7538 4550 50  0001 C CNN
F 3 "~" H 7500 4700 50  0001 C CNN
	1    7500 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C38
U 1 1 622A7B57
P 7950 4700
F 0 "C38" H 8065 4746 50  0000 L CNN
F 1 "4.7µ" H 8065 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7988 4550 50  0001 C CNN
F 3 "~" H 7950 4700 50  0001 C CNN
	1    7950 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 622A7B69
P 7500 4900
F 0 "#PWR0118" H 7500 4650 50  0001 C CNN
F 1 "GND" H 7505 4727 50  0000 C CNN
F 2 "" H 7500 4900 50  0001 C CNN
F 3 "" H 7500 4900 50  0001 C CNN
	1    7500 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 622A7B6F
P 7950 4900
F 0 "#PWR0119" H 7950 4650 50  0001 C CNN
F 1 "GND" H 7955 4727 50  0000 C CNN
F 2 "" H 7950 4900 50  0001 C CNN
F 3 "" H 7950 4900 50  0001 C CNN
	1    7950 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 4900 7500 4850
Wire Wire Line
	7500 4550 7500 4500
Wire Wire Line
	7950 4500 7950 4550
Wire Wire Line
	7950 4850 7950 4900
$Comp
L Device:C C35
U 1 1 622A92E0
P 7500 2850
F 0 "C35" H 7615 2896 50  0000 L CNN
F 1 "100n" H 7615 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 7538 2700 50  0001 C CNN
F 3 "~" H 7500 2850 50  0001 C CNN
	1    7500 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C37
U 1 1 622A92E6
P 7950 2850
F 0 "C37" H 8065 2896 50  0000 L CNN
F 1 "4.7µ" H 8065 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7988 2700 50  0001 C CNN
F 3 "~" H 7950 2850 50  0001 C CNN
	1    7950 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 622A92F8
P 7500 3050
F 0 "#PWR0122" H 7500 2800 50  0001 C CNN
F 1 "GND" H 7505 2877 50  0000 C CNN
F 2 "" H 7500 3050 50  0001 C CNN
F 3 "" H 7500 3050 50  0001 C CNN
	1    7500 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 622A92FE
P 7950 3050
F 0 "#PWR0123" H 7950 2800 50  0001 C CNN
F 1 "GND" H 7955 2877 50  0000 C CNN
F 2 "" H 7950 3050 50  0001 C CNN
F 3 "" H 7950 3050 50  0001 C CNN
	1    7950 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 3050 7500 3000
Wire Wire Line
	7500 2700 7500 2650
Wire Wire Line
	7950 2650 7950 2700
Wire Wire Line
	7950 3000 7950 3050
$Comp
L Device:C C48
U 1 1 622B6BD6
P 3500 4650
F 0 "C48" H 3615 4696 50  0000 L CNN
F 1 "100n" H 3615 4605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3538 4500 50  0001 C CNN
F 3 "~" H 3500 4650 50  0001 C CNN
	1    3500 4650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0141
U 1 1 622B6BE2
P 3500 4850
F 0 "#PWR0141" H 3500 4600 50  0001 C CNN
F 1 "GND" H 3505 4677 50  0000 C CNN
F 2 "" H 3500 4850 50  0001 C CNN
F 3 "" H 3500 4850 50  0001 C CNN
	1    3500 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4850 3500 4800
Wire Wire Line
	3500 4500 3500 4450
$Comp
L Device:C C47
U 1 1 622B7668
P 3500 2800
F 0 "C47" H 3615 2846 50  0000 L CNN
F 1 "100n" H 3615 2755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3538 2650 50  0001 C CNN
F 3 "~" H 3500 2800 50  0001 C CNN
	1    3500 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0143
U 1 1 622B7674
P 3500 3000
F 0 "#PWR0143" H 3500 2750 50  0001 C CNN
F 1 "GND" H 3505 2827 50  0000 C CNN
F 2 "" H 3500 3000 50  0001 C CNN
F 3 "" H 3500 3000 50  0001 C CNN
	1    3500 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3000 3500 2950
Wire Wire Line
	3500 2650 3500 2600
$Comp
L power:GND #PWR0133
U 1 1 62414A09
P 4250 4850
F 0 "#PWR0133" H 4250 4600 50  0001 C CNN
F 1 "GND" V 4255 4722 50  0000 R CNN
F 2 "" H 4250 4850 50  0001 C CNN
F 3 "" H 4250 4850 50  0001 C CNN
	1    4250 4850
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0136
U 1 1 62414EF4
P 4250 4950
F 0 "#PWR0136" H 4250 4700 50  0001 C CNN
F 1 "GND" V 4255 4822 50  0000 R CNN
F 2 "" H 4250 4950 50  0001 C CNN
F 3 "" H 4250 4950 50  0001 C CNN
	1    4250 4950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0137
U 1 1 624151FE
P 4250 5050
F 0 "#PWR0137" H 4250 4800 50  0001 C CNN
F 1 "GND" V 4255 4922 50  0000 R CNN
F 2 "" H 4250 5050 50  0001 C CNN
F 3 "" H 4250 5050 50  0001 C CNN
	1    4250 5050
	0    1    1    0   
$EndComp
Text GLabel 4250 5150 0    50   Input ~ 0
XSHUT_7
$Comp
L power:GND #PWR0140
U 1 1 6241563B
P 4250 5250
F 0 "#PWR0140" H 4250 5000 50  0001 C CNN
F 1 "GND" V 4255 5122 50  0000 R CNN
F 2 "" H 4250 5250 50  0001 C CNN
F 3 "" H 4250 5250 50  0001 C CNN
	1    4250 5250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0142
U 1 1 62415D2D
P 4250 2950
F 0 "#PWR0142" H 4250 2700 50  0001 C CNN
F 1 "GND" V 4255 2822 50  0000 R CNN
F 2 "" H 4250 2950 50  0001 C CNN
F 3 "" H 4250 2950 50  0001 C CNN
	1    4250 2950
	0    1    1    0   
$EndComp
Text GLabel 4250 2850 0    50   Input ~ 0
XSHUT_1
$Comp
L power:GND #PWR0144
U 1 1 62415EA3
P 4250 2750
F 0 "#PWR0144" H 4250 2500 50  0001 C CNN
F 1 "GND" V 4255 2622 50  0000 R CNN
F 2 "" H 4250 2750 50  0001 C CNN
F 3 "" H 4250 2750 50  0001 C CNN
	1    4250 2750
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0145
U 1 1 624162C5
P 4250 2650
F 0 "#PWR0145" H 4250 2400 50  0001 C CNN
F 1 "GND" V 4255 2522 50  0000 R CNN
F 2 "" H 4250 2650 50  0001 C CNN
F 3 "" H 4250 2650 50  0001 C CNN
	1    4250 2650
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0146
U 1 1 62416412
P 4250 2550
F 0 "#PWR0146" H 4250 2300 50  0001 C CNN
F 1 "GND" V 4255 2422 50  0000 R CNN
F 2 "" H 4250 2550 50  0001 C CNN
F 3 "" H 4250 2550 50  0001 C CNN
	1    4250 2550
	0    1    1    0   
$EndComp
$Comp
L Device:R R29
U 1 1 6242B4D7
P 9050 4150
F 0 "R29" V 8843 4150 50  0000 C CNN
F 1 "10k" V 8934 4150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8980 4150 50  0001 C CNN
F 3 "~" H 9050 4150 50  0001 C CNN
	1    9050 4150
	0    1    1    0   
$EndComp
Text GLabel 8900 4150 0    50   Input ~ 0
XSHUT_4
Wire Wire Line
	9250 4150 9200 4150
$Comp
L Device:R R30
U 1 1 6242BFD3
P 9050 4450
F 0 "R30" V 8843 4450 50  0000 C CNN
F 1 "10k" V 8934 4450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8980 4450 50  0001 C CNN
F 3 "~" H 9050 4450 50  0001 C CNN
	1    9050 4450
	0    1    1    0   
$EndComp
Text GLabel 8900 4450 0    50   Input ~ 0
XSHUT_7
Wire Wire Line
	9250 4450 9200 4450
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62550D8B
P 2100 2650
AR Path="/623A3BAC/62550D8B" Ref="JP?"  Part="1" 
AR Path="/62398514/62550D8B" Ref="JP15"  Part="1" 
F 0 "JP15" H 2100 2763 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 2100 2764 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 2100 2650 50  0001 C CNN
F 3 "~" H 2100 2650 50  0001 C CNN
	1    2100 2650
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62550D91
P 2100 3650
AR Path="/623A3BAC/62550D91" Ref="JP?"  Part="1" 
AR Path="/62398514/62550D91" Ref="JP16"  Part="1" 
F 0 "JP16" H 2100 3763 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 2100 3764 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 2100 3650 50  0001 C CNN
F 3 "~" H 2100 3650 50  0001 C CNN
	1    2100 3650
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62550D97
P 2100 4600
AR Path="/623A3BAC/62550D97" Ref="JP?"  Part="1" 
AR Path="/62398514/62550D97" Ref="JP17"  Part="1" 
F 0 "JP17" H 2100 4713 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 2100 4714 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 2100 4600 50  0001 C CNN
F 3 "~" H 2100 4600 50  0001 C CNN
	1    2100 4600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0147
U 1 1 62550D9D
P 1950 2650
AR Path="/62398514/62550D9D" Ref="#PWR0147"  Part="1" 
AR Path="/623A3BAC/62550D9D" Ref="#PWR?"  Part="1" 
F 0 "#PWR0147" H 1950 2500 50  0001 C CNN
F 1 "+3.3V" V 1965 2778 50  0000 L CNN
F 2 "" H 1950 2650 50  0001 C CNN
F 3 "" H 1950 2650 50  0001 C CNN
	1    1950 2650
	0    -1   -1   0   
$EndComp
Text Label 2250 2650 0    50   ~ 0
PWR0
$Comp
L power:+3.3V #PWR0148
U 1 1 62550DA4
P 1950 3650
AR Path="/62398514/62550DA4" Ref="#PWR0148"  Part="1" 
AR Path="/623A3BAC/62550DA4" Ref="#PWR?"  Part="1" 
F 0 "#PWR0148" H 1950 3500 50  0001 C CNN
F 1 "+3.3V" V 1965 3778 50  0000 L CNN
F 2 "" H 1950 3650 50  0001 C CNN
F 3 "" H 1950 3650 50  0001 C CNN
	1    1950 3650
	0    -1   -1   0   
$EndComp
Text Label 2250 3650 0    50   ~ 0
PWR1
Text Label 2250 4600 0    50   ~ 0
PWR2
$Comp
L power:+3.3V #PWR0150
U 1 1 62551675
P 1950 4600
AR Path="/62398514/62551675" Ref="#PWR0150"  Part="1" 
AR Path="/623A3BAC/62551675" Ref="#PWR?"  Part="1" 
F 0 "#PWR0150" H 1950 4450 50  0001 C CNN
F 1 "+3.3V" V 1965 4728 50  0000 L CNN
F 2 "" H 1950 4600 50  0001 C CNN
F 3 "" H 1950 4600 50  0001 C CNN
	1    1950 4600
	0    -1   -1   0   
$EndComp
Text Label 3500 2600 2    50   ~ 0
PWR0
Text Label 4250 2450 2    50   ~ 0
PWR0
Text Label 7500 2650 2    50   ~ 0
PWR0
Text Label 7950 2650 2    50   ~ 0
PWR0
Text Label 9250 3800 0    50   ~ 0
PWR0
Text Label 9250 4150 0    50   ~ 0
PWR1
Text Label 3500 3550 2    50   ~ 0
PWR1
Text Label 4250 3600 2    50   ~ 0
PWR1
Text Label 7500 3550 2    50   ~ 0
PWR1
Text Label 7950 3550 2    50   ~ 0
PWR1
Text Label 9250 4450 0    50   ~ 0
PWR2
Text Label 3500 4450 2    50   ~ 0
PWR2
Text Label 4250 4750 2    50   ~ 0
PWR2
Text Label 7500 4500 2    50   ~ 0
PWR2
Text Label 7950 4500 2    50   ~ 0
PWR2
Text GLabel 6250 4100 2    50   Input ~ 0
GPIOI_1
$Comp
L power:GND #PWR0152
U 1 1 6255FCB9
P 6250 3600
AR Path="/62398514/6255FCB9" Ref="#PWR0152"  Part="1" 
AR Path="/623A3BAC/6255FCB9" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/6255FCB9" Ref="#PWR?"  Part="1" 
F 0 "#PWR0152" H 6250 3350 50  0001 C CNN
F 1 "GND" V 6255 3472 50  0000 R CNN
F 2 "" H 6250 3600 50  0001 C CNN
F 3 "" H 6250 3600 50  0001 C CNN
	1    6250 3600
	0    -1   -1   0   
$EndComp
Text GLabel 6550 3800 2    50   Input ~ 0
SCL1
Text GLabel 6550 3900 2    50   Input ~ 0
SDA1
Text GLabel 6250 5250 2    50   Input ~ 0
GPIOI_1
$Comp
L power:GND #PWR0153
U 1 1 6255FCC2
P 6250 4750
AR Path="/62398514/6255FCC2" Ref="#PWR0153"  Part="1" 
AR Path="/623A3BAC/6255FCC2" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/6255FCC2" Ref="#PWR?"  Part="1" 
F 0 "#PWR0153" H 6250 4500 50  0001 C CNN
F 1 "GND" V 6255 4622 50  0000 R CNN
F 2 "" H 6250 4750 50  0001 C CNN
F 3 "" H 6250 4750 50  0001 C CNN
	1    6250 4750
	0    -1   -1   0   
$EndComp
Text GLabel 6550 4950 2    50   Input ~ 0
SCL1
Text GLabel 6550 5050 2    50   Input ~ 0
SDA1
Text GLabel 6250 2950 2    50   Input ~ 0
GPIOI_1
$Comp
L power:GND #PWR0154
U 1 1 6255FCCB
P 6250 2450
AR Path="/62398514/6255FCCB" Ref="#PWR0154"  Part="1" 
AR Path="/623A3BAC/6255FCCB" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/6255FCCB" Ref="#PWR?"  Part="1" 
F 0 "#PWR0154" H 6250 2200 50  0001 C CNN
F 1 "GND" V 6255 2322 50  0000 R CNN
F 2 "" H 6250 2450 50  0001 C CNN
F 3 "" H 6250 2450 50  0001 C CNN
	1    6250 2450
	0    -1   -1   0   
$EndComp
Text GLabel 6550 2650 2    50   Input ~ 0
SCL1
Text GLabel 6550 2750 2    50   Input ~ 0
SDA1
Text Label 6250 2550 0    50   ~ 0
PWR0
Text Label 6250 3700 0    50   ~ 0
PWR1
Text Label 6250 4850 0    50   ~ 0
PWR2
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 6255FCD6
P 6400 5050
AR Path="/623A3BAC/6255FCD6" Ref="JP?"  Part="1" 
AR Path="/623A41A0/6255FCD6" Ref="JP?"  Part="1" 
AR Path="/62398514/6255FCD6" Ref="JP23"  Part="1" 
F 0 "JP23" H 6400 4950 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 6400 5164 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 6400 5050 50  0001 C CNN
F 3 "~" H 6400 5050 50  0001 C CNN
	1    6400 5050
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 6255FCDC
P 6400 4950
AR Path="/623A3BAC/6255FCDC" Ref="JP?"  Part="1" 
AR Path="/623A41A0/6255FCDC" Ref="JP?"  Part="1" 
AR Path="/62398514/6255FCDC" Ref="JP22"  Part="1" 
F 0 "JP22" H 6550 5050 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 6400 5064 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 6400 4950 50  0001 C CNN
F 3 "~" H 6400 4950 50  0001 C CNN
	1    6400 4950
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 6255FCE2
P 6400 3900
AR Path="/623A3BAC/6255FCE2" Ref="JP?"  Part="1" 
AR Path="/623A41A0/6255FCE2" Ref="JP?"  Part="1" 
AR Path="/62398514/6255FCE2" Ref="JP21"  Part="1" 
F 0 "JP21" H 6400 3800 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 6400 4014 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 6400 3900 50  0001 C CNN
F 3 "~" H 6400 3900 50  0001 C CNN
	1    6400 3900
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 6255FCE8
P 6400 3800
AR Path="/623A3BAC/6255FCE8" Ref="JP?"  Part="1" 
AR Path="/623A41A0/6255FCE8" Ref="JP?"  Part="1" 
AR Path="/62398514/6255FCE8" Ref="JP20"  Part="1" 
F 0 "JP20" H 6550 3900 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 6400 3914 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 6400 3800 50  0001 C CNN
F 3 "~" H 6400 3800 50  0001 C CNN
	1    6400 3800
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 6255FCEE
P 6400 2750
AR Path="/623A3BAC/6255FCEE" Ref="JP?"  Part="1" 
AR Path="/623A41A0/6255FCEE" Ref="JP?"  Part="1" 
AR Path="/62398514/6255FCEE" Ref="JP19"  Part="1" 
F 0 "JP19" H 6400 2650 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 6400 2864 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 6400 2750 50  0001 C CNN
F 3 "~" H 6400 2750 50  0001 C CNN
	1    6400 2750
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 6255FCF4
P 6400 2650
AR Path="/623A3BAC/6255FCF4" Ref="JP?"  Part="1" 
AR Path="/623A41A0/6255FCF4" Ref="JP?"  Part="1" 
AR Path="/62398514/6255FCF4" Ref="JP18"  Part="1" 
F 0 "JP18" H 6550 2750 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 6400 2764 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 6400 2650 50  0001 C CNN
F 3 "~" H 6400 2650 50  0001 C CNN
	1    6400 2650
	1    0    0    -1  
$EndComp
$EndSCHEMATC
