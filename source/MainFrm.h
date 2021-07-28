#pragma once
#include "afxwin.h"
#include "afxdialogex.h"
#include "CRoomSettingDlg.h"
#include "shinevv.h"
#include <map>
class CMainFrame : public CFrameWnd
{	
public: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)
	CMenu m_menu;
	CRoomSettingDlg m_roomSetting;
	std::map<std::string, HWND> _windows;
// 实现
public:
	virtual ~CMainFrame();
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCamStart();
	afx_msg void OnCamStop();

	afx_msg void OnLogin();
	afx_msg void OnSetting();
	afx_msg void OnLogout();
	afx_msg void OnDevicechk();
	afx_msg LRESULT OnServerConnected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnServerDisConnected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPeerConsumer(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnConsumerClosed(WPARAM wParam, LPARAM lParam);
};


