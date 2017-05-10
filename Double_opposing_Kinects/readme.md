-----------------------------------------------
# 3D Data Acquisition and Registration Using Two Opposing Kinects #
-----------------------------------------------
<p align="center">
  <img src="https://cloud.githubusercontent.com/assets/22081195/19001689/5eca2bce-8740-11e6-87a8-b11b086f9d3b.gif" width=600>
</p>

## Introduction
This system has been developed to calibrate two opposing Kinects V2 RGBD sensors using an optical approach and register their point clouds to a joint space [1]. It contains calibration, acquisition and registration parts and has been implemented in C++ (Microsoft Visual Studio 2012) and Matlab. We have also used third party libraries explained in **Hardware and Software Requirements** section. Compilation directions and running instructions have been explained in each related sub-repository, i.e. **Calibration_Acquisition**, **Client_Acquisition**, **Server_Acquisition** and **Registration**.

Unlike other approaches which use Kinect SDK built-in functions and generate RGB point cloud only for on-line streams (it means Kinect needs to be connected!), our system is able to generate and align RGB point clouds off-line, using pre-recorded RGB and depth data frames. This allows to reconstruct RGB point cloud of a dynamic object at _30fps_ consistent rate, which could be important for sensitive applications, e.g. medical recordings.

According to Kinect for Windows SDK 2.0, individual machines are required for each separate Kinect V2 device. Although other libraries such as [libfreenect2](https://github.com/OpenKinect/libfreenect2) allows to connect two devices to a powerful machine with separate USB3 buses, it decreases the frame rate and it also does not provide the body skeleton data, which could be necessary for some applications. Therefore, the system uses two Windows machines which have been locally connected via TCP/IP protocol. Machines system time are synchronised using NTP.

**If you use any form of this source code in your research, kindly cite [1].**

## Hardware and Software Requirements

The source code requires the following equipment and libraries to perform:

+ Two Kinects (second generation) for Windows
+ Two Kinect-compatible Windows (8.1 or 10) PCs or laptops
+ Three double sided chessboards ([preparation instructions](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Double_sided_chessboards))
+ [Kinect for Windows SDK 2.0](https://www.microsoft.com/en-gb/download/details.aspx?id=44561)
+ Microsoft Visual Studio C++
+ Matlab 2015b or later
+ [Intel Threading Building Blocks](https://www.threadingbuildingblocks.org/software-release/tbb4320140724oss)
+ [OpenCV](https://github.com/opencv/opencv)
+ [Network Time Protocol(NTP)](https://github.com/ntp-project/ntp)


## Calibration
First, two Kinects must be calibrated against each other to find the parameters of rigid transformation. These parameters are then exploited in the registration step. For this, after putting the two Kinects opposing each other within a desire distance between them, three double-sided chessboards are set up in between two Kinects and in different depths. All of the chessboards should be completely in the field of view of two Kinects. A pair of infrared/depth images obtained from each Kinect is required for calibration. This data must be acquired by both machines using [**Calibration_Acquisition**](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Calibration_Acquisition) and is used to estimate the transformation parameters. The calibration method has been completely explained in [1]. 

## Registration
After RGB, depth and skeleton (optional) data are acquired and stored on each machine separately using [**Server_Acquisition**](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Server_Acquisition) and [**Client_Acquisition**](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Client_Acquisition), their RGB point clouds are then generated and registered into a joint space using the [**Registration**](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Registration) source code. Both Client and Server Data Acquisition applications have been implemented in C++ using Microsoft Visual Studio 2012. Registration stage has been implemeted in Matlab. Compilation and running directions of Client_Acquisition, Server_Acquisition and Registration has been explained in their sub-repositories. To be able to match corresponding RGB, depth and skeleton data, captured by Client and Server machines, two machines' system time must be synchronised. For this, Client and Server machines are locally networked and NTP is used for synchronisation.

### NTP Synchronisation
NTP is a network time protocol which is used for synchronising a machine system time with internal or external servers. A Windows (32-64bit) compatible version can be downloaded from [**this page**](https://www.meinbergglobal.com/english/sw/ntp.htm). Here, NTP must be installed on both client and sever machines, and their INI files must be configured such that the client machine system time would be synchronised with the server. For more informtion about the synchronisation, please refer to this [**guidance**](https://www.meinbergglobal.com/english/sw/readme-ntpinstaller.htm). There is also an [**NTP Time Server Monitor**](https://www.meinbergglobal.com/english/sw/ntp-server-monitor.htm) application which can be used for easier configuring of the INI files.


## Summary
In summary, you must take the following steps to be able to run the source codes and generate and register 3D RGB point clouds:

1. Setup two opposing Kinects
2. Locally network and synchronise server and client machines time using NTP
3. Calibrate Kinects
  1. Setup three double-sided chessboards
  2. Acquire infrared/depth data using both machines by [Calibration_Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Calibration_Acquisition)
4. Register point clouds
 1. Acquire RGB, depth and skeleton (optional) data by [Client_Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Client_Acquisition) and [Server_Acquisition](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Server_Acquisition)
 2. Generate and register RGB point clouds using [Registration](https://github.com/BristolVisualPFT/3D_Data_Acquisition_Registration_Using_Kinects/tree/master/Double_opposing_Kinects/Registration) source code.

## Do You Need Help?
Compilation and running directions of the source codes have been explained in details, in their dedicated sub-repositories. Further, the system methodology has been explained in our paper [1]. But, if you have any question or suggestion, please feel free to contact me by email: vahid [dot] soleimani [at] bristol [dot] ac [dot] uk .


## Publication
If you use any form of this source code in your research, kindly cite the following paper.

[1] V. Soleimani, M. Mirmehdi, D.Damen, S. Hannuna, M. Camplani, "3D Data Acquisition and Registration Using Two Opposing Kinects", International Conference on 3D Vision, Stanford, USA, October 2016.

<p align="center">
  <img src="https://cloud.githubusercontent.com/assets/22081195/19785457/560e5e72-9c91-11e6-9e0b-de685185675a.png" width=800>
</p>
