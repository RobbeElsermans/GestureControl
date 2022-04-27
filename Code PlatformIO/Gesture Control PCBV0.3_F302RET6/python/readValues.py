#!/usr/bin/python
#import serial
import matplotlib.pyplot as plt
import keyboard


#ser = serial.Serial("COM6",115200)

#tekst = str(ser.read(200))
tekst = "L156,C152,R875\\r\\nL158,C152,R875\\r\\nL162,C152,R875\\r\\nL164,C152,R875\\r\\nL166,C152,R875\\r\\nL168,C152,R875\\r\\nL587"
tekst2 = "L156,C152,R875\\r\\nL158,C152,R875\\r\\nL162,C152,R875\\r\\nL164,C152,R875\\r\\nL166,C152,R875\\r\\nL168,C152,R875\\r\\nL587"
counter = 0

while(True):
    try:
        if keyboard.is_pressed('q') or counter > 200:
            print("You pressed p")
            meetingen = tekst.split("\\r\\n")
            index = 0
            for item in meetingen:
                meetingen[index] = (item.split(", "))
                #print(item)
                index = index + 1

            finaalmeetingen =[]
            for item in meetingen:
                for items in item:
                    #print(items)
                    finaalmeetingen.append(items.split(","))
                index = 0
                subindex = 0

            for items in finaalmeetingen:
                for item in items:
                    #print(item)
                    #print(index)
                    if "L" in item :
                        finaalmeetingen[index][subindex] = str(item).replace("L", "")
                    if "C" in item :
                        finaalmeetingen[index][subindex] = str(item).replace("C", "")
                    if "R" in item :
                        finaalmeetingen[index][subindex] = str(item).replace("R", "")
                    subindex = subindex + 1
                if subindex < 2 :
                    finaalmeetingen.pop(index)
                subindex = 0
                index  = index + 1

            x = range(len(finaalmeetingen))
            y1 = []
            y2 = []
            y3 = []
            #print(finaalmeetingen)
            for items in finaalmeetingen:
                y1.append(items[0])
                y2.append(items[1])
                y3.append(items[2])

            #print(x)
            #print(y1)

            plt.plot(x,y1,label="left")
            plt.plot(x,y2,label="center")
            plt.plot(x,y3,label="right")
            plt.legend()
            plt.show()
            #print(meetingen)
            break
        else:
            tekst = tekst + tekst2
            counter = counter + 1
    except:
        #ophalen van de seriële monitor en bufferen
        break
    