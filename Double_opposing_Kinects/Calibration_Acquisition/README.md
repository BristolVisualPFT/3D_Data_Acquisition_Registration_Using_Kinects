-------------------------------------
# Kinect Calibration Data Acquisition #
-------------------------------------
<p align="center">
  <img src="https://cloud.githubusercontent.com/assets/22081195/18998120/23018c92-872f-11e6-8609-5eeb6290aa98.png" width=400>
  <img src="https://cloud.githubusercontent.com/assets/22081195/18998130/29c86442-872f-11e6-9699-09c03a1f3faf.png" width=400>
  <img src="https://cloud.githubusercontent.com/assets/22081195/18998140/2dd54870-872f-11e6-9205-b0c686ede193.png" width=700>
</p>

## Introduction
This application is used to acquire, visualise (on-line) and record RGB, infrared, depth and skeleton data frames at _30fps_ and provides RGB, infrared, depth and body Meta data which can be used to synchronise RGB, depth and body data. It is very similar to the **[Single Kinect Data Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Single_Kinect)**, however, it can also acquire the infrared data, which must be used for estimating the calibration parameters. This is a Windows form-based application and completely implemented in C++ using Microsoft Visual Studio 2012. We have also used third party libraries which are explained in **Dependencies** Section.
 
**If you use any form of this source code in your research, kindly cite [1].**

<p align="center">
  <img src="https://cloud.githubusercontent.com/assets/22081195/18997867/33005e9e-872e-11e6-9816-73aef75130bf.png" width=300>
</p>

## Compilation and Running
The required hardware and software resources, necessary libraries and their dependencies establishment, the application specification and details, and format of its output data are described in the following guidance document.



<h3 align="center"> 
   <img src="https://cloud.githubusercontent.com/assets/22081195/18995638/f2690506-8724-11e6-9bb2-3f2028f5bb49.png" width=30>
   Click on the image to open the guidance document
   <img src="https://cloud.githubusercontent.com/assets/22081195/18995638/f2690506-8724-11e6-9bb2-3f2028f5bb49.png" width=30> 
</h3>
[![ttt](https://cloud.githubusercontent.com/assets/22081195/18998636/6e0b0c16-8731-11e6-8157-286fd9beb8e9.png)](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/files/503372/KinectCalibration_How_does_it_work.pdf)


## Dependencies
The system requires the following libraries to perform:
+ [Kinect for Windows SDK 2.0](https://www.microsoft.com/en-gb/download/details.aspx?id=44561)
+ [Intel Threading Building Blocks](https://www.threadingbuildingblocks.org/software-release/tbb4320140724oss)
+ [OpenCV](https://github.com/opencv/opencv)

## License
This code is licensed under MIT license, which means you can modify and use for any purposes. But, the third party libraries have different licenses.
+ Kinect for Windows SDK 2.0 (Free Commercial License)
+ Intel Threading Building Blocks (GPLv2 License)
+ OpenCV (BSD License)


## Do You Need Help?
Compilation and running directions of the source codes have been explained in details, in guidance document under **Compilation and Running** Section. Further, the system methodology has been explained in our paper [1]. But, if you have any question or suggestion, please feel free to contact me by email: vahid [dot] soleimani [at] bristol [dot] ac [dot] uk .


## Publication
If you use any form of this source code in your research, kindly cite the following paper.

[1] V. Soleimani, M. Mirmehdi, D.Damen, S. Hannuna, M. Camplani, "3D Data Acquisition and Registration Using Two Opposing Kinects", _International Conference on 3D Vision_, Stanford, USA, October 2016.

<p align="center">
  <img src="https://cloud.githubusercontent.com/assets/22081195/19785457/560e5e72-9c91-11e6-9e0b-de685185675a.png" width=800>
</p>


