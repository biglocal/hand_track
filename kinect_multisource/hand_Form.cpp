#include "hand_Form.h"
#include <array>
#include <iostream>

#include <Kinect.h>
#include "hand_tracking.h"
// Kinect for Windows SDK Header

using namespace System;
using namespace System::Windows::Forms;

[STAThread]//leave this as is
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	kinect_multisource::hand_Form form;
	Application::Run(%form);
}

long App::Init(System::Windows::Forms::ListBox^  lb_log)
{
	HRESULT hr;
	char str_log[512];

	lb_log->Items->Add("Get Sensor...");
	hr = GetDefaultKinectSensor(&m_sensor);
	if (FAILED(hr))
	{
		lb_log->Items->Add("Get Sensor failed");
		return -1;
	}
	/* depthFrameSource init */
	lb_log->Items->Add("depthFrameSource init...");
	IDepthFrameSource* depthFrameSource;
	hr = m_sensor->get_DepthFrameSource(&depthFrameSource);
	if (FAILED(hr))
	{
		lb_log->Items->Add("Failed to get the depth frame source.");
		return - 1;
	}
	IFrameDescription *frameDesc;
	depthFrameSource->get_FrameDescription(&frameDesc);
	frameDesc->get_Width(&iDepthWidth);
	frameDesc->get_Height(&iDepthHeight);
	snprintf(str_log, sizeof(str_log), "Width:%d, Height:%d", iDepthWidth, iDepthHeight);
	lb_log->Items->Add(gcnew String(str_log));
	/* get the depth frame reader */
	lb_log->Items->Add("get the depth frame reader...");
	hr = depthFrameSource->OpenReader(&m_depthFrameReader);
	if (FAILED(hr))
	{
		lb_log->Items->Add("Failed to open the depth frame reader!\n");
		return -1;
	}
	SafeRelease(depthFrameSource);
	m_depthBuffer = new UINT16[iDepthWidth * iDepthHeight];
	
	/* bodyFrameSource init */
	IBodyFrameSource* bodyFrameSource = nullptr;
	hr = m_sensor->get_BodyFrameSource(&bodyFrameSource);
	if (FAILED(hr))
	{
		lb_log->Items->Add("Failed to get the body frame source.");
		return -1;
	}

	if (bodyFrameSource->get_BodyCount(&iBodyCount) != S_OK)
	{
		lb_log->Items->Add("Can't get body count");
		return -1;
	}
	snprintf(str_log, sizeof(str_log), "Can trace %d bodies", iBodyCount);
	lb_log->Items->Add(gcnew String(str_log));
	/* get the body frame reader */
	lb_log->Items->Add("get the body index frame reader...");
	hr = bodyFrameSource->OpenReader(&m_bodyFrameReader);
	if (FAILED(hr))
	{
		lb_log->Items->Add("Failed to open the depth frame reader!\n");
		return -1;
	}
	SafeRelease(bodyFrameSource);

	/* body index FrameSource init */
	IBodyIndexFrameSource* bodyIndexFrameSource = nullptr;
	hr = m_sensor->get_BodyIndexFrameSource(&bodyIndexFrameSource);
	if (FAILED(hr))
	{
		lb_log->Items->Add("Failed to get the body index frame source.");
		return -1;
	}

	/* get the body frame reader */
	lb_log->Items->Add("get the body index frame reader...");
	hr = bodyIndexFrameSource->OpenReader(&m_bodyIndexFrameReader);
	if (FAILED(hr))
	{
		lb_log->Items->Add("Failed to open the body index frame reader!\n");
		return -1;
	}
	SafeRelease(bodyIndexFrameSource);

	/* Init CoordinateMapper */
	if (m_sensor->get_CoordinateMapper(&m_coordinateMapper) != S_OK)
	{
		lb_log->Items->Add("get_CoordinateMapper failed");
		return -1;
	}
	lb_log->Items->Add("============== Init OK ==============");
	return 0;
}

void App::Shutdown(System::Windows::Forms::ListBox^  lb_log)
{
	//put cleaning up stuff here
	delete[] m_depthBuffer;
	SafeRelease(m_depthFrameReader);
	SafeRelease(m_sensor);
	lb_log->Items->Add("Release kinect resource");
}

void kinect_multisource::hand_Form::hand_Form_Load(System::Object^  sender, System::EventArgs^  e)
{
	App app;
	if (FAILED(app.Init(lb_log)))
	{
		lb_log->Items->Add("Kinect initial failed");
		return;
	}
	app.Shutdown(lb_log);
}