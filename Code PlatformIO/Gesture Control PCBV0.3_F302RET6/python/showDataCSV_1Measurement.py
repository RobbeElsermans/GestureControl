#!/usr/bin/python
from csv import reader
import matplotlib.pyplot as plt

fileName = "data_2022-05-03_122826"

file = open("test/" + fileName + ".csv", 'r', newline='')

data = reader(file, delimiter=',')

distance=[]
status=[]

for items in data:
    if not("DISTANCE" in items[0]):
        distance.append(int(items[0]))
        # if '' in items[1]:
        #     status.append(0)
        #     print(items)
        # else:
        status.append(int(items[1]))

#aanmaken x as
x = range(len(distance))

fig, ax1 = plt.subplots()
l1, = ax1.plot(distance,label="distance",color="blue")
ax1.set_ylabel("distance (mm)")
ax1.set_xlabel("measurement number")
ax2 = ax1.twinx()
l2, = ax2.plot(status,label="status",color="red")
ax2.set_ylabel("status code")

plt.legend(handles=[l1, l2])
plt.show()