#!/usr/bin/python
import serial
import matplotlib.pyplot as plt

ser = serial.Serial("COM6",115200)

tekst = str(ser.read(200))
print(tekst)
meetingen = tekst.split("\\r\\n")
print(meetingen)
ser.close()

index = 0
for item in meetingen:
    meetingen[index] = (item.split(", "))
    #print(item)
    index = index + 1

for item in meetingen:
    for items in item:
        print(items)
        
print(meetingen)