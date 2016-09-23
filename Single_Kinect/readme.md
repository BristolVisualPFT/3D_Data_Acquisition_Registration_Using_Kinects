-------------------------------------
#Single Kinect Data Acquisition
-------------------------------------
![rgb_depth_skel_sel](https://cloud.githubusercontent.com/assets/22081195/18792861/20a91bf6-81b0-11e6-9d02-8df6653204bd.png)


This application is able to acquire, visualise (on-line) and record RGB, depth and skeleton data frames at 30fps and provide their corresponding Meta data which can be used to synchronise them. It is a Windows form-based application and completely implemented in C++ using Microsoft Visual Studio 2012. We have also used third party libraries which are explained in Dependencies section.
 
If you use any form of this source code in your research, kindly cite [1].

##How does it work?
The required hardware and software resources, necessary libraries and their dependencies establishment, the application specification and details and format of its output data are described in:

[How does it work?](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/files/489895/How_it_works.pdf)
<p align="center">
  <img src="https://cloud.githubusercontent.com/assets/22081195/18792882/3f01c72e-81b0-11e6-864e-0967ac98120f.png" width=300>
</p>


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
The system methodology has been described in our paper [1]. But, if you have any question or suggestion, please feel free to contact me by email: vahid [dot] soleimani [at] bristol [dot] ac [dot] uk


##Publication
If you use any form of this source code in your research, kindly cite the following paper.

[1] V. Soleimani, M. Mirmehdi, D.Damen, S. Hannuna, M. Camplani, "3D Data Acquisition and Registration Using Two Opposing Kinects", _International Conference on 3D Vision_, Stanford, USA, October 2016.



