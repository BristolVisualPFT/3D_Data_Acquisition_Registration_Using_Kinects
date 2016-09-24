-----------------------------------------------
#3D Data Acquisition and Registration Using Two Opposing Kinects
-----------------------------------------------

##Introduction
This system has been developed to calibrate two opposing Kinects V2 RGBD sensors using an optical approach and register their point clouds to a joint space [1]. It contains calibration, acquisition and registration parts and has been implemented in C++ (Microsoft Visual Studio 2012) and Matlab. We have also used third party libraries explained in **Hardware and Software Requirements** section. Compilation directions and running instructions have been explained in each related sub-repository, i.e. **Calibrator**, **Client_Acquisition**, **Server_Acquisition** and **Registration**.

Unlike other approaches which use Kinect SDK built-in functions and can generate RGB point cloud only for on-line streams (it means Kinect needs to be connected!), our system is able to generate and align RGB point clouds off-line, using pre-recorded RGB and depth data frames. This allows to reconstruct RGBD point cloud of a dynamic object at consistent 30fps, which could be important for sensitive applications, e.g. medical recordings.

According to Kinect for Windows SDK 2.0, individual machines are required for each separate Kinect V2 device. Although libfreenect2 allows to connect two devices to a powerful machine with separate USB3 buses, it decreases the frame rate and it does not also provide the body skeleton data, which could be necessary for some applications. Therefore, the system uses two Windows machine which has been locally connected via TCP/IP protocol. Machines system time are synchronised using NTP.


##Hardware and software Requirements

The system require the following equipments and libraries to perform:

+ Two KinectV2
+ Two KinectV2-compatible Windows machines
+ Three double sided chessboards
+ Kinect for Windows SDK 2.0 (Free Comercial License)
+ Intel Threading Building Blocks (GPLv2 License)
+ OpenCV (BSD License)
