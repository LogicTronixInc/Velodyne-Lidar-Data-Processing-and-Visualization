#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "PacketDriver.h"
#include "PacketDecoder.h"
#include <boost/shared_ptr.hpp>
#include<deque>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void showLidarTopview(vector<LidarPoint> lidarPoints)
{
    cv::Size worldSize(8.0, 8.0); // width and height of sensor field in m
    cv::Size imageSize(1000, 1000); // corresponding top view image in pixel

    // create topview image
    cv::Mat topviewImg(imageSize, CV_8UC3, cv::Scalar(0, 0, 0));
    float max_ref=0;
    // plot Lidar points into image
    for (auto it = lidarPoints.begin(); it != lidarPoints.end(); ++it)
    {
        float xw = (*it).x; // world position in m with x facing forward from sensor
        float yw = (*it).y; // world position in m with y facing left from sensor

        int y = (-xw * imageSize.height / worldSize.height) + imageSize.height / 2;
        int x = (-yw * imageSize.height / worldSize.height) + imageSize.width / 2;

       

//        cv::circle(topviewImg, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);
        
        // TODO: 
        // 1. Change the color of the Lidar points such that 
        // X=0.0m corresponds to red while X=20.0m is shown as green.
        // 2. Remove all Lidar points on the road surface while preserving 
        // measurements on the obstacles in the scene.
        float zw=(*it).z;
        // cout << "(" << xw << " , " << yw << " , " << zw << " ),  " ;
        // cout << "(" << x << " , " << y << " , " << zw << " ),  " ;
        if(zw>-1.40){
            float val=it->x;
            float reflectivity=it->r; // reflectivity of lidar point
            float maxval =worldSize.height;
            int red = min(255,(int)(255*abs((val-maxval)/maxval)));
            int green = min(255,(int)(255*(1-abs((val-maxval)/maxval))));
            int thickness=reflectivity>0.5?-1:1; // -1:ellipse arc outline 1:filled ellipse sector
            cv::circle(topviewImg,cv::Point(x,y),1,cv::Scalar(0,green,red),thickness);
            // cout << "in image update" << endl;
            cv::circle(topviewImg,cv::Point(500,500),5,cv::Scalar(0,green,red),thickness);

        }
    }
    // cout << endl ; 
    // cout<<"max reflectivity: "<<max_ref<<endl;
    // plot distance markers
    float lineSpacing = 2.0; // gap between distance markers
    int nMarkers = floor(worldSize.height / lineSpacing);
    for (size_t i = 0; i < nMarkers; ++i)
    {
        int y = (-(i * lineSpacing) * imageSize.height / worldSize.height) + imageSize.height;
        cv::line(topviewImg, cv::Point(0, y), cv::Point(imageSize.width, y), cv::Scalar(255, 0, 0));
    }

    // display image
    string windowName = "Top-View Perspective of LiDAR data";
    // cv::namedWindow(windowName, 2);
    cv::imshow(windowName, topviewImg);
    cv::waitKey(10); // wait for key to be pressed
}

int main()
{
  PacketDriver driver;
  driver.InitPacketDriver(DATA_PORT);
  PacketDecoder decoder;
  decoder.SetCorrectionsFile("../16db.xml");

  std::string* data = new std::string();
  unsigned int* dataLength = new unsigned int();
  std::deque<PacketDecoder::HDLFrame> frames;
  PacketDecoder::HDLFrame latest_frame;
  while (true) {
    driver.GetPacket(data, dataLength);
    decoder.DecodePacket(data, dataLength);
    frames = decoder.GetFrames();
    if (decoder.GetLatestFrame(&latest_frame)) {
      // std::cout << "Number of points: " << latest_frame.x.size() << std::endl;

      //printing x coordinates
      //  cout << std::endl;
      // cout << " x coordinates : " ;
      // for (const auto& lidar_point : latest_frame.lidar_points){
      //   std::cout << lidar_point.x << ", ";
      // }
      // cout << std::endl;
      //  cout << std::endl;

       showLidarTopview(latest_frame.lidar_points);

      // //printing x coordinates
      //  cout << std::endl;
      // cout << " x coordinates : " ;
      // for (const auto& x : latest_frame.x){
      //   std::cout << x << ", ";
      // }
      // cout << std::endl;
      //  cout << std::endl;

      // //printing y coordinates
      // cout << " y coordinates : " ;
      // for (const auto& y : latest_frame.y){
      //   std::cout << y << ", ";
      // }
      // cout << std::endl;
      //  cout << std::endl;

      // //printing z coordinates
      // cout << " z coordinates : " ;
      // for (const auto& z : latest_frame.z){
      //   std::cout << z << ", ";
      // }
      // cout << std::endl;
      //  cout << std::endl;

      // //printing intensity
      // cout << " intensity :  " ;
      // for (const auto& i : latest_frame.intensity){
      //   std::cout << (int)i << ", ";
      // }
      // cout << std::endl;
      //  cout << std::endl;

      // //printing intensity
      // cout << " Laser ID :  " ;
      // for (const auto& id : latest_frame.laser_id){
      //   std::cout << (int)id << ", ";
      // }
      // cout << std::endl;
      //  cout << std::endl;

     

      // //printing azimuth
      // cout << " Azimuth :  " ;
      // for (const auto& az : latest_frame.azimuth){
      //   std::cout << az << ", ";
      // }
      // cout << std::endl;
      //  cout << std::endl;

      // std::cout << "Laser ID: " << latest_frame.laser_id.size() << std::endl;
    }
  }

  return 0;
}
