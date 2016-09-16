-----------------------------------------------------------------
# 3D Data Acquisiton and Registration using Multiple Kinects #
-----------------------------------------------------------------

## Introduction
This is an open source implementaion of "3D data acquisition and registration using two opposing Kinects" [1]. This system is designed for acquiring and recording RGB, depth and skeleton data frames of two Kinects and register their RGB point cloud into a joint coordinate system.

To make the users life easier, two source codes adapted to be used with a single Kinect or double Kinects configurations.

## [Single Kinect Data Acquisition](https://github.com/BristolVisualPFT/Double_Kinect_3D_Data_Acquisition_Registration/tree/master/Single_Kinect_Data_Acquisition)
This part is a windows form based application and completely implemented in C++ using Microsft Visual Studio 2012. We have also used third party libraries which are exaplined in Dependencies section. This application is capabale of acquiring, on-line visualisation and recording RGB, depth and skeleton data frames and provide their corresponding metadata, which are required for their synchronization. The code and the data types and specifications have been explained in the related sub-repository.


##[Double Opposing Kinects Data Acquisition and Registration](https://github.com/BristolVisualPFT/Double_Kinect_3D_Data_Acquisition_Registration/tree/master/Double_Kinect_Data_Acquisition_Registration)
