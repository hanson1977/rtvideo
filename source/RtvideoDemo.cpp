
// RtvideoDemo.cpp: 定义应用程序的类行为。
//

#include "RtvideoDemo.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CRtvideoDemoApp, CWinApp)
END_MESSAGE_MAP()
CRtvideoDemoApp::CRtvideoDemoApp() noexcept
{
	SetAppID(_T("RtvideoDemo.AppID.NoVersion"));
}
CRtvideoDemoApp theApp;
BOOL CRtvideoDemoApp::InitInstance()
{
	m_pMainWnd = new CMainFrame();
	m_pMainWnd->SetWindowText(L"1080P高清视频会议");
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}


void CRtvideoDemoApp::OnFinalRelease()
{	
	CWinApp::OnFinalRelease();
}
