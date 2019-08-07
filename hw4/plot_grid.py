import numpy as np
import matplotlib.pyplot as plt


for beta in np.arange(50,150,10):
	grid = np.transpose(np.loadtxt("grid_beta_{:.0f}.dat".format(beta), unpack=True))

	for y in range(len(grid)):
		for x in range(len(grid)):
			if (grid[y][x] == 0):
				plt.plot(x+1,y+1,"r.")
			if (grid[y][x] == 1):
				plt.plot(x+1,y+1,"b.")
			if (grid[y][x] == 2):
				plt.plot(x+1,y+1,"g.")
			if (grid[y][x] == 3):
				plt.plot(x+1,y+1,"c.")
			if (grid[y][x] == 4):
				plt.plot(x+1,y+1,"k.")
	plt.grid()
	plt.title("BETA = {:.2f}".format(beta/100.))
	plt.savefig("BETA={:.2f}.png".format(beta/100.))


'''

y = np.loadtxt("q_3.dat", unpack=True)
plt.plot(np.arange(.5,1.501,.01),y,"bx",label ="q=3")
plt.plot(np.arange(.5,1.501,.01),y,"b")


y = np.loadtxt("q_4.dat", unpack=True)
plt.plot(np.arange(.5,1.501,.01),y, "gx",label ="q=4")
plt.plot(np.arange(.5,1.501,.01),y,"g")


y = np.loadtxt("q_5.dat", unpack=True)
plt.plot(np.arange(.5,1.501,.01),y,"rx", label ="q=5")
plt.plot(np.arange(.5,1.501,.01),y,"r")

plt.xlabel("beta")
plt.ylabel("<M>")
plt.legend(loc="best")
plt.show()
'''
