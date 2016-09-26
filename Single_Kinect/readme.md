-------------------------------------
#Single Kinect Data Acquisition
-------------------------------------
![rgb_depth_skel_sel](https://cloud.githubusercontent.com/assets/22081195/18792861/20a91bf6-81b0-11e6-9d02-8df6653204bd.png)

##Introduction
This application is able to acquire, visualise (on-line) and record RGB, depth and skeleton data frames at 30fps and provides RGB, depth and body Meta data which can be used to synchronise RGB, depth and body data. It is a Windows form-based application and completely implemented in C++ using Microsoft Visual Studio 2012. We have also used third party libraries which are explained in Dependencies section.
 
If you use any form of this source code in your research, kindly cite [1].

<p align="center">
  <img src="https://cloud.githubusercontent.com/assets/22081195/18792882/3f01c72e-81b0-11e6-864e-0967ac98120f.png" width=300>
</p>
##Compilation and Running
The required hardware and software resources, necessary libraries and their dependencies establishment, the application specification and details, and format of its output data are described in:


<h3 align="center">Click on the image to open the pdf </h3>
[![ttt](https://cloud.githubusercontent.com/assets/22081195/18803669/02f6c34e-81ea-11e6-8828-631dcd0e485c.png)](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/files/489895/How_it_works.pdf)


##Dependencies
The system requires the following libraries to perform:
+ [Kinect for Windows SDK 2.0](https://www.microsoft.com/en-gb/download/details.aspx?id=44561)
+ [Intel Threading Building Blocks](https://www.threadingbuildingblocks.org/software-release/tbb4320140724oss)
+ [OpenCV](https://github.com/opencv/opencv)

##License
This code is licensed under MIT license, which mean you can modify and use for any purposes. But, the third party libraries have different licenses.
+ Kinect for Windows SDK 2.0 (Free Commercial License)
+ Intel Threading Building Blocks (GPLv2 License)
+ OpenCV (BSD License)


##Do You Need Help?
Source codes compilation and running directions have been explained in details, in their dedicated sub-repositories. Further, the system methodology has been illustrated in our paper [1]. But, if you have any question or suggestion, please feel free to contact me by email: vahid [dot] soleimani [at] bristol [dot] ac [dot] uk .


##Publication
If you use any form of this source code in your research, kindly cite the following paper.

[1] V. Soleimani, M. Mirmehdi, D.Damen, S. Hannuna, M. Camplani, "3D Data Acquisition and Registration Using Two Opposing Kinects", _International Conference on 3D Vision_, Stanford, USA, October 2016.



