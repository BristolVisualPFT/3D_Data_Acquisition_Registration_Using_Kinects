-------------------------------------
#Kinect Server Data Acquisition
-------------------------------------
![rgb_depth_skel_sel](https://cloud.githubusercontent.com/assets/22081195/18792861/20a91bf6-81b0-11e6-9d02-8df6653204bd.png)

##Introduction

This is a modified version of  **[Single Kinect Data Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Single_Kinect)** software, which has been adapted to communicate with and instruct **[Client Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Client_Acquisition)** software through a TCP/IP local network. This software has been dsigned to used along with the **[Client Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Client_Acquisition)** and cannot be used on its own. It is able to acquire, visualise (on-line) and record RGB, depth and skeleton data frames at _30fps_ and provides RGB, depth and body Meta data. The software features and its output specifications along with the compilation directions have been explained in the guidance document under **Compilation and Running** Section. This is a Windows form-based application and completely implemented in C++ using Microsoft Visual Studio 2012. We have also used third party libraries which are explained in **Dependencies** Section.
 
**If you use any form of this source code in your research, kindly cite [1].**

<p align="center">
  <img src="https://cloud.githubusercontent.com/assets/22081195/18999485/cb3657e8-8735-11e6-93e1-fdac403ace92.png" width=300>
</p>
##Compilation and Running
The required hardware and software resources, necessary libraries and their dependencies establishment, the application specification and details, and format of its output data are described in:



<h3 align="center"> 
   <img src="https://cloud.githubusercontent.com/assets/22081195/18995638/f2690506-8724-11e6-9bb2-3f2028f5bb49.png" width=30>
   Click on the image to open the guidance document
   <img src="https://cloud.githubusercontent.com/assets/22081195/18995638/f2690506-8724-11e6-9bb2-3f2028f5bb49.png" width=30> 
</h3>
[![ttt](https://cloud.githubusercontent.com/assets/22081195/18999490/ced6982c-8735-11e6-836c-1110b4bdc2c9.png)](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/files/503428/ServerAcquisition_How_does_it_work.pdf)


##Dependencies
The system requires the following libraries to perform:
+ [Kinect for Windows SDK 2.0](https://www.microsoft.com/en-gb/download/details.aspx?id=44561)
+ [Intel Threading Building Blocks](https://www.threadingbuildingblocks.org/software-release/tbb4320140724oss)
+ [OpenCV](https://github.com/opencv/opencv)

##License
This code is licensed under MIT license, which means you can modify and use for any purposes. But, the third party libraries have different licenses.
+ Kinect for Windows SDK 2.0 (Free Commercial License)
+ Intel Threading Building Blocks (GPLv2 License)
+ OpenCV (BSD License)


##Do You Need Help?
Compilation and running directions of the source codes have been explained in details, in guidance document under **Compilation and Running** Section. Further, the system methodology has been explained in our paper [1]. But, if you have any question or suggestion, please feel free to contact me by email: vahid [dot] soleimani [at] bristol [dot] ac [dot] uk .


##Publication
If you use any form of this source code in your research, kindly cite the following paper.

[1] V. Soleimani, M. Mirmehdi, D.Damen, S. Hannuna, M. Camplani, "3D Data Acquisition and Registration Using Two Opposing Kinects", _International Conference on 3D Vision_, Stanford, USA, October 2016.


