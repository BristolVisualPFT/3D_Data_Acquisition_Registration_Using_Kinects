----------------------------------------------
#RGB Point Clouds Alignment and Registration
----------------------------------------------



##Introduction

This package can generate and align RGB point clouds using the pre-recorded RGB and depth data frames recorded by **[Client Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Client_Acquisition)** and **[Server Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Server_Acquisition)** applications. It synchronise and align RGB and depth frames in each Kinect and also matches corresponding data frames between two Kinects. Further, using the recorded calibration data (double-sided chessboards), this source code estimate the rigid transformation parameters, i.e. rotation and translation matrices and use them for registering the data recorded by **[Client Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Client_Acquisition)** and **[Server Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Server_Acquisition)** applications.



**If you use any form of this source code in your research, kindly cite [1].**

##Compilation and Running


##Dependencies
You need only Matlab 2015b or later versions for compiling and running this source code.


##License
This code is licensed under MIT license, which means you can modify and use for any purposes.

##Do You Need Help?
Compilation and running directions of the source codes have been explained in details in **Compilation and Running** Section. Further, the system methodology has been explained in our paper [1]. But, if you have any question or suggestion, please feel free to contact me by email: vahid [dot] soleimani [at] bristol [dot] ac [dot] uk .


##Publication
If you use any form of this source code in your research, kindly cite the following paper.

[1] V. Soleimani, M. Mirmehdi, D.Damen, S. Hannuna, M. Camplani, "3D Data Acquisition and Registration Using Two Opposing Kinects", _International Conference on 3D Vision_, Stanford, USA, October 2016.
