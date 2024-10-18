import numpy as np 
import matplotlib.pyplot as plt 
from mpl_toolkits.mplot3d import Axes3D

npz = np.load('lidar_decoded_data.npz')

x = npz['arr_0']                                        

y = npz['arr_1'] 

z = npz['arr_2'] 

fig = plt.figure()
 
# syntax for 3-D projection
ax = fig.add_subplot(111, projection='3d')
ax.scatter(x, y, z, c='blue', marker='o')

ax.set_xlabel('X Axis')
ax.set_ylabel('Y Axis')
ax.set_zlabel('Z Axis')
ax.set_title('3D Scatter Plot')
plt.show()