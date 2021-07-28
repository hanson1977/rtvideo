// CRoomSettingDlg.cpp: 实现文件
//
#include "resource.h"
#include "CRoomSettingDlg.h"
#include "afxdialogex.h"
#include "RtvideoDemo.h"
#include <codecvt>

// CRoomSettingDlg 对话框

IMPLEMENT_DYNAMIC(CRoomSettingDlg, CDialogEx)

CRoomSettingDlg::CRoomSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ROOMSETTING, pParent)
	, _RoomID(_T("152440"))
	, _token(_T("8d2840889f239afd9de52ccc78f9b71b"))
	, _peerName(_T("hansonxc"))
	, _serverAddr(_T("v3.shinevv.com"))
	, _serverPort(4443)
{

}

CRoomSettingDlg::~CRoomSettingDlg()
{
}

void CRoomSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ROOMID, _RoomID);
	DDX_Text(pDX, IDC_TOKEN, _token);
	DDX_Text(pDX, IDC_PEERNAME, _peerName);
	DDX_Text(pDX, IDC_SERVER, _serverAddr);
	DDX_Text(pDX, IDC_SERVERPORT, _serverPort);
}


BEGIN_MESSAGE_MAP(CRoomSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRoomSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRoomSettingDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CRoomSettingDlg 消息处理程序
BOOL CRoomSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	int errCode;
	const char* errMsg = NULL;
	bool isConnected = is_vvserver_connected(theApp._instance, errCode, errMsg);
	if (isConnected){
		GetDlgItem(IDC_CONNSTAT)->SetWindowText(L"已连接");
	}		
	else if (errCode < 0) {
		GetDlgItem(IDC_CONNSTAT)->SetWindowText(CString(errMsg));
	}else
		GetDlgItem(IDC_CONNSTAT)->SetWindowText(L"已断开");

	GetDlgItem(IDOK)->EnableWindow(!isConnected);
	GetDlgItem(IDCANCEL)->EnableWindow(isConnected);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void CRoomSettingDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
	std::string roomId = convert.to_bytes(_RoomID);
	std::string peerName = convert.to_bytes(_peerName);
	std::string server = convert.to_bytes(_serverAddr);
	std::string token = convert.to_bytes(_token);
	//连接
	vvserver_connect(theApp._instance, roomId.c_str(), token.c_str(), server.c_str(), _serverPort);

	CDialogEx::OnOK();
}


void CRoomSettingDlg::OnBnClickedCancel()
{
	UpdateData(FALSE);
	//断开连接
	vvserver_disconnect(theApp._instance);
	CDialogEx::OnCancel();
}
