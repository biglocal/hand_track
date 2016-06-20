#include "hand_Form.h"
#include <array>
#include <iostream>

#include <Kinect.h>
#include "hand_tracking.h"
//
// Kinect for Windows SDK Header

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;

[STAThread]//leave this as is
void main(array<String^>^ args) {
	App app;
	//App::managed^ managed_c = gcnew App::managed;
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	//kinect_multisource::hand_Form form;
	Application::Run(%app.managed_c->form);
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
	depthFrameSource->get_DepthMaxReliableDistance(&uDepthMax);
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


void App::Tick(System::Windows::Forms::ListBox^  lb_log)
{
	HRESULT hr;
	IDepthFrame* depthFrame;
	hr = m_depthFrameReader->AcquireLatestFrame(&depthFrame);
	if (FAILED(hr))
	{
		lb_log->Items->Add("Acquire Depth Frame Failed");
		return;
	}
	hr = depthFrame->CopyFrameDataToArray(iDepthWidth * iDepthHeight, m_depthBuffer);
	SafeRelease(depthFrame);
}

void App::Draw(System::Windows::Forms::ListBox^  lb_log, System::Windows::Forms::PictureBox^  pic_result)
{

	lb_log->Items->Add("Draw Pic");
	mDepthImg = cv::Mat(iDepthHeight, iDepthWidth, CV_16U, uDepthPointNum);
	mDepthImg.convertTo(mImg8bit, CV_8U, 255.0f / uDepthMax);

	// only color images are supported
	assert(mImg8bit.type() == CV_8UC1);

	if ((pic_result->Image == nullptr) || (pic_result->Width != mImg8bit.cols) || (pic_result->Height != mImg8bit.rows))
	{
		pic_result->Width = mImg8bit.cols;
		pic_result->Height = mImg8bit.rows;
		pic_result->Image = gcnew System::Drawing::Bitmap(mImg8bit.cols, mImg8bit.rows);
	}

	// Create System::Drawing::Bitmap from cv::Mat
	System::Drawing::Bitmap^ bmpImage = gcnew System::Drawing::Bitmap(
		mImg8bit.cols, mImg8bit.rows, mImg8bit.step,
		System::Drawing::Imaging::PixelFormat::Format8bppIndexed,
		System::IntPtr(mImg8bit.data)
	);

	// Draw Bitmap over a PictureBox
	System::Drawing::Graphics^ g = System::Drawing::Graphics::FromImage(pic_result->Image);

	g->DrawImage(bmpImage, 0, 0, mImg8bit.cols, mImg8bit.rows);
	pic_result->Refresh();
}

void App::managed::wait_frame()
{

}

void App::managed::create_thread()
{
	Thread^ threads = gcnew Thread(gcnew ParameterizedThreadStart(this, &App::managed::wait_frame));
	threads->Start();
}

void kinect_multisource::hand_Form::hand_Form_Load(System::Object^  sender, System::EventArgs^  e)
{
	if (FAILED(App::Init(lb_log)))
	{
		lb_log->Items->Add("Kinect initial failed");
		return;
	}
	

	App::Shutdown(lb_log);
}