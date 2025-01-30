# Velodyne-Lidar-Data-Processing-and-Visualization
This repositiory is for bringing up Velodyne VLP 16 LIdar and Visualization in Linux system with native C++ libraries.

# Building and Testing the Lidar Viewer application
Get the source from github : https://github.com/LogicTronixInc/Velodyne-Lidar-Data-Processing-and-Visualization.git 

* In `src` folder create the build directory:
```
mkdir build
```

* Change to build directory and run cmake and then run make
```
cd build
cmake ..
make
```
* This will create `test_PacketDecoder` app along with libraries in the build directory.

* Now connect the Lidar to the host machine through ethernet and setup the host PC network to same domain as Lidar.

* Now run the `test_PacketDecoder` app to view the Lidar data