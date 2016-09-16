-----------------------------------------------------------------
# 3D Data Acquisiton and Registration using Multiple Kinects #
-----------------------------------------------------------------

## Introduction
This is an open source implementaion of "3D data acquisition and registration using two opposing Kinects" [1]. This system has been designed for acquiring and recording RGB, depth and skeleton data frames of two Kinects and register their RGB point cloud into a joint coordinate system.

To make the users life easier, two source codes adapted to be used with a single Kinect or double Kinect configurations.

## [Single Kinect Data Acquisition](https://github.com/BristolVisualPFT/Double_Kinect_3D_Data_Acquisition_Registration/tree/master/Single_Kinect_Data_Acquisition)
This is a windows form based application and completely implemented in C++ using Microsft Visual Studio 2012. We have also used third party libraries which are exaplined in Dependencies section. This application is able to acquire, visualise (on-line) and record RGB, depth and skeleton data frames at 30fps and provide their corresponding metadata for synchronization. The code, and the data types and specifications have been explained in the related sub-repository.


##[Double Opposing Kinect Data Acquisition and Registration](https://github.com/BristolVisualPFT/Double_Kinect_3D_Data_Acquisition_Registration/tree/master/Double_Kinect_Data_Acquisition_Registration)
This system has been developed to calibrate two opposing Kinects V2 using an optical approach and register their point clouds to a joint space [1]. It conrains calibration, acquisition and registeration parts and has been implemented in C++ (Microsft Visual Studio 2012) and Matlab. We have also used third party libraries exaplined in Dependencies section.

Unlike other approaches which use  Kinect for Windows SDK built-in functions and can generate RGB point cloud only for on-line streams (Kinect deends to be connected), our system is able to generate and align RGB point clouds off-line, using pre-recorded RGB and depth data frames. This allows to reconstruct RGBD point cloud of a dynamic object at consistant 30fps, which could be important for sensitive applications such as respiratory monitoring.

According to Kinect for Windows SDK 2.0, individual machines are required for each separate Kinect V2 device. 
Although libfreenect2 allows to connect two devices to a powerful machine with separate USB3 buses, it decreases the frame  rate and it does not also provide the body skeleton data data, which could be necassry for some applications. Therefore, the system requires two Windows machine which has been localy connected via TCP/IP protocol. Machine system times are synchronised using NTP timing protocol.

# Requirements


