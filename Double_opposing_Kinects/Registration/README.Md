----------------------------------------------
#RGB Point Clouds Alignment and Registration
----------------------------------------------



##Introduction

This package generates RGB point clouds of two Kinects using the pre-recorded RGBD data recorded by **[Client Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Client_Acquisition)** and **[Server Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Server_Acquisition)** applications and aligns them. It synchronises and aligns RGB and depth data frames in each Kinect and also matches corresponding data frames between two Kinects. Using the recorded calibration data (recorded from three double-sided chessboards), this source code is able to estimate the rigid transformation parameters, i.e. rotation and translation matrices, and use them to register point clouds generated using RGB and depth data recorded by **[Client Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Client_Acquisition)** and **[Server Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Server_Acquisition)**.



**If you use any form of this source code in your research, kindly cite [1].**

##Compilation and Running
The package contains several functions in separate Matlab M files, which performs synchronisation, alignment and registration of point clouds.

To help useres understand how to run and use the source code, an example has been provided. In this example, after downloading [**this sample RGBD data**](https://drive.google.com/file/d/0BxUVE0cBp62XRkFwWTdtTUlZc2M/view?usp=sharing) and decompressing it, two Matlab M files _"compute_R_T.m"_ and _"two_point_clouds_registration.m"_, must be compile and run respectively.
By executing _"compute_R_T.m"_, the rotation and transformation matrices are computed. These parameters are then exploited in _"two_point_clouds_registration.m"_ to perform the registration and alignment. Note that the _"data_path"_ variable in both M files must be initialised with the name of main folder of downloaded RGBD data, which here is named _"sample_rgbd_data"_.

To be able to align the RGB and depth frames correctly and generate the point cloud for each Kinect, camera and filter parameters of the RGB and depth sensors must be extracted from each Kinect and saved into a Matlab data file similar to the current ones. This can be done by using [libfreenects2](https://github.com/OpenKinect/libfreenect2) library.

##Dependencies
You need only Matlab 2015b or later versions for compiling and running this source code.


##License
This code is licensed under MIT license, which means you can modify and use for any purposes.

##Do You Need Help?
Compilation and running directions of the source codes have been explained in details in **Compilation and Running** Section. Further, the system methodology has been explained in our paper [1]. But, if you have any question or suggestion, please feel free to contact me by email: vahid [dot] soleimani [at] bristol [dot] ac [dot] uk .


##Publication
If you use any form of this source code in your research, kindly cite the following paper.

[1] V. Soleimani, M. Mirmehdi, D.Damen, S. Hannuna, M. Camplani, "3D Data Acquisition and Registration Using Two Opposing Kinects", _International Conference on 3D Vision_, Stanford, USA, October 2016.
