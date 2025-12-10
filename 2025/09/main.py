import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("input.dat", delimiter=',')
plt.plot(data[:,0], data[:,1])
plt.show()
