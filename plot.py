import matplotlib.pyplot as plt
import numpy as np
import sys
import os

with open('out.txt', 'r') as f:
    #make line starting at x1, y1 given in even numbered line and ending at x2, y2 given on next odd line
    lines = f.readlines()
    for i in range(0, len(lines), 2):
        x1, y1 = lines[i].split()
        x2, y2 = lines[i+1].split()
        plt.plot([float(x1), float(x2)], [float(y1), float(y2)], 'ro-')
    #now plot the points from in.txt ingnore the first line
with open('in.txt', 'r') as f:
    lines = f.readlines()
    for line in lines[1:]:
        x, y = line.split()
        plt.plot(float(x), float(y), 'bo')
with open('out2.txt', 'r') as f:
    lines = f.readlines()
    for line in lines[:]:
        x, y = line.split()
        plt.plot(float(x), float(y), 'ro')
#bound x and y axis
plt.xlim(-20, 20)
plt.ylim(-20, 20)
plt.axis("equal")
plt.show()

