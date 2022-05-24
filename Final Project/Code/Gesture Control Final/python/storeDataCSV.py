#!/usr/bin/python

# Made By Robbe Elsermans
# Dit python script gebruik je wanneer de printf("L%d,C%d,R%d\r\n",waarde1,waarde2,waarde3); plot naar de seriële monitor.

from datetime import date, datetime
from csv import writer
import serial

try:
    _1Measurement = 18
    amountReadings = 1000
    
    #instelling seriële communicatie met poort: COM6 en baudrate: 115200
    ser = serial.Serial("COM6",115200)
    #tekst = "L156,C152,R875\\r\\nL158,C152,R875\\r\\nL162,C152,R875\\r\\nL164,C152,R875\\r\\nL166,C152,R875\\r\\nL168,C152,R875\\r\\nL587"
    
    tekst = ser.read((amountReadings*_1Measurement))
    #print(tekst)
    #decoderen naar string
    tekst = str(tekst.decode())
    #spaties wegwerken
    tekst = tekst.replace(" ","")
    ser.close()
    ##print(tekst)

    #Data splitsen bij de return statement
    meetingen = tekst.split("\r\n")
    #print(meetingen)

    #print(tekst)
    #Data onderverdelen in een array van integers
    testData = []
    for items in meetingen:
        testData.append(items.split(','))
    #De elementen die niet volledig zijn, eruit gooien
    index = 0
    #print(testData)
    for items in testData:
        #print(len(items))
        if len(items) < 3:
            testData.pop(index)
        index = index + 1
    #print(testData)

    #testData= [["L512","C402","R854"],["L512","C402","R854"],["L512","C402","R854"],["L512","C400","R854"],["L512","C402","R858"],["L512","C402","R864"],["L512","C402","R874"]]

    #header van csv aanmaken
    headerCSV = ["LEFT","CENTER","RIGHT"]

    #L,C en R weghalen 
    index = 0
    subindex = 0
    for items in testData:
        for item in items:
            testData[index][subindex] = str(item[1:])
            #print(item[1:(len(item))])
            #print(item)
            #print(subindex)
            ##print(testData[index][subindex])
            subindex = subindex + 1
        subindex = 0
        index = index +1
    subindex = 0
    index = 0

    #print(len(testData))

    #print(testData)
    #maak de timestamp
    timestamp = f"{date.today()}_{datetime.now().hour}{datetime.now().minute}{datetime.now().second}"
    ##print(timestamp)

    #opent (maakt) het bestand 
    file = open(("logs/data_"+timestamp+ ".csv"), 'w', newline='')

    #kopel het bestand aan de cvs schrijver
    schrijf = writer(file)

    #header en waardes wegschrijven
    schrijf.writerow(headerCSV)
    schrijf.writerows(testData)

    #bestand sluiten
    file.close()

except KeyboardInterrupt:
    file.close()
    #ser.close()