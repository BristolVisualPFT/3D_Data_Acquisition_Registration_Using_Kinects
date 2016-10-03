///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////                          University of Bristol                          ////////////////
//////////////                       Computer Science Department                       ////////////////
//===================================================================================================//
///////                            This is an open source code for:                             ///////
////////           "3D Data Acquisition and Registration using Two Opposing Kinects"         //////////
////////////////      V. Soleimani, M. Mirmehdi, D. Damen, S. Hannuna, M. Camplani    /////////////////
////////////////         International Conference on 3D Vision, Stanford, 2016        /////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Kinect.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <time.h>
#include "tbb/tbb_thread.h"
#include "tbb/concurrent_queue.h"
#include "tbb/tick_count.h"


#define KIN_JointType_SpineBase	0
#define KIN_JointType_SpineMid 1
#define KIN_JointType_Neck 2
#define KIN_JointType_Head 3
#define KIN_JointType_ShoulderLeft 4
#define KIN_JointType_ElbowLeft 5
#define KIN_JointType_WristLeft 6
#define KIN_JointType_HandLeft 7
#define KIN_JointType_ShoulderRight 8
#define KIN_JointType_ElbowRight 9
#define KIN_JointType_WristRight 10
#define KIN_JointType_HandRight 11
#define KIN_JointType_HipLeft 12
#define KIN_JointType_KneeLeft 13
#define KIN_JointType_AnkleLeft 14
#define KIN_JointType_FootLeft 15
#define KIN_JointType_HipRight 16
#define KIN_JointType_KneeRight 17
#define KIN_JointType_AnkleRight 18
#define KIN_JointType_FootRight 19
#define KIN_JointType_SpineShoulder 20
#define KIN_JointType_HandTipLeft 21
#define KIN_JointType_ThumbLeft 22
#define KIN_JointType_HandTipRight 23
#define KIN_JointType_ThumbRight 24
#define KIN_JointType_Count ( JointType_ThumbRight + 1 ) 
#define InfraredSourceValueMaximum static_cast<float>(USHRT_MAX)
#define InfraredOutputValueMinimum 0.01f 
#define InfraredOutputValueMaximum 1.0f
#define InfraredSceneValueAverage 0.09f
#define InfraredSceneStandardDeviations 3.0f

using namespace cv; 
//Various Structures
struct im { 
	Mat * matrix;
	INT64 i64DeviceTimeStamp;
	tbb::tick_count tbbtcNativeTimeStamp;
	SYSTEMTIME st;
};
typedef struct im ImageStruct;

struct fp {
	float fValues[6];
	tbb::tick_count tbbtcNativeTimeStamp;
	SYSTEMTIME st;
};
typedef struct fp ForceStruct;

struct skel {
	float x[25];
	float y[25];
	float z[25];
	int TrackingState[25];
	INT64 i64DeviceTimeStamp;
	tbb::tick_count tbbtcNativeTimeStamp;
	SYSTEMTIME st;
};
typedef struct skel Skeleton;


#define W 160
#define h 64

//NEW
using namespace cv;
using namespace std;

// Current Kinect
IKinectSensor* m_pKinectSensor;

ICoordinateMapper*      m_pCoordinateMapper;

// Depth reader
IDepthFrameReader*      m_pDepthFrameReader;
// Color reader
IColorFrameReader*      m_pColorFrameReader;
// Body Reader
IBodyFrameReader*       m_pBodyFrameReader;

IInfraredFrameReader*   m_pInfraredFrameReader;

IBodyFrameSource*		m_pBodyFrameSource;

RGBQUAD*                m_pColorRGBX;
static const int        cColorWidth  = 1920;
static const int        cColorHeight = 1080;

RGBQUAD*                m_pDepthRGBX;
static const int        cDepthWidth  = 512;
static const int        cDepthHeight = 424;

RGBQUAD*                m_pIRRGBX;
static const int        cIRWidth  = 512;
static const int        cIRHeight = 424;


Mat *imgColour;
Mat *imgColourDisplay;
Mat *imgDepth;
Mat *imgDepthDisplay;
Mat *imgIR;
Mat *imgIRDisplay;


Mat *imgInfo;

char cpFilenameJPG[1000];
char cpFilenamePNG[1000];
char cpSubdirectoryName[1000];
char cpRootDirect[1000];
char cpFullDirectPath[1000];
char cpFullDirectPathRGB[1000];
char cpFullDirectPathDepth[1000];
char cpFullDirectPathIR[1000];
char m_cpStartSPiroTime[1000];
char m_cpTestType[1000];


int m_iDepthWriteCnt = 0;
int m_iColourWriteCnt = 0;
int m_iIRWriteCnt = 0;
int m_iBodyWriteCnt = 0;

int m_iCurrPerson = 0;
bool m_bNotRecording = true;
int m_iFrameNum = 0;

//Other Kinect timing stuff
INT64                   m_nStartTime = 0;
INT64                   m_nLastCounter = 0;
double                  m_fFreq;
DWORD                   m_nNextStatusTime;
DWORD                   m_nFramesSinceUpdate;

cv::Point m_2dpScreenCoords[JointType_Count];
char m_cpDebugStr[1000];

//Bools to control what is on and what is not
bool m_bViewRGB = false;
bool m_bViewDepth = false;
bool m_bViewBody = true;
bool m_bViewForce = false;

bool m_bSaveRGB = false;
bool m_bSaveDepth = false;
bool m_bSaveBody = false;
bool m_bSaveForce = false;

bool m_bRunMainLoop = false;

bool m_bUseBMPencode = false;
bool m_bUseJPGencode = true;
bool m_bMarknSpirePoint = false;

bool m_bScreenSkeleton = true;



//Thread stuff
//Display
tbb::concurrent_queue<cv::Mat *> bufferDepthDisplay;
tbb::concurrent_queue<cv::Mat *> bufferRGBDisplay;
tbb::concurrent_queue<cv::Mat *> bufferIRDisplay;
int m_iDisplayScaleFactor = 2;

//Save
tbb::concurrent_queue<ImageStruct *> bufferDepthSave;
tbb::concurrent_queue<ImageStruct *> bufferRGBSave;
tbb::concurrent_queue<ImageStruct *> bufferIRSave;
tbb::concurrent_queue<ForceStruct *> bufferForceSave;
tbb::concurrent_queue<Skeleton *> bufferSkelSave;
float m_fRGBscaleFactor  = 0.5;


//Output file pointers
FILE *m_fpRGBMeta = NULL;
FILE *m_fpDepthMeta = NULL;
FILE *m_fpIRMeta = NULL;
FILE *m_fpSkel = NULL;
VideoWriter  m_outputVideo;     


char m_cpRGBfilepathTmp[1000];
char m_cpDepthfilepathTmp[1000];
char m_cpIRfilepathTmp[1000];

bool m_bStillWriting = false;

//Timing
tbb::tick_count m_tcStart;

//GUI poritioning
int m_iTop;
int m_iLeft;
int m_iWidth;
int m_iHeight;

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////                          University of Bristol                          ////////////////
//////////////                       Computer Science Department                       ////////////////
//===================================================================================================//
///////                            This is an open source code for:                             ///////
////////           "3D Data Acquisition and Registration using Two Opposing Kinects"         //////////
////////////////      V. Soleimani, M. Mirmehdi, D. Damen, S. Hannuna, M. Camplani    /////////////////
////////////////         International Conference on 3D Vision, Stanford, 2016        /////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
