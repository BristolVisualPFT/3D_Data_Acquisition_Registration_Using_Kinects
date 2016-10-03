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

#pragma once
#include "KinectFunctions.h"

class workclass
{
public:

	workclass(void)
	{
	}

	~workclass(void)
	{
	}


	static bool writeSkeleton()
	{
		Skeleton * tmp;
		if(bufferSkelSave.try_pop(tmp))
		{
			char myDate [12];
			sprintf(myDate,"%.2hd%.2hd%.2hd%.3hd",tmp->st.wHour,tmp->st.wMinute,tmp->st.wSecond,tmp->st.wMilliseconds);

			fprintf(m_fpSkel,"%s %d %lld %g ", myDate, m_iBodyWriteCnt, tmp->i64DeviceTimeStamp, (tmp->tbbtcNativeTimeStamp - m_tcStart).seconds());
			for(int i = 0; i < 25; i++)
			{
				fprintf(m_fpSkel,"%d %f %f %f ", tmp->TrackingState[i], tmp->x[i], tmp->y[i], tmp->z[i]);
				
			}
			fprintf(m_fpSkel,"\n");

			//Free memory
			free(tmp);
			m_iBodyWriteCnt++;
			return true;
		}
		return false;
	}

	static bool writeDepth()
	{
		ImageStruct * tmp;

		if(bufferDepthSave.try_pop(tmp))
		{
			sprintf(m_cpDepthfilepathTmp,"%s\\depth%s%d.png",
				cpFullDirectPathDepth,
				(m_iDepthWriteCnt<10)?"0000":(m_iDepthWriteCnt<100)?"000":(m_iDepthWriteCnt<1000)?"00":(m_iDepthWriteCnt<10000)?"0":"",
				m_iDepthWriteCnt);

			imwrite(m_cpDepthfilepathTmp, *(tmp->matrix));


			//Now write in metadata file
			char myDate [12];
			sprintf(myDate,"%.2hd%.2hd%.2hd%.3hd",tmp->st.wHour,tmp->st.wMinute,tmp->st.wSecond,tmp->st.wMilliseconds);
			fprintf(m_fpDepthMeta,"%s, %d, %lld, %g\n", myDate, m_iDepthWriteCnt, tmp->i64DeviceTimeStamp, (tmp->tbbtcNativeTimeStamp - m_tcStart).seconds());

			//Free memory
			tmp->matrix->release();
			free(tmp);

			m_iDepthWriteCnt++;
		
			return true;
		}
		return false;
	}


	static bool writeRGB()
	{
		ImageStruct * tmp;

		if(bufferRGBSave.try_pop(tmp))
		{
			cv::Size sz;

			sz.height = (int)(((float)tmp->matrix->rows) * m_fRGBscaleFactor);
			sz.width = (int)(((float)tmp->matrix->cols) * m_fRGBscaleFactor);

			resize( *(tmp->matrix),  *(tmp->matrix),sz); 

			if(m_bUseBMPencode)
			{
				sprintf(m_cpRGBfilepathTmp,"%s\\rgb%s%d.bmp",
					cpFullDirectPathRGB,
					(m_iColourWriteCnt<10)?"0000":(m_iColourWriteCnt<100)?"000":(m_iColourWriteCnt<1000)?"00":(m_iColourWriteCnt<10000)?"0":"",
					m_iColourWriteCnt);
					imwrite(m_cpRGBfilepathTmp,*(tmp->matrix));
			}
			else
			{
				sprintf(m_cpRGBfilepathTmp,"%s\\rgb%s%d.jpg",
					cpFullDirectPathRGB,
					(m_iColourWriteCnt<10)?"0000":(m_iColourWriteCnt<100)?"000":(m_iColourWriteCnt<1000)?"00":(m_iColourWriteCnt<10000)?"0":"",
					m_iColourWriteCnt);
				std::vector<int> qualityType;
				qualityType.push_back(CV_IMWRITE_JPEG_QUALITY);
				qualityType.push_back(95);
				imwrite(m_cpRGBfilepathTmp,*(tmp->matrix),qualityType);
			} 

		
			//Now write in metadata file
			char myDate [12];
			sprintf(myDate,"%.2hd%.2hd%.2hd%.3hd",tmp->st.wHour,tmp->st.wMinute,tmp->st.wSecond,tmp->st.wMilliseconds);
			fprintf(m_fpRGBMeta,"%s, %d, %lld, %g\n", myDate, m_iColourWriteCnt, tmp->i64DeviceTimeStamp, (tmp->tbbtcNativeTimeStamp - m_tcStart).seconds());

			//Free memo
			tmp->matrix->release();
			free(tmp);		

			m_iColourWriteCnt++;

			return true;
		}
		return false;
	}

	static bool myPushDepthSave(Mat *depthImSave, INT64 ts, tbb::tick_count nts)
	{
		ImageStruct * tmp = new ImageStruct();

		tmp->matrix = new Mat(depthImSave->rows,depthImSave->cols, CV_16U);
		int dataSize=depthImSave->rows*depthImSave->cols*((int)depthImSave->elemSize());

		memcpy(tmp->matrix->data,depthImSave->data,  (size_t)dataSize);

		tmp->i64DeviceTimeStamp = ts;
		tmp->tbbtcNativeTimeStamp = nts;

		bufferDepthSave.push(tmp);

		return true;
	}

	static bool myPushRGBSave(Mat *rgbImSave, INT64 ts, tbb::tick_count nts)
	{
		ImageStruct * tmp = new ImageStruct();

		tmp->matrix = new Mat(rgbImSave->rows,rgbImSave->cols, CV_8UC4);
		int dataSize=rgbImSave->rows*rgbImSave->cols*((int)rgbImSave->elemSize());

		memcpy(tmp->matrix->data,rgbImSave->data,  (size_t)dataSize);

		tmp->i64DeviceTimeStamp = ts;
		tmp->tbbtcNativeTimeStamp = nts;

		bufferRGBSave.push(tmp);

		return true;
	}

	static bool myPushSkelSaveScreen(Joint joints[], INT64 ts, tbb::tick_count nts, cv::Point m_2dpScreenCoords[JointType_Count])
	{
		Skeleton * tmp = new Skeleton();

		for (int j = 0; j < JointType_Count && j < 25; ++j)
		{
			if (joints[j].TrackingState != TrackingState_Inferred && joints[j].TrackingState != TrackingState_Tracked)
			{		
				tmp->x[j] = tmp->y[j] = tmp->z[j] = -10000;
				tmp->TrackingState[j] = 0;				
			}
			else
			{		

				tmp->x[j] = (float)(m_2dpScreenCoords[j].x);
				tmp->y[j] = (float)(m_2dpScreenCoords[j].y);
				tmp->z[j] = joints[j].Position.Z;
				tmp->TrackingState[j] = joints[j].TrackingState;
			}
		}
		tmp->i64DeviceTimeStamp = ts;
		tmp->tbbtcNativeTimeStamp = nts;

		bufferSkelSave.push(tmp);

		return true;
	}


	static bool myPushSkelSave(Joint joints[], INT64 ts, tbb::tick_count nts)
	{
		Skeleton * tmp = new Skeleton();

		for (int j = 0; j < JointType_Count && j < 25; ++j)
		{
			if (joints[j].TrackingState != TrackingState_Inferred && joints[j].TrackingState != TrackingState_Tracked)
			{		
				tmp->x[j] = tmp->y[j] = tmp->z[j] = -10000;
				tmp->TrackingState[j] = 0;				
			}
			else
			{			
				tmp->x[j] = joints[j].Position.X;
				tmp->y[j] = joints[j].Position.Y;
				tmp->z[j] = joints[j].Position.Z;
				tmp->TrackingState[j] = joints[j].TrackingState;
			}
		}
		tmp->i64DeviceTimeStamp = ts;
		tmp->tbbtcNativeTimeStamp = nts;

		bufferSkelSave.push(tmp);

		return true;
	}

	static bool myPushForceSave(float forces[], tbb::tick_count nts)
	{
		ForceStruct * tmp = new ForceStruct();

		for(int j = 0; j < 6; ++j)
		{
			tmp->fValues[j] = forces[j];
		}

		tmp->tbbtcNativeTimeStamp = nts;

		bufferForceSave.push(tmp);


		return true;
	}

	static bool myPushDepthDisplay(Mat *depthImDisplay)
	{
		Mat * tmp = new Mat(depthImDisplay->rows,depthImDisplay->cols, CV_8UC4);
		int dataSize=depthImDisplay->rows*depthImDisplay->cols*((int)depthImDisplay->elemSize());

		memcpy(tmp->data,depthImDisplay->data,  (size_t)dataSize);

		bufferDepthDisplay.push(tmp);
		return true;
	}

	static bool myPushRGBDisplay(Mat *rgbImDisplay)
	{
		Mat * tmp = new Mat(rgbImDisplay->rows,rgbImDisplay->cols, CV_8UC4);
		int dataSize=rgbImDisplay->rows*rgbImDisplay->cols*((int)rgbImDisplay->elemSize());

		memcpy(tmp->data,rgbImDisplay->data,  (size_t)dataSize);

		bufferRGBDisplay.push(tmp);
		return true;
	}



	static void CloseSavePaths()
	{
		if(m_bSaveRGB)
		{			
			fclose(m_fpRGBMeta);

		}
		if(m_bSaveDepth)
		{	
			fclose(m_fpDepthMeta);
		}
		if(m_bSaveForce)
		{
			fclose(m_fpForce);
		}
		if(m_bSaveBody)
		{		
			fclose(m_fpSkel);
		}
	}

	static bool InitSavePaths()
	{		
		char cpTmpPath[1000];

		//If saving anything create a directory to store it in
		if(m_bSaveRGB || m_bSaveDepth || m_bSaveBody || m_bSaveForce)
		{
			CreateFolder();
		}
		//Colour
		if(m_bSaveRGB)
		{
			CreateRGBFolder();
			sprintf(cpTmpPath,"%s\\rgbMeta.txt",cpFullDirectPath);
			m_fpRGBMeta = fopen(cpTmpPath,"a");
			
		}
		if(m_bSaveDepth)
		{
			CreateDepthFolder();
			sprintf(cpTmpPath,"%s\\depthMeta.txt",cpFullDirectPath);
			m_fpDepthMeta = fopen(cpTmpPath,"a");
		}
		if(m_bSaveForce)
		{
			sprintf(cpTmpPath,"%s\\forceData.txt",cpFullDirectPath);
			m_fpForce = fopen(cpTmpPath,"a");
		}
		if(m_bSaveBody)
		{
			sprintf(cpTmpPath,"%s\\bodyData.txt",cpFullDirectPath);
			m_fpSkel = fopen(cpTmpPath,"a");

		}

		//Reset counters
		m_iDepthWriteCnt = 0;
		m_iColourWriteCnt = 0;
		m_iBodyWriteCnt = 0;

		return true;
	}

	static void  InitStuff()
	{
		//Do timestamp start
		m_tcStart = tbb::tick_count::now();


		InitSavePaths();

		// create heap storage for color pixel data in RGBX format
		if(m_bViewRGB)
		{						
			imgColourDisplay = new Mat(cColorHeight / m_iDisplayScaleFactor,cColorWidth / m_iDisplayScaleFactor, CV_8UC4);
			namedWindow( "Colour window", WINDOW_AUTOSIZE );
			moveWindow("Colour window", 600, 10);
		}
		if(m_bViewRGB || m_bSaveRGB)
		{
			m_pColorRGBX = new RGBQUAD[cColorWidth * cColorHeight];	
			imgColour = new Mat(cColorHeight,cColorWidth, CV_8UC4);
		}
		// create heap storage for color pixel data in RGBX format
		if(m_bViewDepth  || m_bViewBody)
		{
			// create heap storage for depth pixel data in RGBX format
			m_pDepthRGBX = new RGBQUAD[cDepthWidth * cDepthHeight];
			imgDepthDisplay = new Mat(cDepthHeight, cDepthWidth, CV_8UC4);					
			namedWindow( "Depth window", WINDOW_AUTOSIZE );
			moveWindow("Depth window", 10, 10);

		}
		if(m_bViewDepth || m_bSaveDepth) //Need to show body in a window - use depth 
		{
			imgDepth = new Mat(cDepthHeight, cDepthWidth,CV_16U);
		}
		if(m_bViewForce || m_bSaveForce)
		{
		}
		if(!(m_bViewBody || m_bViewDepth || m_bViewForce || m_bViewRGB))
		{
			namedWindow( "Info Window", WINDOW_AUTOSIZE );
			
			Mat Img = imread("im.png",CV_LOAD_IMAGE_COLOR);
			resize(Img, Img,cv::Size(290, 80)); 
			imshow("Info Window", Img);
			moveWindow("Info Window", m_iLeft , m_iTop + m_iHeight);
			waitKey(10);
					
		}
	}


	// Safe release for interfaces
	template<class Interface>
	static inline void SafeRelease(Interface *& pInterfaceToRelease)
	{
		if (pInterfaceToRelease != NULL)
		{
			pInterfaceToRelease->Release();
			pInterfaceToRelease = NULL;
		}
	}

	static void UpdateDepthWrap()
	{
		if(m_bSaveDepth || m_bViewDepth)
		{
			while(m_bRunMainLoop)
			{
				UpdateDepth();
			}
		}
	}

	static void UpdateColourWrap()
	{
		if(m_bSaveRGB || m_bViewRGB)
		{
			while(m_bRunMainLoop)
			{					
				UpdateColour();
			}
		}
	}

	static void UpdateBodyWrap()
	{
		if(m_bSaveBody || m_bViewBody)
		{
			while(m_bRunMainLoop)
			{					 
				UpdateBody();
			}
		}
	}


	static void writeRGBwrap()
	{
		while(1)
		{
			writeRGB();
		}
	}
	static void writeDepthwrap()
	{
		while(1)
		{
			writeDepth();
		}
	}
	static void writeSkeletonwrap()
	{
		while(1)
		{
			writeSkeleton();
		}
	}

	static bool SaveThread()
	{		

		if(m_bSaveRGB)
		{
			tbb::tbb_thread pMyThread1 = tbb::tbb_thread( writeRGBwrap);
		}
		if(m_bSaveDepth)
		{
			tbb::tbb_thread pMyThread2 = tbb::tbb_thread( writeDepthwrap);			
		}
		if(m_bSaveBody)
		{
			tbb::tbb_thread pMyThread4 = tbb::tbb_thread( writeSkeletonwrap);	
		}


		return true;
	}

	static void  mainLoop(int iNumIts, int numSaves)
	{
		tbb::tbb_thread pMyThread1 = tbb::tbb_thread( UpdateDepthWrap);
		tbb::tbb_thread pMyThread2 = tbb::tbb_thread( UpdateColourWrap);
		tbb::tbb_thread pMyThread3 = tbb::tbb_thread( UpdateBodyWrap);
		
		Sleep(100);

		SaveThread();

		Mat *tmp;
		while(m_bRunMainLoop)
		{
			if(m_bViewDepth && !m_bViewBody)
			{
				if (bufferDepthDisplay.try_pop(tmp)){
				imshow( "Depth window", *tmp);
				tmp->release();		 
				}
				waitKey(1);
			}
			if(m_bViewRGB)
			{
				if (bufferRGBDisplay.try_pop(tmp)){
				imshow( "Colour window", *tmp);
				tmp->release();
				}
				waitKey(1);
			}
			if(m_bViewBody)
			{
				if (bufferDepthDisplay.try_pop(tmp)){
				imshow( "Depth window", *tmp);
				tmp->release();	
				}
				waitKey(1);
			}	
			if(!(m_bViewBody || m_bViewDepth || m_bViewForce || m_bViewRGB))
			{							
				waitKey(100);
			}
		}

		//finishing writing files
		while(1)
		{
			Sleep(100);
			if(bufferDepthSave.unsafe_size() > 0 || bufferRGBSave.unsafe_size() > 0 || bufferForceSave.unsafe_size() > 0 || bufferSkelSave.unsafe_size() > 0)
			{
				continue;
			}
			else
			{
				break;
			}
		}


	}

	static HRESULT InitializeDefaultSensor()
	{
		HRESULT hr;

		hr = GetDefaultKinectSensor(&m_pKinectSensor);
		if (FAILED(hr))
		{
			return hr;
		}

		if (m_pKinectSensor)
		{
			// Initialize the Kinect and get the depth reader
			IDepthFrameSource* pDepthFrameSource = NULL;

			// Initialize the Kinect and get the color reader
			IColorFrameSource* pColorFrameSource = NULL; 

			// Initialize the Kinect and get the infrared reader
			//IInfraredFrameSource* pInfraredFrameSource = NULL;


			// Initialize the Kinect and get coordinate mapper and the body reader
			IBodyFrameSource* pBodyFrameSource = NULL;

			hr = m_pKinectSensor->Open();

			if(m_bViewBody || m_bSaveBody)
			{
				if (SUCCEEDED(hr))
				{
					hr = m_pKinectSensor->get_CoordinateMapper(&m_pCoordinateMapper);
				}

				if (SUCCEEDED(hr))
				{
					hr = m_pKinectSensor->get_BodyFrameSource(&m_pBodyFrameSource);
				}

				if (SUCCEEDED(hr))
				{
					hr = m_pBodyFrameSource->OpenReader(&m_pBodyFrameReader);
				}

				SafeRelease(m_pBodyFrameSource);
			}

			if(m_bViewDepth || m_bSaveDepth)
			{
				if (SUCCEEDED(hr))
				{
					hr = m_pKinectSensor->get_DepthFrameSource(&pDepthFrameSource);
				}

				if (SUCCEEDED(hr))
				{
					hr = pDepthFrameSource->OpenReader(&m_pDepthFrameReader);
				}
				SafeRelease(pDepthFrameSource);


			}

			if(m_bViewRGB || m_bSaveRGB)
			{
				if (SUCCEEDED(hr))
				{
					hr = m_pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
				}

				if (SUCCEEDED(hr))
				{
					hr = pColorFrameSource->OpenReader(&m_pColorFrameReader);
				}
				SafeRelease(pColorFrameSource);
			}

		}

		if (!m_pKinectSensor || FAILED(hr))
		{
			printf("No ready Kinect found!");
			getchar();
			return E_FAIL;
		}


		return hr;
	}

	static void BodyToDepthScreen(int *x, int *y, const CameraSpacePoint& bodyPoint, int width, int height)
	{
		DepthSpacePoint depthPoint = {0};
		m_pCoordinateMapper->MapCameraPointToDepthSpace(bodyPoint, &depthPoint);
		*x = static_cast<int>(depthPoint.X * width) / cDepthWidth;
		*y = static_cast<int>(depthPoint.Y * height) / cDepthHeight;

	}

	static void BodyToColourScreen(int *x, int *y, const CameraSpacePoint& bodyPoint, int width, int height)
	{
		// Calculate the body's position on the screen
		DepthSpacePoint depthPoint = {0};
		m_pCoordinateMapper->MapCameraPointToDepthSpace(bodyPoint, &depthPoint);
		*x = static_cast<int>(depthPoint.X * width) / cColorWidth;
		*y = static_cast<int>(depthPoint.Y * height) / cColorHeight;

	}



	static void textMessage()
	{		
		cv::putText(*imgDepthDisplay,m_cpDebugStr, cv::Point(10,50),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar( 0, 255, 0 ),2);			 
	}

	static void ProcessBodyOriginal(INT64 nTime, int nBodyCount, IBody** ppBodies)
	{
		HRESULT hr;
		if (m_pCoordinateMapper)
		{
			int width = cDepthWidth;
			int height = cDepthHeight;
			for (int i = 0; i < nBodyCount; ++i)
			{
				IBody* pBody = ppBodies[i];
				if (pBody)
				{
					BOOLEAN bTracked = false;
					hr = pBody->get_IsTracked(&bTracked);

					if (SUCCEEDED(hr) && bTracked)
					{
						Joint joints[JointType_Count]; 
						HandState leftHandState = HandState_Unknown;
						HandState rightHandState = HandState_Unknown;
						pBody->get_HandLeftState(&leftHandState);
						pBody->get_HandRightState(&rightHandState);
						hr = pBody->GetJoints(_countof(joints), joints);
						if (SUCCEEDED(hr))
						{
							if(m_bSaveBody)
							{
								if(m_bScreenSkeleton)
								{
									for (int j = 0; j < _countof(joints); ++j)
									{
										BodyToDepthScreen(&(m_2dpScreenCoords[j].x), &(m_2dpScreenCoords[j].y),joints[j].Position, width, height);		
									}
									myPushSkelSaveScreen(joints, nTime, tbb::tick_count::now(),m_2dpScreenCoords);

								}
								else
								{
									myPushSkelSave(joints, nTime, tbb::tick_count::now());
								}
							}
							if(m_bViewBody)
							{
								for (int j = 0; j < _countof(joints); ++j)
								{
									BodyToDepthScreen(&(m_2dpScreenCoords[j].x), &(m_2dpScreenCoords[j].y),joints[j].Position, width, height);		
								}
								DrawBody(joints,  m_2dpScreenCoords);
							}
						}
					}
				}
			}
		}
	}



	static void UpdateBody()
	{

		if (!m_pBodyFrameReader)
		{
			return;
		}

		IBodyFrame* pBodyFrame = NULL;
		SYSTEMTIME st_tmp;

		HRESULT hr = m_pBodyFrameReader->AcquireLatestFrame(&pBodyFrame);

		if (SUCCEEDED(hr))
		{
			INT64 nTime = 0;
			hr = pBodyFrame->get_RelativeTime(&nTime);
			IBody* ppBodies[BODY_COUNT] = {0};
			if (SUCCEEDED(hr))
			{
				hr = pBodyFrame->GetAndRefreshBodyData(_countof(ppBodies), ppBodies);
				GetSystemTime(&st_tmp);
			}

			if (SUCCEEDED(hr))
			{

				if(!m_bViewDepth && m_bViewBody)
					*imgDepthDisplay = Mat::zeros(cDepthHeight, cDepthWidth, CV_8UC4);
				if (m_pCoordinateMapper)
				{
					for (int i = 0; i < BODY_COUNT; ++i)
					{
						IBody* pBody = ppBodies[i];
						if (pBody)
						{
							BOOLEAN bTracked = false;
							hr = pBody->get_IsTracked(&bTracked);
							if (SUCCEEDED(hr) && bTracked)
							{
								Joint joints[JointType_Count]; 
								hr = pBody->GetJoints(_countof(joints), joints);
								if (SUCCEEDED(hr))
								{
									if (Body_send_flag)
									{
									if(m_bSaveBody)
									{
										if(m_bScreenSkeleton)
										{
											for (int j = 0; j < _countof(joints); ++j)
											{
												DepthSpacePoint depthPoint = {0};
												m_pCoordinateMapper->MapCameraPointToDepthSpace(joints[j].Position, &depthPoint);
												m_2dpScreenCoords[j].x = static_cast<int>(depthPoint.X);
												m_2dpScreenCoords[j].y = static_cast<int>(depthPoint.Y);
											}
											Skeleton * tmp = new Skeleton();
											for (int j = 0; j < JointType_Count && j < 25; ++j)
											{
												if (joints[j].TrackingState != TrackingState_Inferred && joints[j].TrackingState != TrackingState_Tracked)
												{		
													tmp->x[j] = tmp->y[j] = tmp->z[j] = -10000;
													tmp->TrackingState[j] = 0;				
												}
												else
												{		
													tmp->x[j] = (float)(m_2dpScreenCoords[j].x);
													tmp->y[j] = (float)(m_2dpScreenCoords[j].y);
													tmp->z[j] = joints[j].Position.Z;
													tmp->TrackingState[j] = joints[j].TrackingState;
												}
											}
											tmp->i64DeviceTimeStamp = nTime;
											tmp->tbbtcNativeTimeStamp = tbb::tick_count::now();
											tmp->st = st_tmp;
											bufferSkelSave.push(tmp);
										}
										else
										{
											Skeleton * tmp = new Skeleton();
											for (int j = 0; j < JointType_Count && j < 25; ++j)
											{
												if (joints[j].TrackingState != TrackingState_Inferred && joints[j].TrackingState != TrackingState_Tracked)
												{		
													tmp->x[j] = tmp->y[j] = tmp->z[j] = -10000;
													tmp->TrackingState[j] = 0;				
												}
												else
												{			
													tmp->x[j] = joints[j].Position.X;
													tmp->y[j] = joints[j].Position.Y;
													tmp->z[j] = joints[j].Position.Z;
													tmp->TrackingState[j] = joints[j].TrackingState;
												}
											}
											tmp->i64DeviceTimeStamp = nTime;
											tmp->tbbtcNativeTimeStamp = tbb::tick_count::now();
											tmp->st = st_tmp;
											bufferSkelSave.push(tmp);
										}
									
									}
									if(m_bViewBody)
									{
										for (int j = 0; j < _countof(joints); ++j)
										{
											DepthSpacePoint depthPoint = {0};
											m_pCoordinateMapper->MapCameraPointToDepthSpace(joints[j].Position, &depthPoint);
											m_2dpScreenCoords[j].x = static_cast<int>(depthPoint.X);
											m_2dpScreenCoords[j].y = static_cast<int>(depthPoint.Y);
										}
										// Torso
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_Head], m_2dpScreenCoords[KIN_JointType_Neck],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_Neck], m_2dpScreenCoords[KIN_JointType_SpineShoulder],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_SpineShoulder], m_2dpScreenCoords[KIN_JointType_SpineMid],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_SpineMid], m_2dpScreenCoords[KIN_JointType_SpineBase],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_SpineShoulder], m_2dpScreenCoords[KIN_JointType_ShoulderRight],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_SpineShoulder], m_2dpScreenCoords[KIN_JointType_ShoulderLeft],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_SpineBase], m_2dpScreenCoords[KIN_JointType_HipRight],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_SpineBase], m_2dpScreenCoords[KIN_JointType_HipLeft],cv::Scalar( 255, 0, 0 ), 3 );
										// Left Arm
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_ShoulderLeft], m_2dpScreenCoords[KIN_JointType_ElbowLeft],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_ElbowLeft], m_2dpScreenCoords[KIN_JointType_WristLeft],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_WristLeft], m_2dpScreenCoords[KIN_JointType_HandLeft],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_HandLeft], m_2dpScreenCoords[KIN_JointType_HandTipLeft],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_WristLeft], m_2dpScreenCoords[KIN_JointType_ThumbLeft],cv::Scalar( 255, 0, 0 ), 3 );
										// Right Arm
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_ShoulderRight], m_2dpScreenCoords[KIN_JointType_ElbowRight],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_ElbowRight], m_2dpScreenCoords[KIN_JointType_WristRight],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_WristRight], m_2dpScreenCoords[KIN_JointType_HandRight],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_HandRight], m_2dpScreenCoords[KIN_JointType_HandTipRight],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_WristRight], m_2dpScreenCoords[KIN_JointType_ThumbRight],cv::Scalar( 255, 0, 0 ), 3 );
										// Right Leg
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_HipRight], m_2dpScreenCoords[KIN_JointType_KneeRight],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_KneeRight], m_2dpScreenCoords[KIN_JointType_AnkleRight],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_AnkleRight], m_2dpScreenCoords[KIN_JointType_FootRight],cv::Scalar( 255, 0, 0 ), 3 );
										// Left Leg
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_HipLeft], m_2dpScreenCoords[KIN_JointType_KneeLeft],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_KneeLeft], m_2dpScreenCoords[KIN_JointType_AnkleLeft],cv::Scalar( 255, 0, 0 ), 3 );
										cv::line(*imgDepthDisplay, m_2dpScreenCoords[KIN_JointType_AnkleLeft], m_2dpScreenCoords[KIN_JointType_FootLeft],cv::Scalar( 255, 0, 0 ), 3 );
										// Draw the joints
										for (int i = 0; i < 24; ++i)
										{
											if (joints[i].TrackingState == TrackingState_Inferred)
											{	
												cv::circle( *imgDepthDisplay, m_2dpScreenCoords[i], 3, cv::Scalar( 0, 0, 255 ), 2 );
											}
											else if (joints[i].TrackingState == TrackingState_Tracked)
											{
												cv::circle( *imgDepthDisplay, m_2dpScreenCoords[i], 3, cv::Scalar( 0, 255, 0 ), 2 );
											}
										}
									}
									//
									}
								}
							}
						}
					}
				}
				if(m_bViewBody)
				{
					Mat * tmp = new Mat(imgDepthDisplay->rows,imgDepthDisplay->cols, CV_8UC4);
					int dataSize=imgDepthDisplay->rows*imgDepthDisplay->cols*((int)imgDepthDisplay->elemSize());
					memcpy(tmp->data,imgDepthDisplay->data,  (size_t)dataSize);
					bufferDepthDisplay.push(tmp);
				}
			}

			for (int i = 0; i < _countof(ppBodies); ++i)
			{
				SafeRelease(ppBodies[i]);
			}
		}

		SafeRelease(pBodyFrame);

	}

	static void UpdateDepth()
	{
		if (!m_pDepthFrameReader)
		{
			strcpy(m_cpDebugStr,"No Depth reader");		
			return;
		}

		IDepthFrame* pDepthFrame = NULL;

		HRESULT hr = m_pDepthFrameReader->AcquireLatestFrame(&pDepthFrame);

		if (SUCCEEDED(hr))
		{
			INT64 nTime = 0;
			IFrameDescription* pFrameDescription = NULL;
			int nWidth = 0;
			int nHeight = 0;
			USHORT nDepthMinReliableDistance = 0;
			USHORT nDepthMaxReliableDistance = 0;
			UINT nBufferSize = 0;
			UINT16 *pBuffer = NULL;
			SYSTEMTIME st_tmp;

			hr = pDepthFrame->get_RelativeTime(&nTime);

			if (SUCCEEDED(hr))
			{
				hr = pDepthFrame->get_FrameDescription(&pFrameDescription);
			}

			if (SUCCEEDED(hr))
			{
				hr = pFrameDescription->get_Width(&nWidth);
			}

			if (SUCCEEDED(hr))
			{
				hr = pFrameDescription->get_Height(&nHeight);
			}

			if (SUCCEEDED(hr))
			{
				hr = pDepthFrame->get_DepthMinReliableDistance(&nDepthMinReliableDistance);
			}

			if (SUCCEEDED(hr))
			{
				hr = pDepthFrame->get_DepthMaxReliableDistance(&nDepthMaxReliableDistance);
			}

			if (SUCCEEDED(hr))
			{
				GetSystemTime(&st_tmp);
				hr = pDepthFrame->AccessUnderlyingBuffer(&nBufferSize, &pBuffer);            
			}

			if (SUCCEEDED(hr))
			{
					
				if (Depth_send_flag)
				{
					if (pBuffer && (nWidth == cDepthWidth) && (nHeight == cDepthHeight))
					{
						if(m_bSaveDepth)
						{
							imgDepth->data = (uchar*)pBuffer;
							ImageStruct * tmp = new ImageStruct();
							tmp->matrix = new Mat(imgDepth->rows,imgDepth->cols, CV_16U);
							int dataSize=imgDepth->rows*imgDepth->cols*((int)imgDepth->elemSize());
							memcpy(tmp->matrix->data,imgDepth->data,  (size_t)dataSize);
							tmp->i64DeviceTimeStamp = nTime;
							tmp->tbbtcNativeTimeStamp = tbb::tick_count::now();
							tmp->st = st_tmp;
							bufferDepthSave.push(tmp);
						}
						if(m_bViewDepth && m_pDepthRGBX)
						{
							RGBQUAD* pRGBX = m_pDepthRGBX;
							const UINT16* pBufferEnd = pBuffer + (nWidth * nHeight);
							while (pBuffer < pBufferEnd)
							{
								USHORT depth = *pBuffer;
								BYTE intensity = static_cast<BYTE>((depth >= nDepthMinReliableDistance) && (depth <= nDepthMaxReliableDistance) ? (depth % 256) : 0);
								pRGBX->rgbRed   = intensity;
								pRGBX->rgbGreen = intensity;
								pRGBX->rgbBlue  = intensity;
								++pRGBX;
								++pBuffer;
							}
							imgDepthDisplay->data = (uchar*) m_pDepthRGBX;
							if(!m_bViewBody)
								myPushDepthDisplay(imgDepthDisplay);
						}
					}
				}
				
			}

			SafeRelease(pFrameDescription);
		}
		SafeRelease(pDepthFrame);
	}


	static void UpdateIR()
	{
		if (!m_pInfraredFrameReader)
		{
			cout << "No Infrared reader\n";
			return;
		}

		IInfraredFrame* pInfraredFrame = NULL;

		HRESULT hr = m_pInfraredFrameReader->AcquireLatestFrame(&pInfraredFrame);

		if (SUCCEEDED(hr))
		{
			INT64 nTime = 0;
			IFrameDescription* pFrameDescription = NULL;
			int nWidth = 0;
			int nHeight = 0;
			UINT nBufferSize = 0;
			UINT16 *pBuffer = NULL;
			SYSTEMTIME st_tmp;

			hr = pInfraredFrame->get_RelativeTime(&nTime);

			if (SUCCEEDED(hr))
			{
				hr = pInfraredFrame->get_FrameDescription(&pFrameDescription);
			}

			if (SUCCEEDED(hr))
			{
				hr = pFrameDescription->get_Width(&nWidth);
			}

			if (SUCCEEDED(hr))
			{
				hr = pFrameDescription->get_Height(&nHeight);
			}

			if (SUCCEEDED(hr))
			{
				GetSystemTime(&st_tmp);
				hr = pInfraredFrame->AccessUnderlyingBuffer(&nBufferSize, &pBuffer); 
				
			}

			if (SUCCEEDED(hr))
			{
				if (Depth_send_flag)
				{

				if (pBuffer && (nWidth == cDepthWidth) && (nHeight == cDepthHeight))
				{
					if(m_bSaveDepth)
					{
							imgDepth->data = (uchar*)pBuffer;
							ImageStruct * tmp = new ImageStruct();
							tmp->matrix = new Mat(imgDepth->rows,imgDepth->cols, CV_16U);
							int dataSize=imgDepth->rows*imgDepth->cols*((int)imgDepth->elemSize());
							memcpy(tmp->matrix->data,imgDepth->data,  (size_t)dataSize);
							tmp->i64DeviceTimeStamp = nTime;
							tmp->tbbtcNativeTimeStamp = tbb::tick_count::now();
							tmp->st = st_tmp;
							bufferDepthSave.push(tmp);
					}
					if(m_pDepthRGBX && m_bViewDepth)
					{
						RGBQUAD* pDest = m_pDepthRGBX;
						const UINT16* pBufferEnd = pBuffer + (nWidth * nHeight);
						while (pBuffer < pBufferEnd)
						{
							float intensityRatio = static_cast<float>(*pBuffer) / InfraredSourceValueMaximum;
							intensityRatio /= InfraredSceneValueAverage * InfraredSceneStandardDeviations;
							intensityRatio = min(InfraredOutputValueMaximum, intensityRatio);
							intensityRatio = max(InfraredOutputValueMinimum, intensityRatio);
							byte intensity = static_cast<byte>(intensityRatio * 255.0f); 
							pDest->rgbRed = intensity;
							pDest->rgbGreen = intensity;
							pDest->rgbBlue = intensity;
							++pDest;
							++pBuffer;
						}
						imgDepthDisplay->data = (uchar*) m_pDepthRGBX;
     					myPushDepthDisplay(imgDepthDisplay);
					}
				}
			}
			}
			SafeRelease(pFrameDescription);
		}

		SafeRelease(pInfraredFrame);
	}

	static void UpdateColour()
	{
		if (!m_pColorFrameReader)
		{
			cout << "No Depth reader\n";
			return;
		}
		IColorFrame* pColorFrame = NULL;

		HRESULT hr = m_pColorFrameReader->AcquireLatestFrame(&pColorFrame);

		if (SUCCEEDED(hr))
		{

			INT64 nTime = 0;
			IFrameDescription* pFrameDescription = NULL;
			int nWidth = 0;
			int nHeight = 0;
			ColorImageFormat imageFormat = ColorImageFormat_None;
			UINT nBufferSize = 0;
			RGBQUAD *pBuffer = NULL;
			SYSTEMTIME st_tmp;
			
			hr = pColorFrame->get_RelativeTime(&nTime);

			if (SUCCEEDED(hr))
			{
				hr = pColorFrame->get_FrameDescription(&pFrameDescription);
			}

			if (SUCCEEDED(hr))
			{
				hr = pFrameDescription->get_Width(&nWidth);
			}

			if (SUCCEEDED(hr))
			{
				hr = pFrameDescription->get_Height(&nHeight);
			}

			if (SUCCEEDED(hr))
			{
				hr = pColorFrame->get_RawColorImageFormat(&imageFormat);
			}

			if (SUCCEEDED(hr))
			{
				GetSystemTime(&st_tmp);
				if (imageFormat == ColorImageFormat_Bgra)
				{
					hr = pColorFrame->AccessRawUnderlyingBuffer(&nBufferSize, reinterpret_cast<BYTE**>(&pBuffer));
				}
				else if (m_pColorRGBX)
				{
					pBuffer = m_pColorRGBX;
					nBufferSize = cColorWidth * cColorHeight * sizeof(RGBQUAD);
					hr = pColorFrame->CopyConvertedFrameDataToArray(nBufferSize, reinterpret_cast<BYTE*>(pBuffer), ColorImageFormat_Bgra);            
				}
				else
				{
					hr = E_FAIL;
				}
				
			}

			if (SUCCEEDED(hr))
			{
				if (RGB_send_flag)
				{
						
				int dataSize=imgColour->rows*imgColour->cols*((int)imgColour->elemSize());
				imgColour->data = (uchar*) pBuffer;

				if(m_bSaveRGB)
				{
					if (pBuffer && (nWidth == cColorWidth) && (nHeight == cColorHeight))
					{		
					ImageStruct * tmp = new ImageStruct();
					tmp->matrix = new Mat(imgColour->rows,imgColour->cols, CV_8UC4);
					int dataSize=imgColour->rows*imgColour->cols*((int)imgColour->elemSize());
					memcpy(tmp->matrix->data,imgColour->data,  (size_t)dataSize);
					tmp->i64DeviceTimeStamp = nTime;
					tmp->tbbtcNativeTimeStamp = tbb::tick_count::now();
					tmp->st = st_tmp;
					bufferRGBSave.push(tmp);
					}
				}
				if(m_bViewRGB)
				{
					resize(*imgColour, *imgColourDisplay,cv::Size(imgColourDisplay->cols, imgColourDisplay->rows)); 
					myPushRGBDisplay(imgColourDisplay);				
				}

				}
			}

			SafeRelease(pFrameDescription);
		}

		SafeRelease(pColorFrame);		
	}

	static void UpdateSocketSend()
	{
		if (RGB_send_flag)
		{
			send( ClientSocket, "R", 1, 0 );
			RGB_send_flag = false;
		}
		if (Depth_send_flag)
		{
			send( ClientSocket, "D", 1, 0 );
			Depth_send_flag = false;
		}
		if (Body_send_flag)
		{
			send( ClientSocket, "B", 1, 0 );
			Body_send_flag = false;
		}

	}

	static void UpdateSocketReceive()
	{


	}


		static void UpdateSocketSendWrap()
	{
		while(m_bRunMainLoop)
		{					
			UpdateSocketSend();
		}
	}

	static void UpdateSocketReceiveWrap()
	{
		while(m_bRunMainLoop)
		{					
			UpdateSocketReceive();
		}
	}


	static void safeClose()
	{
		
		//Close files
		CloseSavePaths();

		// done with color frame reader
		SafeRelease(m_pColorFrameReader);

		// done with depth frame reader
		SafeRelease(m_pDepthFrameReader);

		// done with body frame reader
		SafeRelease(m_pBodyFrameReader);


		// done with coordinate mapper
		SafeRelease(m_pCoordinateMapper);

		// close the Kinect Sensor
		if (m_pKinectSensor)
		{
			m_pKinectSensor->Close();
		}

		SafeRelease(m_pKinectSensor);

		if(m_bSaveForce || m_bViewForce)
		{
			// Step 4 : Close device and release any allocated resource.
		//	m_instantAiCtrl->Dispose();
		}

		//Close files
		CloseSavePaths();


		//////// Close Socket
		closesocket(ListenSocket);
		// shutdown the connection since we're done
		int iResult = shutdown(ClientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			closesocket(ClientSocket);
			WSACleanup();
		}
		// cleanup
		closesocket(ClientSocket);
		WSACleanup();

	}

	static void ProcessColor(INT64 nTime, RGBQUAD* pBuffer, int nWidth, int nHeight) 
	{

		// Make sure we've received valid data
		if (pBuffer && (nWidth == cColorWidth) && (nHeight == cColorHeight))
		{		
			myPushRGBSave(imgColour, nTime, tbb::tick_count::now());
		}
	}


	static void ProcessDepth(INT64 nTime, const UINT16* pBuffer, int nWidth, int nHeight, USHORT nMinDepth, USHORT nMaxDepth)
	{
		// Make sure we've received valid data
		if (pBuffer && (nWidth == cDepthWidth) && (nHeight == cDepthHeight))
		{

			//write the image
			if(m_bSaveDepth)
			{
				imgDepth->data = (uchar*)pBuffer;
				myPushDepthSave(imgDepth, nTime, tbb::tick_count::now());
			}

			if(m_pDepthRGBX && m_bViewDepth)
			{
				RGBQUAD* pRGBX = m_pDepthRGBX;

				// end pixel is start + width*height - 1
				const UINT16* pBufferEnd = pBuffer + (nWidth * nHeight);

				while (pBuffer < pBufferEnd)
				{
					USHORT depth = *pBuffer;

					// To convert to a byte, we're discarding the most-significant
					// rather than least-significant bits.
					// We're preserving detail, although the intensity will "wrap."
					// Values outside the reliable depth range are mapped to 0 (black).

					// Note: Using conditionals in this loop could degrade performance.
					// Consider using a lookup table instead when writing production code.
					BYTE intensity = static_cast<BYTE>((depth >= nMinDepth) && (depth <= nMaxDepth) ? (depth % 256) : 0);

					pRGBX->rgbRed   = intensity;
					pRGBX->rgbGreen = intensity;
					pRGBX->rgbBlue  = intensity;

					++pRGBX;
					++pBuffer;
				}
				imgDepthDisplay->data = (uchar*) m_pDepthRGBX;
				if(!m_bViewBody)
					myPushDepthDisplay(imgDepthDisplay);

			}
		}
	}

	static void CreateRGBFolder()
	{
		sprintf(cpFullDirectPathRGB,"%s\\RGB",cpFullDirectPath);
		wchar_t wtext[1000];
		mbstowcs(wtext, cpFullDirectPathRGB, strlen(cpFullDirectPathRGB)+1);//Plus null
		LPWSTR ptr = wtext;

		if (CreateDirectory(ptr, NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError())
		{
		}
		else
		{
		}
	}

	static void CreateDepthFolder()
	{

		sprintf(cpFullDirectPathDepth,"%s\\DEPTH",cpFullDirectPath);
		wchar_t wtext[1000];
		mbstowcs(wtext, cpFullDirectPathDepth, strlen(cpFullDirectPathDepth)+1);//Plus null
		LPWSTR ptr = wtext;

		if (CreateDirectory(ptr, NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError())
		{
		}
		else
		{
		}
	}

	static void CreateFolder()
	{
		GetFolderName();

		sprintf(cpFullDirectPath,"%s\\%s", cpRootDirect, cpSubdirectoryName);
		wchar_t wtext[1000];
		mbstowcs(wtext, cpFullDirectPath, strlen(cpFullDirectPath)+1);//Plus null
		LPWSTR ptr = wtext;

		if (CreateDirectory(ptr, NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError())
		{
		}
		else
		{
		}
	}

	static void GetFolderNameSpiro()
	{
		SYSTEMTIME st;
		GetSystemTime(&st);

		sprintf(m_cpStartSPiroTime,"%.4hd%.2hd%.2hd, %.2hd%.2hd%.2hd%.3hd",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	}

	static void GetFolderName()
	{
		SYSTEMTIME st;
		GetSystemTime(&st);

		sprintf(cpSubdirectoryName,"%d-%s%d-%s%d-%s%d_%s%d-%s%d",  st.wYear,
			(st.wMonth < 10)?"0":"",st.wMonth,
			(st.wDay < 10)?"0":"",st.wDay,
			(st.wHour < 10)?"0":"",st.wHour,
			(st.wMinute < 10)?"0":"",st.wMinute,
			(st.wSecond < 10)?"0":"",st.wSecond);
	}

	static void GetFilenamePNG()
	{
		SYSTEMTIME st;
		GetSystemTime(&st);

		sprintf(cpFilenamePNG,"depth_%s%d-%s%d_%s%d-%s%d-%s%d.png" ,

			(st.wDay < 10)?"0":"",st.wDay,
			(st.wHour < 10)?"0":"",st.wHour,
			(st.wMinute < 10)?"0":"",st.wMinute,
			(st.wSecond < 10)?"0":"",st.wSecond,
			(st.wMilliseconds < 10)?"000":(st.wMilliseconds < 100)?"00":(st.wMilliseconds < 1000)?"0":"",st.wMilliseconds);
	}

	static void GetFilenameJPG()
	{
		SYSTEMTIME st;
		GetSystemTime(&st);

		sprintf(cpFilenameJPG,"colour_%s%d-%s%d_%s%d-%s%d-%s%d.jpg" ,

			(st.wDay < 10)?"0":"",st.wDay,
			(st.wHour < 10)?"0":"",st.wHour,
			(st.wMinute < 10)?"0":"",st.wMinute,
			(st.wSecond < 10)?"0":"",st.wSecond,
			(st.wMilliseconds < 10)?"000":(st.wMilliseconds < 100)?"00":(st.wMilliseconds < 1000)?"0":"",st.wMilliseconds);

	}

	static void DrawBone(const Joint* pJoints, cv::Point pJointPoints[], int iStart, int iEnd)
	{
		cv::line(*imgDepthDisplay, pJointPoints[iStart], pJointPoints[iEnd],cv::Scalar( 255, 0, 0 ), 3 );
	}

	static void DrawBody(const Joint* pJoints, cv::Point pJointPoints[])
	{
		//Text

		// Draw the bones
		// Torso
		DrawBone(pJoints, pJointPoints, KIN_JointType_Head, KIN_JointType_Neck);
		DrawBone(pJoints, pJointPoints, KIN_JointType_Neck, KIN_JointType_SpineShoulder);
		DrawBone(pJoints, pJointPoints, KIN_JointType_SpineShoulder, KIN_JointType_SpineMid);
		DrawBone(pJoints, pJointPoints, KIN_JointType_SpineMid, KIN_JointType_SpineBase);
		DrawBone(pJoints, pJointPoints, KIN_JointType_SpineShoulder, KIN_JointType_ShoulderRight);
		DrawBone(pJoints, pJointPoints, KIN_JointType_SpineShoulder, KIN_JointType_ShoulderLeft);
		DrawBone(pJoints, pJointPoints, KIN_JointType_SpineBase, KIN_JointType_HipRight);
		DrawBone(pJoints, pJointPoints, KIN_JointType_SpineBase, KIN_JointType_HipLeft);

		// Left Arm
		DrawBone(pJoints, pJointPoints, KIN_JointType_ShoulderLeft, KIN_JointType_ElbowLeft);
		DrawBone(pJoints, pJointPoints, KIN_JointType_ElbowLeft, KIN_JointType_WristLeft);
		DrawBone(pJoints, pJointPoints, KIN_JointType_WristLeft, KIN_JointType_HandLeft);
		DrawBone(pJoints, pJointPoints, KIN_JointType_HandLeft, KIN_JointType_HandTipLeft);
		DrawBone(pJoints, pJointPoints, KIN_JointType_WristLeft, KIN_JointType_ThumbLeft);

		// Right Arm
		DrawBone(pJoints, pJointPoints, KIN_JointType_ShoulderRight, KIN_JointType_ElbowRight);
		DrawBone(pJoints, pJointPoints, KIN_JointType_ElbowRight, KIN_JointType_WristRight);
		DrawBone(pJoints, pJointPoints, KIN_JointType_WristRight, KIN_JointType_HandRight);
		DrawBone(pJoints, pJointPoints, KIN_JointType_HandRight, KIN_JointType_HandTipRight);
		DrawBone(pJoints, pJointPoints, KIN_JointType_WristRight, KIN_JointType_ThumbRight);

		// Right Leg
		DrawBone(pJoints, pJointPoints, KIN_JointType_HipRight, KIN_JointType_KneeRight);
		DrawBone(pJoints, pJointPoints, KIN_JointType_KneeRight, KIN_JointType_AnkleRight);
		DrawBone(pJoints, pJointPoints, KIN_JointType_AnkleRight, KIN_JointType_FootRight);

		// Left Leg
		DrawBone(pJoints, pJointPoints, KIN_JointType_HipLeft, KIN_JointType_KneeLeft);
		DrawBone(pJoints, pJointPoints, KIN_JointType_KneeLeft, KIN_JointType_AnkleLeft);
		DrawBone(pJoints, pJointPoints, KIN_JointType_AnkleLeft, KIN_JointType_FootLeft);

		// Draw the joints
		for (int i = 0; i < JointType_Count; ++i)
		{
			if (pJoints[i].TrackingState == TrackingState_Inferred)
			{	
				cv::circle( *imgDepthDisplay, pJointPoints[i], 3, cv::Scalar( 0, 0, 255 ), 2 );
			}
			else if (pJoints[i].TrackingState == TrackingState_Tracked)
			{
				cv::circle( *imgDepthDisplay, pJointPoints[i], 3, cv::Scalar( 0, 255, 0 ), 2 );
			}
		}
	}
};

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
