#!/usr/bin/python
from datetime import date, datetime
from csv import writer
import serial



testData= [["L512","C402","R854"],["L512","C402","R854"],["L512","C402","R854"],["L512","C400","R854"],["L512","C402","R858"],["L512","C402","R864"],["L512","C402","R874"]]

headerCSV = ["LEFT","CENTER","RIGHT"]

#maak de timestamp
timestamp = f"{date.today()}_{datetime.now().hour}{datetime.now().minute}{datetime.now().second}"
print(timestamp)

#open (maak) het bestand 
file = open(("logs/data_"+timestamp), 'w', newline='')

#kopel het bestand aan de cvs schrijver
schrijf = writer(file)

#header importeren
schrijf.writerow(headerCSV)
schrijf.writerows(testData)

#bestand sluiten
file.close()