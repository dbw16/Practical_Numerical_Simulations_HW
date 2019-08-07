import numpy as np
import matplotlib.pyplot as plt
'''
#this is used to graph the 11 results vs time 
x ,t = np.loadtxt("file.txt", unpack=True)
plt.title("Soultions to x''= -x^3 t exp(-x^2/2) ")
plt.xlabel("t")
plt.ylabel("x(t)")
plt.plot(t,x,".",ms=2,label="soultions")
plt.grid()
plt.legend(loc="best")
plt.savefig("hw2_1_sols.pdf")


#the bellow code can be used to graph the resuclt vs c in order to find the 11 soultions 
#however i implented code to do this instead

x , t = np.loadtxt("file.txt", unpack=True)
print len(t)
print len(x)
plt.grid()
plt.plot(t,x,".",ms=2,)
plt.savefig("hw2_1.pdf")
'''


#this is used to genragte the planet digram 
import numpy as np
import matplotlib.pyplot as plt

p1x,p1y,p2x,p2y,p3x,p3y,p4x,p4y = np.loadtxt("hw2_2.txt", unpack=True)
plt.title("Planets trajectories  ")
plt.xlabel("x")
plt.ylabel("y")
plt.plot(p1x,p1y,"-",label="Planet 1")
plt.plot(p2x,p2y,"-",label="Planet 2")
plt.plot(p3x,p3y,"-",label="Planet 3")
plt.plot(p4x,p4y,"-",label="Planet 4")
plt.legend(loc="best")
plt.grid()
plt.savefig("hw2_2.pdf")

