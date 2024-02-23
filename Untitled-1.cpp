//Generate python script to plot lines
//lines will in the form of x1 y1 /n x2 y2 /n
//take input from file out.txt
//output to file plot.py
//write code in python
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

with open('out.txt', 'r') as f:
    lines = f.readlines()
    x = []
    y = []
    for line in lines:
        x1, y1, x2, y2 = map(float, line.split())
        x.append(x1)
        x.append(x2)
        y.append(y1)
        y.append(y2)
        plt.plot(x, y, 'ro-', label='line 1')
        x = []
        y = []

plt.show()
