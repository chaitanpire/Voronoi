import matplotlib.pyplot as plt
import numpy as np
plt.xlim(-200, 200)
plt.ylim(-200, 200)
with open('out.txt', 'r') as f:
    #make line starting at x1, y1 given in even numbered line and ending at x2, y2 given on next odd line
    
    

    lines = f.readlines()
    #reverse the list
    lines = lines[::-1]
    
    for i in range(len(lines)):
        if "End of Event" in lines[i]:
            lines = lines[:i]
            break
    #remove the last 2 lines
    lines = lines[:-2]
    lines = lines[::-1]
    
    edges = lines

    x_coords = []
    y_coords = []
    for i in range(0, len(edges), 2):
        x1, y1 = map(float, edges[i].split())
        x2, y2 = map(float, edges[i+1].split())
        x_coords.extend([x1, x2])
        y_coords.extend([y1, y2])
    
    # Plot each edge with a random color
    for i in range(0, len(x_coords)-8, 2):
        color = np.random.rand(3,)  # Generate random RGB color
        #avoid white colour
        while abs(color[0] - color[1]) < 0.3  and abs(color[2] - color[1]) < 0.3 :
            color = np.random.rand(3,)
        plt.plot([x_coords[i], x_coords[i+1]], [y_coords[i], y_coords[i+1]], color=color)
    
    # Set the last four lines to black
    for i in range(len(x_coords) - 8, len(x_coords) - 1, 2):
        plt.plot([x_coords[i], x_coords[i+1]], [y_coords[i], y_coords[i+1]], color='black', marker='o', markersize=3)
    
with open('in.txt', 'r') as f:
    lines = f.readlines()
    for line in lines[1:]:
        x, y = line.split()
        plt.plot(float(x), float(y), 'bo')
#bound x and y axis

plt.axis("equal")
plt.show()

