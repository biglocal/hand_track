#pragma once

#include <iostream>
#include <Kinect.h>
#include "hand_Form.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

template<typename T>
void SafeRelease(T& ptr) { if (ptr) { ptr->Release(); ptr = nullptr; } }

class App
{
public:
	long Init(System::Windows::Forms::ListBox^  lb_log);
	void Tick(System::Windows::Forms::ListBox^  lb_log);
	void Draw(System::Windows::Forms::ListBox^  lb_log, System::Windows::Forms::PictureBox^  pic_result);
	void Shutdown(System::Windows::Forms::ListBox^  lb_log);
	
	ref class managed
	{
	public:
		void create_thread();
		void wait_frame();
	private:
		kinect_multisource::hand_Form form;
	};

	managed^ managed_c;
private:
	cv::Mat mImg8bit;
	cv::Mat mDepthImg;
	IKinectSensor* m_sensor = nullptr;
	IDepthFrameReader* m_depthFrameReader = nullptr;
	IBodyFrameReader*  m_bodyFrameReader = nullptr;
	ICoordinateMapper* m_coordinateMapper = nullptr;
	IBodyIndexFrameReader* m_bodyIndexFrameReader = nullptr;

	int iDepthWidth = 0;
	int iDepthHeight = 0;
	int uDepthPointNum = 0;
	int iBodyCount = 0;

	UINT16 *m_depthBuffer = nullptr;
	UINT16 uDepthMax;
};



