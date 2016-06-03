#pragma once

#include <iostream>
#include <Kinect.h>
#include "hand_Form.h"

template<typename T>
void SafeRelease(T& ptr) { if (ptr) { ptr->Release(); ptr = nullptr; } }

class App
{
public:
	long Init(System::Windows::Forms::ListBox^  lb_log);
	void Shutdown(System::Windows::Forms::ListBox^  lb_log);

private:
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
};