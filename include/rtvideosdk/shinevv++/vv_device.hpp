#ifndef __VV__DEVICE_HPP__
#include "shinevv.h"
#define __VV__DEVICE_HPP__

class VVDevice {
public:
	VVDevice() {};
	//重置摄像头
	virtual void ResetCapture(int idx, int width, int height, int fps) = 0;
	//开启摄像头
	virtual void StartCapture() = 0;
	//停止摄像头
	virtual void StopCapture() = 0;
	//增加摄像头预览窗口
	virtual void AddCapturePreview(void* window) = 0;
	//移除摄像头预览
	virtual void RemoveCapturePreview(void* window) = 0;
	//devices manager
	virtual int GetVideoDevices(vv_device_info deviceInfo[]) = 0;
	//切换摄像头,桌面共享，RTSP摄像头等其他源
	virtual void SetVideoSource(const char* sourceUrl) = 0;
	//音频设备
	virtual int GetAudioDevices(vv_device_info deviceInfo[]) = 0;
public:
	void SetCameraCapture(int idx, int width, int height, int fps) {
		_config._index = idx;
		_config._width = width;
		_config._height = height;
		_config._fps = fps;
	}
public:
	struct Config {
	public:
		Config() {};
		int _index = 0;
		int _width = 1920;
		int _height = 1080;
		int _fps = 25;
	}_config;
};

#endif
