#pragma once
#include "afxwin.h"
#include "afxdialogex.h"
#include "shinevv.h"
#include "webrtc_camera.h"
// CDeviceCheckWnd 对话框

class CDeviceCheckWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CDeviceCheckWnd)

public:
	CDeviceCheckWnd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDeviceCheckWnd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEVICECHECK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	std::unique_ptr<WebrtcCamera> _camera;
	// 视频设备
	CComboBox m_videoDevices;
	// 视频能力集
	CComboBox m_videoCaps;
	// 视频渲染窗口
	CStatic m_videoRenderWnd;
	//device info
	vv_device_info m_sDeviceInfos[10] = { 0 };

	int m_sDeviceCnt = 0;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboVids();
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeComboCaps();
	// 视频发送带宽
	int m_videoBitRate;
};
