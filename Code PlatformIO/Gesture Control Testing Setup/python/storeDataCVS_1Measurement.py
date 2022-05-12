#!/usr/bin/python
from datetime import date, datetime
from csv import writer
import serial

try:
    _1Measurement = 8
    amountReadings = 600
    
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
    #print(tekst)

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
        if len(items) < 2:
            testData.pop(index)
        index = index + 1
    #print(testData)
    meetingen.pop()
    #testData= [["L512","C402","R854"],["L512","C402","R854"],["L512","C402","R854"],["L512","C400","R854"],["L512","C402","R858"],["L512","C402","R864"],["L512","C402","R874"]]
    #print(meetingen)
    #header van csv aanmaken
    headerCSV = ["DISTANCE", "STATUS"]

    #L,C en R weghalen 
    #print(len(testData))

    #print(testData)
    #maak de timestamp
    timestamp = f"{date.today()}_{datetime.now().hour}{datetime.now().minute}{datetime.now().second}"
    ##print(timestamp)

    #open (maak) het bestand 
    file = open(("test/data_"+timestamp+".csv"), 'w', newline='')

    #kopel het bestand aan de cvs schrijver
    schrijf = writer(file)

    #header importeren
    schrijf.writerow(headerCSV)
    schrijf.writerows(testData)

    #bestand sluiten
    file.close()

except KeyboardInterrupt:
    file.close()
    #ser.close()