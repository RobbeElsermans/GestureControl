EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
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
L VL53L3CX:VL53L3CXV0DH_1 U?
U 1 1 623B5A6D
P 3850 3700
AR Path="/62398514/623B5A6D" Ref="U?"  Part="1" 
AR Path="/623A41A0/623B5A6D" Ref="U4"  Part="1" 
AR Path="/623B5A6D" Ref="U4"  Part="1" 
F 0 "U4" H 5000 4100 60  0000 C CNN
F 1 "VL53L3CXV0DH_RIGHT" H 4850 3981 60  0000 C CNN
F 2 "VL53L3CX:VL53L3CXV0DH&slash_1" H 4850 3940 60  0001 C CNN
F 3 "" H 3850 3700 60  0000 C CNN
	1    3850 3700
	1    0    0    -1  
$EndComp
Text GLabel 5900 4200 2    50   Input ~ 0
GPIOI_2
$Comp
L power:+3.3V #PWR?
U 1 1 623B5A74
P 5900 3800
AR Path="/62398514/623B5A74" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5A74" Ref="#PWR044"  Part="1" 
F 0 "#PWR044" H 5900 3650 50  0001 C CNN
F 1 "+3.3V" V 5915 3928 50  0000 L CNN
F 2 "" H 5900 3800 50  0001 C CNN
F 3 "" H 5900 3800 50  0001 C CNN
	1    5900 3800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 623B5A7A
P 5900 3700
AR Path="/62398514/623B5A7A" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5A7A" Ref="#PWR043"  Part="1" 
F 0 "#PWR043" H 5900 3450 50  0001 C CNN
F 1 "GND" V 5905 3572 50  0000 R CNN
F 2 "" H 5900 3700 50  0001 C CNN
F 3 "" H 5900 3700 50  0001 C CNN
	1    5900 3700
	0    -1   -1   0   
$EndComp
Text GLabel 5900 3900 2    50   Input ~ 0
SCL1
Text GLabel 5900 4000 2    50   Input ~ 0
SDA1
$Comp
L power:+3.3V #PWR?
U 1 1 623B5A82
P 3800 3700
AR Path="/62398514/623B5A82" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5A82" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 3800 3550 50  0001 C CNN
F 1 "+3.3V" V 3815 3828 50  0000 L CNN
F 2 "" H 3800 3700 50  0001 C CNN
F 3 "" H 3800 3700 50  0001 C CNN
	1    3800 3700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 623B5A88
P 3800 3900
AR Path="/62398514/623B5A88" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5A88" Ref="#PWR040"  Part="1" 
F 0 "#PWR040" H 3800 3650 50  0001 C CNN
F 1 "GND" V 3805 3772 50  0000 R CNN
F 2 "" H 3800 3900 50  0001 C CNN
F 3 "" H 3800 3900 50  0001 C CNN
	1    3800 3900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 623B5A8E
P 3800 4000
AR Path="/62398514/623B5A8E" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5A8E" Ref="#PWR041"  Part="1" 
F 0 "#PWR041" H 3800 3750 50  0001 C CNN
F 1 "GND" V 3805 3872 50  0000 R CNN
F 2 "" H 3800 4000 50  0001 C CNN
F 3 "" H 3800 4000 50  0001 C CNN
	1    3800 4000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 623B5A94
P 3800 4200
AR Path="/62398514/623B5A94" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5A94" Ref="#PWR042"  Part="1" 
F 0 "#PWR042" H 3800 3950 50  0001 C CNN
F 1 "GND" V 3805 4072 50  0000 R CNN
F 2 "" H 3800 4200 50  0001 C CNN
F 3 "" H 3800 4200 50  0001 C CNN
	1    3800 4200
	0    1    1    0   
$EndComp
Text GLabel 3800 4100 0    50   Input ~ 0
XSHUT_2
$Comp
L power:GND #PWR?
U 1 1 623B5A9B
P 3800 3800
AR Path="/62398514/623B5A9B" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5A9B" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 3800 3550 50  0001 C CNN
F 1 "GND" V 3805 3672 50  0000 R CNN
F 2 "" H 3800 3800 50  0001 C CNN
F 3 "" H 3800 3800 50  0001 C CNN
	1    3800 3800
	0    1    1    0   
$EndComp
Wire Wire Line
	5900 4200 5850 4200
Wire Wire Line
	5850 4000 5900 4000
Wire Wire Line
	5900 3900 5850 3900
Wire Wire Line
	5850 3800 5900 3800
Wire Wire Line
	5900 3700 5850 3700
Wire Wire Line
	3800 3700 3850 3700
Wire Wire Line
	3850 3800 3800 3800
Wire Wire Line
	3800 3900 3850 3900
Wire Wire Line
	3850 4000 3800 4000
Wire Wire Line
	3800 4100 3850 4100
Wire Wire Line
	3850 4200 3800 4200
$Comp
L Device:C C?
U 1 1 623B5AAC
P 6550 3850
AR Path="/62398514/623B5AAC" Ref="C?"  Part="1" 
AR Path="/623A41A0/623B5AAC" Ref="C12"  Part="1" 
F 0 "C12" H 6665 3896 50  0000 L CNN
F 1 "100n" H 6665 3805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6588 3700 50  0001 C CNN
F 3 "~" H 6550 3850 50  0001 C CNN
	1    6550 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 623B5AB2
P 7000 3850
AR Path="/62398514/623B5AB2" Ref="C?"  Part="1" 
AR Path="/623A41A0/623B5AB2" Ref="C13"  Part="1" 
F 0 "C13" H 7115 3896 50  0000 L CNN
F 1 "4.7µ" H 7115 3805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7038 3700 50  0001 C CNN
F 3 "~" H 7000 3850 50  0001 C CNN
	1    7000 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 623B5AB8
P 6550 3650
AR Path="/62398514/623B5AB8" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5AB8" Ref="#PWR045"  Part="1" 
F 0 "#PWR045" H 6550 3500 50  0001 C CNN
F 1 "+3.3V" H 6565 3823 50  0000 C CNN
F 2 "" H 6550 3650 50  0001 C CNN
F 3 "" H 6550 3650 50  0001 C CNN
	1    6550 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 623B5ABE
P 7000 3650
AR Path="/62398514/623B5ABE" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5ABE" Ref="#PWR047"  Part="1" 
F 0 "#PWR047" H 7000 3500 50  0001 C CNN
F 1 "+3.3V" H 7015 3823 50  0000 C CNN
F 2 "" H 7000 3650 50  0001 C CNN
F 3 "" H 7000 3650 50  0001 C CNN
	1    7000 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 623B5AC4
P 6550 4050
AR Path="/62398514/623B5AC4" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5AC4" Ref="#PWR046"  Part="1" 
F 0 "#PWR046" H 6550 3800 50  0001 C CNN
F 1 "GND" H 6555 3877 50  0000 C CNN
F 2 "" H 6550 4050 50  0001 C CNN
F 3 "" H 6550 4050 50  0001 C CNN
	1    6550 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 623B5ACA
P 7000 4050
AR Path="/62398514/623B5ACA" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5ACA" Ref="#PWR048"  Part="1" 
F 0 "#PWR048" H 7000 3800 50  0001 C CNN
F 1 "GND" H 7005 3877 50  0000 C CNN
F 2 "" H 7000 4050 50  0001 C CNN
F 3 "" H 7000 4050 50  0001 C CNN
	1    7000 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 623B5AD0
P 8000 3900
AR Path="/62398514/623B5AD0" Ref="R?"  Part="1" 
AR Path="/623A41A0/623B5AD0" Ref="R15"  Part="1" 
F 0 "R15" V 7793 3900 50  0000 C CNN
F 1 "10k" V 7884 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 7930 3900 50  0001 C CNN
F 3 "~" H 8000 3900 50  0001 C CNN
	1    8000 3900
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 623B5AD6
P 8000 3600
AR Path="/62398514/623B5AD6" Ref="R?"  Part="1" 
AR Path="/623A41A0/623B5AD6" Ref="R14"  Part="1" 
F 0 "R14" V 7793 3600 50  0000 C CNN
F 1 "10k" V 7884 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 7930 3600 50  0001 C CNN
F 3 "~" H 8000 3600 50  0001 C CNN
	1    8000 3600
	0    1    1    0   
$EndComp
Text GLabel 7800 3600 0    50   Input ~ 0
GPIOI_2
Text GLabel 7800 3900 0    50   Input ~ 0
XSHUT_2
$Comp
L power:+3.3V #PWR?
U 1 1 623B5ADE
P 8200 3600
AR Path="/62398514/623B5ADE" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5ADE" Ref="#PWR049"  Part="1" 
F 0 "#PWR049" H 8200 3450 50  0001 C CNN
F 1 "+3.3V" V 8215 3728 50  0000 L CNN
F 2 "" H 8200 3600 50  0001 C CNN
F 3 "" H 8200 3600 50  0001 C CNN
	1    8200 3600
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 623B5AE4
P 8200 3900
AR Path="/62398514/623B5AE4" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5AE4" Ref="#PWR050"  Part="1" 
F 0 "#PWR050" H 8200 3750 50  0001 C CNN
F 1 "+3.3V" V 8215 4028 50  0000 L CNN
F 2 "" H 8200 3900 50  0001 C CNN
F 3 "" H 8200 3900 50  0001 C CNN
	1    8200 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	6550 4050 6550 4000
Wire Wire Line
	6550 3700 6550 3650
Wire Wire Line
	7000 3650 7000 3700
Wire Wire Line
	7000 4000 7000 4050
Wire Wire Line
	7800 3600 7850 3600
Wire Wire Line
	7850 3900 7800 3900
Wire Wire Line
	8150 3600 8200 3600
Wire Wire Line
	8200 3900 8150 3900
$Comp
L Device:C C?
U 1 1 623B5AF2
P 3100 3850
AR Path="/62398514/623B5AF2" Ref="C?"  Part="1" 
AR Path="/623A41A0/623B5AF2" Ref="C11"  Part="1" 
F 0 "C11" H 3215 3896 50  0000 L CNN
F 1 "100n" H 3215 3805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3138 3700 50  0001 C CNN
F 3 "~" H 3100 3850 50  0001 C CNN
	1    3100 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 623B5AF8
P 3100 3650
AR Path="/62398514/623B5AF8" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5AF8" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 3100 3500 50  0001 C CNN
F 1 "+3.3V" H 3115 3823 50  0000 C CNN
F 2 "" H 3100 3650 50  0001 C CNN
F 3 "" H 3100 3650 50  0001 C CNN
	1    3100 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 623B5AFE
P 3100 4050
AR Path="/62398514/623B5AFE" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/623B5AFE" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 3100 3800 50  0001 C CNN
F 1 "GND" H 3105 3877 50  0000 C CNN
F 2 "" H 3100 4050 50  0001 C CNN
F 3 "" H 3100 4050 50  0001 C CNN
	1    3100 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 4050 3100 4000
Wire Wire Line
	3100 3700 3100 3650
$Comp
L VL53L3CX:VL53L3CXV0DH_1 U?
U 1 1 6227DB1B
P 3850 3700
AR Path="/62398514/6227DB1B" Ref="U?"  Part="1" 
AR Path="/623A41A0/6227DB1B" Ref="U8"  Part="1" 
AR Path="/6227DB1B" Ref="U?"  Part="1" 
F 0 "U8" H 4850 4100 60  0000 C CNN
F 1 "VL53L3CXV0DH_RIGHT" H 4850 3981 60  0000 C CNN
F 2 "VL53L3CX:VL53L3CXV0DH&slash_1" H 4850 3940 60  0001 C CNN
F 3 "" H 3850 3700 60  0000 C CNN
	1    3850 3700
	1    0    0    -1  
$EndComp
Connection ~ 3850 3700
Connection ~ 3850 3800
Connection ~ 3850 3900
Connection ~ 3850 4000
Connection ~ 3850 4100
Connection ~ 3850 4200
Connection ~ 5850 4200
Connection ~ 5850 4000
Connection ~ 5850 3900
Connection ~ 5850 3800
Connection ~ 5850 3700
$Comp
L VL53L3CX:VL53L3CXV0DH_1 U?
U 1 1 62283C99
P 3850 3700
AR Path="/62398514/62283C99" Ref="U?"  Part="1" 
AR Path="/623A41A0/62283C99" Ref="U10"  Part="1" 
AR Path="/62283C99" Ref="U?"  Part="1" 
F 0 "U10" H 4700 4100 60  0000 C CNN
F 1 "VL53L3CXV0DH_RIGHT" H 4850 3981 60  0000 C CNN
F 2 "VL53L3CX:VL53L3CXV0DH&slash_1" H 4850 3940 60  0001 C CNN
F 3 "" H 3850 3700 60  0000 C CNN
	1    3850 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 622AAE4A
P 6550 4800
AR Path="/62398514/622AAE4A" Ref="C?"  Part="1" 
AR Path="/623A41A0/622AAE4A" Ref="C40"  Part="1" 
F 0 "C40" H 6665 4846 50  0000 L CNN
F 1 "100n" H 6665 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6588 4650 50  0001 C CNN
F 3 "~" H 6550 4800 50  0001 C CNN
	1    6550 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 622AAE50
P 7000 4800
AR Path="/62398514/622AAE50" Ref="C?"  Part="1" 
AR Path="/623A41A0/622AAE50" Ref="C42"  Part="1" 
F 0 "C42" H 7115 4846 50  0000 L CNN
F 1 "4.7µ" H 7115 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7038 4650 50  0001 C CNN
F 3 "~" H 7000 4800 50  0001 C CNN
	1    7000 4800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 622AAE56
P 6550 4600
AR Path="/62398514/622AAE56" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/622AAE56" Ref="#PWR0124"  Part="1" 
F 0 "#PWR0124" H 6550 4450 50  0001 C CNN
F 1 "+3.3V" H 6565 4773 50  0000 C CNN
F 2 "" H 6550 4600 50  0001 C CNN
F 3 "" H 6550 4600 50  0001 C CNN
	1    6550 4600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 622AAE5C
P 7000 4600
AR Path="/62398514/622AAE5C" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/622AAE5C" Ref="#PWR0125"  Part="1" 
F 0 "#PWR0125" H 7000 4450 50  0001 C CNN
F 1 "+3.3V" H 7015 4773 50  0000 C CNN
F 2 "" H 7000 4600 50  0001 C CNN
F 3 "" H 7000 4600 50  0001 C CNN
	1    7000 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 622AAE62
P 6550 5000
AR Path="/62398514/622AAE62" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/622AAE62" Ref="#PWR0126"  Part="1" 
F 0 "#PWR0126" H 6550 4750 50  0001 C CNN
F 1 "GND" H 6555 4827 50  0000 C CNN
F 2 "" H 6550 5000 50  0001 C CNN
F 3 "" H 6550 5000 50  0001 C CNN
	1    6550 5000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 622AAE68
P 7000 5000
AR Path="/62398514/622AAE68" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/622AAE68" Ref="#PWR0127"  Part="1" 
F 0 "#PWR0127" H 7000 4750 50  0001 C CNN
F 1 "GND" H 7005 4827 50  0000 C CNN
F 2 "" H 7000 5000 50  0001 C CNN
F 3 "" H 7000 5000 50  0001 C CNN
	1    7000 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 5000 6550 4950
Wire Wire Line
	6550 4650 6550 4600
Wire Wire Line
	7000 4600 7000 4650
Wire Wire Line
	7000 4950 7000 5000
$Comp
L Device:C C?
U 1 1 622AC52B
P 6550 2850
AR Path="/62398514/622AC52B" Ref="C?"  Part="1" 
AR Path="/623A41A0/622AC52B" Ref="C39"  Part="1" 
F 0 "C39" H 6665 2896 50  0000 L CNN
F 1 "100n" H 6665 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6588 2700 50  0001 C CNN
F 3 "~" H 6550 2850 50  0001 C CNN
	1    6550 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 622AC531
P 7000 2850
AR Path="/62398514/622AC531" Ref="C?"  Part="1" 
AR Path="/623A41A0/622AC531" Ref="C41"  Part="1" 
F 0 "C41" H 7115 2896 50  0000 L CNN
F 1 "4.7µ" H 7115 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7038 2700 50  0001 C CNN
F 3 "~" H 7000 2850 50  0001 C CNN
	1    7000 2850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 622AC537
P 6550 2650
AR Path="/62398514/622AC537" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/622AC537" Ref="#PWR0128"  Part="1" 
F 0 "#PWR0128" H 6550 2500 50  0001 C CNN
F 1 "+3.3V" H 6565 2823 50  0000 C CNN
F 2 "" H 6550 2650 50  0001 C CNN
F 3 "" H 6550 2650 50  0001 C CNN
	1    6550 2650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 622AC53D
P 7000 2650
AR Path="/62398514/622AC53D" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/622AC53D" Ref="#PWR0129"  Part="1" 
F 0 "#PWR0129" H 7000 2500 50  0001 C CNN
F 1 "+3.3V" H 7015 2823 50  0000 C CNN
F 2 "" H 7000 2650 50  0001 C CNN
F 3 "" H 7000 2650 50  0001 C CNN
	1    7000 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 622AC543
P 6550 3050
AR Path="/62398514/622AC543" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/622AC543" Ref="#PWR0130"  Part="1" 
F 0 "#PWR0130" H 6550 2800 50  0001 C CNN
F 1 "GND" H 6555 2877 50  0000 C CNN
F 2 "" H 6550 3050 50  0001 C CNN
F 3 "" H 6550 3050 50  0001 C CNN
	1    6550 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 622AC549
P 7000 3050
AR Path="/62398514/622AC549" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/622AC549" Ref="#PWR0131"  Part="1" 
F 0 "#PWR0131" H 7000 2800 50  0001 C CNN
F 1 "GND" H 7005 2877 50  0000 C CNN
F 2 "" H 7000 3050 50  0001 C CNN
F 3 "" H 7000 3050 50  0001 C CNN
	1    7000 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 3050 6550 3000
Wire Wire Line
	6550 2700 6550 2650
Wire Wire Line
	7000 2650 7000 2700
Wire Wire Line
	7000 3000 7000 3050
$Comp
L Device:C C?
U 1 1 622B8A44
P 3100 2850
AR Path="/62398514/622B8A44" Ref="C?"  Part="1" 
AR Path="/623A41A0/622B8A44" Ref="C49"  Part="1" 
F 0 "C49" H 3215 2896 50  0000 L CNN
F 1 "100n" H 3215 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3138 2700 50  0001 C CNN
F 3 "~" H 3100 2850 50  0001 C CNN
	1    3100 2850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 622B8A4A
P 3100 2650
AR Path="/62398514/622B8A4A" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/622B8A4A" Ref="#PWR0144"  Part="1" 
F 0 "#PWR0144" H 3100 2500 50  0001 C CNN
F 1 "+3.3V" H 3115 2823 50  0000 C CNN
F 2 "" H 3100 2650 50  0001 C CNN
F 3 "" H 3100 2650 50  0001 C CNN
	1    3100 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 622B8A50
P 3100 3050
AR Path="/62398514/622B8A50" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/622B8A50" Ref="#PWR0145"  Part="1" 
F 0 "#PWR0145" H 3100 2800 50  0001 C CNN
F 1 "GND" H 3105 2877 50  0000 C CNN
F 2 "" H 3100 3050 50  0001 C CNN
F 3 "" H 3100 3050 50  0001 C CNN
	1    3100 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3050 3100 3000
Wire Wire Line
	3100 2700 3100 2650
$Comp
L Device:C C?
U 1 1 622B920C
P 3100 4800
AR Path="/62398514/622B920C" Ref="C?"  Part="1" 
AR Path="/623A41A0/622B920C" Ref="C50"  Part="1" 
F 0 "C50" H 3215 4846 50  0000 L CNN
F 1 "100n" H 3215 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3138 4650 50  0001 C CNN
F 3 "~" H 3100 4800 50  0001 C CNN
	1    3100 4800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 622B9212
P 3100 4600
AR Path="/62398514/622B9212" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/622B9212" Ref="#PWR0146"  Part="1" 
F 0 "#PWR0146" H 3100 4450 50  0001 C CNN
F 1 "+3.3V" H 3115 4773 50  0000 C CNN
F 2 "" H 3100 4600 50  0001 C CNN
F 3 "" H 3100 4600 50  0001 C CNN
	1    3100 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 622B9218
P 3100 5000
AR Path="/62398514/622B9218" Ref="#PWR?"  Part="1" 
AR Path="/623A41A0/622B9218" Ref="#PWR0147"  Part="1" 
F 0 "#PWR0147" H 3100 4750 50  0001 C CNN
F 1 "GND" H 3105 4827 50  0000 C CNN
F 2 "" H 3100 5000 50  0001 C CNN
F 3 "" H 3100 5000 50  0001 C CNN
	1    3100 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 5000 3100 4950
Wire Wire Line
	3100 4650 3100 4600
$EndSCHEMATC
