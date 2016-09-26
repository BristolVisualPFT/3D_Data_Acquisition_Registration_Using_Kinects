-----------------------------------------------
#3D Data Acquisition and Registration Using Two Opposing Kinects
-----------------------------------------------

##Introduction
This system has been developed to calibrate two opposing Kinects V2 RGBD sensors using an optical approach and register their point clouds to a joint space [1]. It contains calibration, acquisition and registration parts and has been implemented in C++ (Microsoft Visual Studio 2012) and Matlab. We have also used third party libraries explained in **Hardware and Software Requirements** section. Compilation directions and running instructions have been explained in each related sub-repository, i.e. **Calibrator**, **Client_Acquisition**, **Server_Acquisition** and **Registration**.

Unlike other approaches which use Kinect SDK built-in functions and generate RGB point cloud only for on-line streams (it means Kinect needs to be connected!), our system is able to generate and align RGB point clouds off-line, using pre-recorded RGB and depth data frames. This allows to reconstruct RGB point cloud of a dynamic object at _30fps_ consistent rate, which could be important for sensitive applications, e.g. medical recordings.

According to Kinect for Windows SDK 2.0, individual machines are required for each separate Kinect V2 device. Although other libraries such as [libfreenect2](https://github.com/OpenKinect/libfreenect2) allows to connect two devices to a powerful machine with separate USB3 buses, it decreases the frame rate and it also does not provide the body skeleton data, which could be necessary for some applications. Therefore, the system uses two Windows machines which have been locally connected via TCP/IP protocol. Machines system time are synchronised using NTP.


##Hardware and Software Requirements

The source code requires the following equipment and libraries to perform:

+ Two second generation of Kinect for Windows
+ Two Kinect-compatible Windows (8.1 or 10) PCs or laptops
+ Three double sided chessboards ([preparation instructions](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Double_sided_chessboard))
+ [Kinect for Windows SDK 2.0](https://www.microsoft.com/en-gb/download/details.aspx?id=44561)
+ [Intel Threading Building Blocks](https://www.threadingbuildingblocks.org/software-release/tbb4320140724oss)
+ [OpenCV](https://github.com/opencv/opencv)
+ [Network Time Protocol(NTP)](https://github.com/ntp-project/ntp)


##Calibration and Registration
First, two Kinects must be calibrated against each other to find the parameters of rigid transformation. These parameters are then exploited in the registration step. For this, after putting the two Kinects opposing each other within a desire distance between them (>2m), three double-sided chessboards are set up in between two Kinects and in different depths. However, all of the chessboards should be completely in the field of view of two Kinects. A pair of infrared/depth images obtained from each Kinect is required for calibration. This data is captured by [Calibrator tool](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Calibrator) and is used in the registration stage to estimate the transformation parameters. The calibration method has been completely explained in [1]. 

In this stage, RGB, depth and skeleton (optional) data are acquired and stored on each machine separately using [Server-Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Server_Acquisition) and [Client-Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Client_Acquisition) tools. Two machines needs to be sunchronised using NTP to be able to match corresponding RGB, depth and skeleton data of each machine.



##Publication
If you use any form of this source code in your research, kindly cite the following paper.

[1] V. Soleimani, M. Mirmehdi, D.Damen, S. Hannuna, M. Camplani, "3D Data Acquisition and Registration Using Two Opposing Kinects", International Conference on 3D Vision, Stanford, USA, October 2016.

