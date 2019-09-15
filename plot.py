from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111,projection='3d')

len = np.loadtxt('len.dat',dtype='int')

xx = np.zeros((len,len))
yy = np.zeros((len,len))
z = np.zeros((len,len))

#points on the plane
xx = np.loadtxt('xx.dat',dtype='double')
yy = np.loadtxt('yy.dat',dtype='double')
z = np.loadtxt('z.dat',dtype='double')

P = np.loadtxt('P.dat',dtype='double') #coordinates of the point P
textco = np.loadtxt('textco.dat',dtype='double') #coordinates of the label of the point P

#points on the line
l_p0=np.loadtxt('l_p[0].dat',dtype='double')
l_p1=np.loadtxt('l_p[1].dat',dtype='double')
l_p2=np.loadtxt('l_p[2].dat',dtype='double')

ax.plot_surface(xx, yy, z, color='yellow',alpha=0.8) #plotting the plane
plt.plot(l_p0,l_p1,l_p2,label="Given Line", color='red') #plotting the line

ax.scatter(P[0], P[1], P[2], color='blue') #plotting the point P
ax.text(textco[0], textco[1], textco[2], 'P', color='blue') #plotting the label of the point P

plt.xlabel('$x$');plt.ylabel('$y$')
plt.legend()
plt.grid()
plt.show()