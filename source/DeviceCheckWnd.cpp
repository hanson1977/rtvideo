// DeviceCheckWnd.cpp: 实现文件
#include "RtvideoDemo.h"
#include "DeviceCheckWnd.h"
#include "afxdialogex.h"


// CDeviceCheckWnd 对话框

IMPLEMENT_DYNAMIC(CDeviceCheckWnd, CDialogEx)

CDeviceCheckWnd::CDeviceCheckWnd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEVICECHECK, pParent)
	, m_videoBitRate(0)
{

}

CDeviceCheckWnd::~CDeviceCheckWnd()
{
	if (_camera.get()) {
		_camera->Stop();
		_camera->Release();
		_camera.release();
	}
}

void CDeviceCheckWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VIDS, m_videoDevices);
	DDX_Control(pDX, IDC_COMBO_CAPS, m_videoCaps);
	DDX_Control(pDX, IDC_VIDEO, m_videoRenderWnd);
	DDX_Text(pDX, IDC_VIDEO_BPS, m_videoBitRate);
}


BEGIN_MESSAGE_MAP(CDeviceCheckWnd, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDS, &CDeviceCheckWnd::OnCbnSelchangeComboVids)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CDeviceCheckWnd::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDeviceCheckWnd::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPS, &CDeviceCheckWnd::OnCbnSelchangeComboCaps)
END_MESSAGE_MAP()


BOOL CDeviceCheckWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_sDeviceCnt = vvdevice_get_video_devices(theApp._instance, m_sDeviceInfos);
	for (int i = 0; i < m_sDeviceCnt; i++) {
		wchar_t* devName = CStr2WStr(m_sDeviceInfos[i].pDeviceName);
		int idx=m_videoDevices.AddString(devName);
		free(devName);
	}
	m_videoDevices.SetCurSel(theApp._current_capture_idx);
	this->m_videoBitRate = theApp._videoBitRate;
	//設置
	OnCbnSelchangeComboVids();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

std::string ShineVideoCapbility2String(vv_video_capability& cap) {
	char buffer[256] = { 0 };
	sprintf(buffer, "%dx%d/%d/%s", cap.width, cap.height, cap.maxFps, cap.videoType);
	return buffer;
}

void CDeviceCheckWnd::OnCbnSelchangeComboVids()
{
	int idx = m_videoDevices.GetCurSel();
	//展示能力列表
	m_videoCaps.ResetContent();
	int cursel = 0;
	
	for (int j = 0; j<m_sDeviceInfos[idx].nNumCaps; j++) {
		vv_video_capability& cap = m_sDeviceInfos[idx].capbilities[j];
		wchar_t* capString = CStr2WStr(ShineVideoCapbility2String(cap).c_str());
		int idx=m_videoCaps.AddString(capString);
		if (cap.width == theApp._capture_width && cap.height == theApp._capture_height) {
			cursel = j;
		}
		m_videoCaps.SetItemData(idx, (DWORD_PTR)&cap);
		free(capString);
	}
	
	if (_camera.get()) {
		_camera->Stop();
		_camera->Release();		
		_camera.release();
	}
	m_videoCaps.SetCurSel(cursel);
	if (idx != theApp._current_capture_idx) {		
		vvdevice_remove_capture_preview(theApp._instance, m_videoRenderWnd.m_hWnd);		
		_camera.reset(WebrtcCamera::Create(idx, m_videoRenderWnd.m_hWnd));
		_camera->Start();
	}
	else {
		vvdevice_add_capture_preview(theApp._instance, m_videoRenderWnd.m_hWnd);
	}
}

void CDeviceCheckWnd::OnClose()
{
	if (_camera.get()) {
		_camera->Stop();
		_camera->Release();
		_camera.release();
	}
	CDialogEx::OnClose();
}


void CDeviceCheckWnd::OnBnClickedOk()
{
	UpdateData();
	if (_camera.get()) {
		_camera->Stop();
		_camera->Release();
		_camera.release();
	}
	else {
		vvdevice_remove_capture_preview(theApp._instance, m_videoRenderWnd.m_hWnd);
	}
	//save the data
	theApp._current_capture_idx = m_videoDevices.GetCurSel();
	theApp._cur_capture_capability_idx = m_videoCaps.GetCurSel();
	theApp._videoBitRate = this->m_videoBitRate;	
	theApp._capture_width = m_sDeviceInfos[theApp._current_capture_idx].capbilities[theApp._cur_capture_capability_idx].width;
	theApp._capture_height = m_sDeviceInfos[theApp._current_capture_idx].capbilities[theApp._cur_capture_capability_idx].height;
	theApp._capture_fps = m_sDeviceInfos[theApp._current_capture_idx].capbilities[theApp._cur_capture_capability_idx].maxFps;
		
	CDialogEx::OnOK();
}


void CDeviceCheckWnd::OnBnClickedCancel()
{
	if (_camera.get()) {
		_camera->Stop();
		_camera->Release();
		_camera.release();
	}
	CDialogEx::OnCancel();
}

void CDeviceCheckWnd::OnCbnSelchangeComboCaps()
{
	int idx = m_videoCaps.GetCurSel();
	vv_video_capability* cap=(vv_video_capability*)m_videoCaps.GetItemData(idx);
	if (cap->width == 1920 && cap->height == 1080) {
		m_videoBitRate = 1800;
	}
	else if (cap->width == 1280 && cap->height == 720) {
		m_videoBitRate = 1200;
	}
	else if (cap->width == 640 && (cap->height == 480 || cap->height == 360)) {
		m_videoBitRate = 300;
	}
	else 
		m_videoBitRate = 800;
	UpdateData(FALSE);
}
