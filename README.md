-----------------------------------------------------------------
#3D Data Acquisition and Registration using Opposing Kinects#
-----------------------------------------------------------------
<p align="center">
  <img src="https://cloud.githubusercontent.com/assets/22081195/18795655/7956496a-81bd-11e6-877b-8082c21ae4f2.gif" width=600>
</p>

##Introduction
This is an open source implementation of **"3D data acquisition and registration using two opposing Kinects"** [1]. This system has been designed for acquiring and recording RGB, depth and skeleton data frames of two Kinects, and registering their RGB point clouds into a joint coordinate system.

To make users life easier, we have adapted the code for either a single Kinct configuration or the double Kinect configurations.

**If you use any form of this source code in your research, kindly cite [1].**

##[Single Kinect Data Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Single_Kinect)
This application is able to acquire, visualise (on-line) and record RGB, depth and skeleton data frames at 30fps and provides their Meta data which can be used to synchronise RGB, depth and body data. This is a Windows form-based application and completely implemented in C++ using Microsoft Visual Studio 2012. We have used third party libraries which are explained in **Dependencies** section. The code, compilation instructions, and data types and specifications have been explained in the related sub-repository.


##[Double Opposing Kinect Data Acquisition and Registration](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects)
This system has been developed to calibrate two opposing Kinects V2 RGBD sensors using an optical approach and register their point clouds to a joint space [1]. It contains calibration, acquisition and registration parts and has been implemented in C++ (Microsoft Visual Studio 2012) and Matlab. We have also used third party libraries explained in Dependencies section. Compilation instructions and directions have been mentioned in the related sub-repository.

Unlike other approaches which use  Kinect SDK built-in functions and generate RGB point cloud only for on-line streams (it means Kinect needs to be connected!), our system is able to generate and align RGB point clouds off-line, using pre-recorded RGB and depth data frames. This allows to reconstruct RGB point cloud of a dynamic object at _30fps_ consistent rate, which could be important for sensitive applications, e.g. medical recordings.

According to Kinect for Windows SDK 2.0, individual machines are required for each separate Kinect V2 device. 
Although other libraries such as [libfreenect2](https://github.com/OpenKinect/libfreenect2) allows to connect two devices to a powerful machine with separate USB3 buses, it decreases the frame rate and it also does not provide the body skeleton data, which could be necessary for some applications. Therefore, the system uses two Windows machines which have been locally connected via TCP/IP protocol. Machines system time are synchronised using NTP.

##Dependencies
The system requires the following libraries to perform:
+ [Kinect for Windows SDK 2.0](https://www.microsoft.com/en-gb/download/details.aspx?id=44561)
+ [Intel Threading Building Blocks](https://www.threadingbuildingblocks.org/software-release/tbb4320140724oss)
+ [OpenCV](https://github.com/opencv/opencv)

##License
This code is licensed under MIT license, which means you can modify and use for any purpose. But, the third party libraries have different licenses.
+ Kinect for Windows SDK 2.0 (Free Commercial License)
+ Intel Threading Building Blocks (GPLv2 License)
+ OpenCV (BSD License)


##Do You Need Help?
Compilation and running directions of the source codes have been explained in details, in their dedicated sub-repositories. Further, the system methodology has been illustrated in our paper [1]. But, if you have any question or suggestion, please feel free to contact me by email: vahid [dot] soleimani [at] bristol [dot] ac [dot] uk .


##Publication
If you use any form of this source code in your research, kindly cite the following paper.

[1] V. Soleimani, M. Mirmehdi, D.Damen, S. Hannuna, M. Camplani, "3D Data Acquisition and Registration Using Two Opposing Kinects", _International Conference on 3D Vision_, Stanford, USA, October 2016.
