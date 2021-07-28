// MainFrm.cpp: CMainFrame 类的实现
#include "RtvideoDemo.h"
#include "MainFrm.h"
#include "resource.h"
#include "shinevv.h"
#include <string>
#include <codecvt>
#include "DeviceCheckWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_NEW_REMOTEWINDOWS WM_USER+0x1000
#define MSG_SERVER_CONNECTED	WM_USER + 1024
#define MSG_SERVER_DISCONNECTED	MSG_SERVER_CONNECTED + 1
#define MSG_PEER_CONSUMER		MSG_SERVER_CONNECTED + 2
#define MSG_CONSUMER_CLOSED		MSG_SERVER_CONNECTED + 3

//callback for connection
void OnServerConnected(void* userdata) {
	CMainFrame* mainWnd = (CMainFrame*)userdata;
	mainWnd->PostMessage(MSG_SERVER_CONNECTED);	
}
void OnServerDisConnected(void* userdata, int errCode, const char* errMsg) {
	CMainFrame* mainWnd = (CMainFrame*)userdata;
	static char strErrMsg[256] = { 0 };
	strcpy(strErrMsg, errMsg);
	mainWnd->PostMessage(MSG_SERVER_DISCONNECTED,errCode,(LPARAM)strErrMsg);
}
void OnRemotePeerConsumer(void* userdata, const char* peerId, const char* kind, void* consumer) {
	CMainFrame* mainWnd = (CMainFrame*)userdata;
	static char strPeer[256] = { 0 };
	strcpy(strPeer, peerId);
	if (strcmp(kind, "video") == 0) {
		mainWnd->PostMessage(MSG_PEER_CONSUMER, (WPARAM)strPeer, (LPARAM)consumer);
	}
}
void OnConsumerClosed(void* userdata, const char* consumerId, const char* kind, void* consumer) {
	CMainFrame* mainWnd = (CMainFrame*)userdata;
	static char strConsumer[256] = { 0 };
	strcpy(strConsumer, consumerId);
	if (strcmp(kind, "video") == 0) {
		mainWnd->PostMessage(MSG_CONSUMER_CLOSED, (WPARAM)strConsumer, (LPARAM)consumer);
	}
}
static shinevv_callbacks_t _g_callbacks = { OnServerConnected ,OnServerDisConnected,OnRemotePeerConsumer,OnConsumerClosed };

LRESULT CALLBACK WebRtcCreateWindowProc2(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		break;
	
	case WM_COMMAND:
		break;
	case WM_CLOSE:
	{
		//CloseWindow(hWnd);
		//::DestroyWindow(hWnd);
		break;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}
int WebRtcCreateWindow(HWND &hwndMain,HWND hParent, int winNum, int width, int height, wchar_t* pTitle)
{
	static HINSTANCE hinst = NULL;
	if (hinst == NULL) {

		hinst = GetModuleHandle(0);
		WNDCLASSEX wcx;
		wcx.hInstance = hinst;
		wcx.lpszClassName = TEXT("VideoRenderTest");
		wcx.lpfnWndProc = (WNDPROC)WebRtcCreateWindowProc2;
		wcx.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcx.lpszMenuName = NULL;
		wcx.cbSize = sizeof(WNDCLASSEX);
		wcx.cbClsExtra = 0;
		wcx.cbWndExtra = 0;
		wcx.hbrBackground = GetSysColorBrush(COLOR_3DFACE);

		// Register our window class with the operating system.
		// If there is an error, exit program.
		if (!RegisterClassEx(&wcx))
		{
			MessageBox(0, TEXT("Failed to register window class!"), TEXT("Error!"), MB_OK | MB_ICONERROR);
			return 0;
		}
	}

	// Create the main window.
	hwndMain = CreateWindowEx(
		0, // no extended styles
		TEXT("VideoRenderTest"), // class name
		pTitle, // window name
		WS_POPUP |WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
		800, // horizontal position
		0, // vertical position
		width, // width
		height, // height
		(HWND)hParent, // no parent or owner window
		(HMENU)NULL, // class menu used
		hinst, // instance handle
		NULL); // no window creation data

	if (!hwndMain)
		return -1;

	// Show the window using the flag specified by the program
	// that started the application, and send the application
	// a WM_PAINT message.

	ShowWindow(hwndMain, SW_SHOWDEFAULT);
	UpdateWindow(hwndMain);
	return 0;
}
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_CAM_START, &CMainFrame::OnCamStart)
	ON_COMMAND(ID_CAM_STOP, &CMainFrame::OnCamStop)
	ON_COMMAND(ID_LOGIN, &CMainFrame::OnLogin)
	ON_COMMAND(ID_SETTING, &CMainFrame::OnSetting)
	ON_COMMAND(ID_LOGOUT, &CMainFrame::OnLogout)
	ON_MESSAGE(MSG_SERVER_CONNECTED, &CMainFrame::OnServerConnected)
	ON_MESSAGE(MSG_SERVER_DISCONNECTED, &CMainFrame::OnServerDisConnected)
	ON_MESSAGE(MSG_PEER_CONSUMER, &CMainFrame::OnPeerConsumer)
	ON_MESSAGE(MSG_CONSUMER_CLOSED, &CMainFrame::OnConsumerClosed)
	ON_COMMAND(ID_DEVICECHK, &CMainFrame::OnDevicechk)
END_MESSAGE_MAP()
CMainFrame::CMainFrame() noexcept
{
	Create(NULL, L"MFC App1");	
}

CMainFrame::~CMainFrame()
{
	destroy_shinevv_instance(theApp._instance);
	theApp._instance = NULL;
}
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_menu.LoadMenu(IDR_MAINFRAME);
	this->SetMenu(&m_menu);	
	theApp._instance = create_shinevv_instance(&_g_callbacks, this);
	//配置服务器
	vvserver_set_server(theApp._instance,"v3.shinevv.com", 4443);
	//配置房间
	vvroom_set_room(theApp._instance, "152440", "8d2840889f239afd9de52ccc78f9b71b");
	
	vvlocal_set_peer(theApp._instance, "hansonxc", "hansonxc", 1800);

	//preview capture
	vvdevice_add_capture_preview(theApp._instance, this->GetSafeHwnd());
	//start capture
	vvdevice_start_capture(theApp._instance);
	return 0;
}

// CMainFrame 消息处理程序
void CMainFrame::OnCamStart()
{
	//start capture
	vvdevice_start_capture(theApp._instance);
}
void CMainFrame::OnCamStop()
{
	//start capture
	vvdevice_stop_capture(theApp._instance);
}

void CMainFrame::OnLogin()
{
	vvroom_join(theApp._instance);
}


void CMainFrame::OnSetting()
{
	m_roomSetting.DoModal();
}


void CMainFrame::OnLogout()
{
	vvroom_leave(theApp._instance);
	for (auto wnd : _windows) {		
		::CloseWindow(wnd.second);
		::DestroyWindow(wnd.second);
	}
	_windows.clear();
}
// CDeviceCheckWnd 消息处理程序


void CMainFrame::OnDevicechk()
{
	CDeviceCheckWnd  deviceChkDlg;
	if(deviceChkDlg.DoModal()==IDOK){
		vvdevice_reset_capture(theApp._instance, theApp._current_capture_idx, theApp._capture_width,
			theApp._capture_height, theApp._capture_fps);
		//need to add render by hand after reset capture
		vvdevice_add_capture_preview(theApp._instance, this->GetSafeHwnd());
	}
}
LRESULT CMainFrame::OnServerConnected(WPARAM wParam, LPARAM lParam) {
	AfxMessageBox(L"服务器连接已成功");
	return 0;
}
LRESULT CMainFrame::OnServerDisConnected(WPARAM wParam, LPARAM lParam) {
	int errCode = wParam;
	const char* errMsg = (const char*)lParam;
	if(errCode<0)
		AfxMessageBox(CString(L"连接失败:") + errMsg);
	else
		AfxMessageBox(L"服务器连接已断开");
	return 0;
}

LRESULT CMainFrame::OnPeerConsumer(WPARAM wParam, LPARAM lParam) {
	const char* strPeer = (const char*)wParam;
	void* consumer = (void*)lParam;
	HWND hwndCreate = NULL;
	if (strPeer != NULL && strlen(strPeer) > 0) {

		WebRtcCreateWindow(hwndCreate, m_hWnd, 0, 640,
			480, CStr2WStr(strPeer));
		shinevv_set_consumer_window(theApp._instance, consumer, hwndCreate);
	}
	_windows.insert(std::pair<std::string, HWND>(shinevv_consumer_get_id(consumer), hwndCreate));
	return 0;
}
LRESULT CMainFrame::OnConsumerClosed(WPARAM wParam, LPARAM lParam) {
	const char* strConsumer = (const char*)wParam;
	void* consumer = (void*)lParam;
	auto wnd = _windows.find(strConsumer);
	if (wnd != _windows.end()) {
		::CloseWindow(wnd->second);
		::DestroyWindow(wnd->second);
		_windows.erase(wnd);
	}
	return 0;
}