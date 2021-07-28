#pragma once
#include "afxwin.h"
#include "afxdialogex.h"

// CRoomSettingDlg 对话框

class CRoomSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRoomSettingDlg)

public:
	CRoomSettingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRoomSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROOMSETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString _RoomID;
	CString _token;
	CString _peerName;
	CString _serverAddr;
	int _serverPort;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
