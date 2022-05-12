#!/usr/bin/python
from csv import reader
import matplotlib.pyplot as plt

fileName = "links_zonder_duim"

file = open("Software_Opstelling/" + fileName + ".csv", 'r', newline='')

data = reader(file, delimiter=',')

left=[]
center=[]
right=[]

for items in data:
    if not("LEFT" in items[0]):
        left.append(int(items[0]))
        center.append(int(items[1]))
        right.append(int(items[2]))

#aanmaken x as
x = range(len(left))

plt.plot(x,left,label="left")
plt.plot(x,center,label="center")
plt.plot(x,right,label="right")
plt.legend()
plt.show()