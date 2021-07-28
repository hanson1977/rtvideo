
#pragma once
#include <SDKDDKVer.h>
#include <afxwin.h>         
#include <afxext.h>        
#include "resource.h"   
#include <locale>
#include "shinevv.h"
static wchar_t* CStr2WStr(const char* CStr)
{
	// 长度设置
	size_t len = strlen(CStr) + 1;
	size_t converted = 0;
	// 准备转换的对象
	wchar_t *WStr;
	WStr = (wchar_t*)malloc(len * sizeof(wchar_t));
	//_wsetlocale(LC_ALL, "");
	// 转换
	int error = mbstowcs_s(&converted, WStr, len, CStr, _TRUNCATE);
	//printf("CStr2WStr converted = %d error = %d\n", converted, error);
	// 返回
	return WStr;
}
static char* WStr2Cstr(wchar_t* WStr)
{
	size_t len = wcslen(WStr) + 1;
	//printf("size_len = %d\n", len);
	size_t converted = 0;

	char *CStr = NULL;

	CStr = (char*)malloc(len * sizeof(char));
	_wsetlocale(LC_ALL, L"zh-CN");
	int error = wcstombs_s(&converted, CStr, len, WStr, _TRUNCATE);

	//printf("converted = %d error = %d\n", converted, error);
	return CStr;
}

class CRtvideoDemoApp : public CWinApp
{
public:
	CRtvideoDemoApp() noexcept;
	//sdk instance
	void* _instance = NULL;
	//摄像头索引
	int _current_capture_idx = 0;
	//当前摄像头能力索引
	int _cur_capture_capability_idx = 0;

	int _capture_width = 1920;
	int _capture_height = 1080;
	int _capture_fps = 25;
	int _videoBitRate = 1500;

// 重写
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
	virtual void OnFinalRelease();
};
extern CRtvideoDemoApp theApp;
