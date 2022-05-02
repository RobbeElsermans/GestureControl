#!/usr/bin/python
from typing import Counter
import serial
import matplotlib.pyplot as plt

ser = serial.Serial("COM6",115200)

#tekst = "L156,C152,R875\\r\\nL158,C152,R875\\r\\nL162,C152,R875\\r\\nL164,C152,R875\\r\\nL166,C152,R875\\r\\nL168,C152,R875\\r\\nL587"
#tekst2 = "L156,C152,R875\\r\\nL158,C152,R875\\r\\nL162,C152,R875\\r\\nL164,C152,R875\\r\\nL166,C152,R875\\r\\nL168,C152,R875\\r\\nL587"
counter = 0
tekst = ""

while(True):
    try:
        if counter > 15:
            counter = 0
            #print("You pressed p")
            meetingen = tekst.split("\\r\\n")
            #print(meetingen)
            index = 0
            for item in meetingen:
                meetingen[index] = (item.split(", "))
                #print(item)
                index = index + 1
                #print(item)
            #print(meetingen)
            finaalmeetingen =[]

            for item in meetingen:
                for items in item:
                    #print(items)
                    finaalmeetingen.append(items.split(","))
                index = 0
                subindex = 0
                #print(finaalmeetingen)
            delete = False
            for items in meetingen:
                #print(items)
                for item in items:
                    #print(item)
                    #print(index)
                    if "'b'" in item:
                        meetingen[index][subindex] = str(item).replace("'b'", "")
                       #print("'b' is in")
                       #print()
                       #print(meetingen[index][subindex])
                       #print()
                    if "L" in item :
                        meetingen[index][subindex] = str(item).replace("L", "")
                    elif "C" in item :
                        meetingen[index][subindex] = str(item).replace("C", "")
                    elif "R" in item :
                        meetingen[index][subindex] = str(item).replace("R", "")
                    else:
                        #delete if not found L C R
                        #print("pop")
                        delete = True
                    subindex = subindex + 1
                   #print(subindex)
                   #print(index)
                #print("before delete")

                if delete == True or subindex < 2:
                    #print("delete")
                    #print(meetingen[index])
                    meetingen.pop(index)
                    index = index -1
                    #print("pop")
                    delete = False
                subindex = 0
                index = index + 1
                #print("after delete")

            index = 0
            subindex = 0

            for items in meetingen:
                for item in items:
                   #print(item)
                    if "'b'" in item:
                        meetingen[index][subindex] = str(item).replace("'b'", "")
                    if "'" in item:
                       #print("b found")
                       #print(f"index: {index}, subindex:{subindex}")
                       #print(meetingen[index][subindex])
                        meetingen[index][subindex] = str(item).replace("'", "")
                       #print(meetingen[index][subindex])
                    if "b" in item:
                        meetingen[index][subindex] = str(item).replace("b", "")
                    if "C" in item:
                        meetingen[index][subindex] = str(item).replace("C", "")
                    if "R" in item:
                        meetingen[index][subindex] = str(item).replace("R", "")
                    if "L" in item:
                        meetingen[index][subindex] = str(item).replace("L", "")
                    subindex = subindex + 1
                subindex = 0
                index = index + 1

            
            index = 0
            subindex = 0
            for items in meetingen:
                for item in items:
                    if "'" in item:
                        meetingen[index][subindex] = str(item).replace("'", "")
                    subindex = subindex + 1
                subindex = 0
                index = index + 1

            meetingen.pop()            
            #print(meetingen)
            #x = range(len(meetingen))
            y1 = []
            y2 = []
            y3 = []
            y4 = []

            #print(meetingen)
            for items in meetingen:
                #print(items[0])
                try:
                    y1.append(int(items[0]))
                    y2.append(int(items[1]))
                    y3.append(int(items[2]))
                    y4.append(450)
                except ValueError:
                    continue
            x = range(len(y1))
            #print(x)
            #print(y1)
            print("done")
            #y1.sort()
            plt.plot(x,y1,label="left")
            plt.plot(x,y2,label="center")
            plt.plot(x,y3,label="right")
            plt.plot(x,y4,label="detect")
            plt.legend()
            plt.show()
            #print(meetingen)
            break
        else:
            #print("collect")
            tekst = tekst + str(ser.read(200))
            counter = counter + 1
    except KeyboardInterrupt:
        #ophalen van de seriële monitor en bufferen
        ser.close()
        break
    