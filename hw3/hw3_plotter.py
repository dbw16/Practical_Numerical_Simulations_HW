import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from scipy import interpolate
import pandas as pd
from scipy.interpolate import griddata

'''
x,y,z = np.loadtxt("hw3_2.txt", unpack=True)






values=np.arange(-1,1,.001)
fig = plt.figure()
ax = fig.gca(projection='3d')
surf = ax.scatter(x, y, z, cmap="hot", marker="x")


plt.show()
'''

x = np.loadtxt("hw3_1.dat", unpack=True)
plt.plot(np.arange(1.2,2,.05),x)
plt.ylabel("n")
plt.xlabel("omega")

plt.show()
