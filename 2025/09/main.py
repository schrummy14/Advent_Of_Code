#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import sys

# data = np.loadtxt("example.dat", delimiter=',')
data = np.loadtxt("input.dat", delimiter=',')
data = np.vstack((data,data[0,:]))
# mx = np.mean(data[:,0])
# my = np.mean(data[:,1])
# mr = 0
# for d in data:
#     rx = d[0]-mx
#     ry = d[1]-my
#     rr = np.sqrt(rx*rx + ry*ry)
#     if rr > mr:
#         mr = rr
# print(mx, my, mr)
# plt.plot(mx,my,'k*')
# circle1 = plt.Circle((mx,my), mr)
# plt.gca().add_patch(circle1)
plt.plot(data[:,0], data[:,1], 'r*-')
# plt.plot(mx,my,'k*')
# plt.ylim(0,np.max(data[:,1]))
# plt.xlim(0,np.max(data[:,0]))

if len(sys.argv) > 1:
    points = [ int(x) for x in sys.argv[1:]]
    k = 0
    while k < len(points):
        x1 = min(points[k+0], points[k+2])
        x2 = max(points[k+0], points[k+2])
        y1 = min(points[k+1], points[k+3])
        y2 = max(points[k+1], points[k+3])
        plt.plot([x1, x2, x2, x1, x1], [y1, y1, y2, y2, y1])
        k += 4

plt.show()
