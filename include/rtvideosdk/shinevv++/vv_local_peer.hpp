#ifndef __VV_LOCAL_PEER__HPP__
#define __VV_LOCAL_PEER__HPP__
#include "shinevv.h"
class VVLocalPeer {
	//关闭麦克风
	virtual void MuteMic(bool mute) = 0;
	//关闭摄像头
	virtual void MuteCamera(bool mute) = 0;
	//录制
	virtual void StartRecord() = 0;
	//停止录制
	virtual void StopRecord() = 0;
	//直播
	virtual void StartPush(const char* rtmpUrl) = 0;
	//停止直播
	virtual void StopPush() = 0;
	//广播消息
	virtual void BroadcastMsg(const char* msg) = 0;
	//设置头像
	virtual void SetImage(const char* imgUrl) = 0;
	//设置昵称
	virtual void SetDisplayName(const char* dispName) = 0;
	//设置本地ID
	virtual void SetPeerId(const char* peerId) = 0;
public:
	void SetLocalPeer(const char* peerId, const char* disp_name, int bitRate) {
		strcpy((char*)_config._peer_id, peerId);
		strcpy((char*)_config._display_name, disp_name);
		_config._bitRate = bitRate;
	}
public:
	// define peer
	struct Config {
	public:
		Config() {};
		const char _peer_id[MAX_STRING_LEN] = { 0 };
		const char _display_name[MAX_STRING_LEN] = { 0 };
		const char _role[MAX_STRING_LEN] = "student";
		const char _device[MAX_STRING_LEN] = "WindowsPC";
		int _bitRate = 1800;
	}_config;
};

#endif