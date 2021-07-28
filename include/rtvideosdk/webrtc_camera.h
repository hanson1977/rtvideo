#pragma once
#include "windows.h"
#include "shinevv.h"
class SHINEVVAPI WebrtcCamera
{
public:
	static WebrtcCamera* Create(int idx,HWND window);
	WebrtcCamera(int idx,HWND window);
	virtual bool Start()=0;
	virtual void Stop()=0;
	virtual void Release() = 0;
	virtual bool IsRunning()=0;	
protected:
	int m_width = 1920;
	int m_height = 1080;
	int m_fps = 30;
	int m_idx = 0;
	HWND m_wnd;
};

