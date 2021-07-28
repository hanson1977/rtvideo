#ifndef __VV__PEER__HPP__
#define __VV__PEER__HPP__
#include "string.h"
class ShinevvFactory;
class VVPeer {
public:
	//构造函数
	VVPeer(ShinevvFactory* factory,const char* jsonPeer);
	~VVPeer();
	
public:
	//静音
	virtual void MutePeerAudio(bool mute);
	//禁视
	virtual void MutePeerVideo(const char* type, bool mute);
	//聊天
	virtual void Chat(const char* msg);
	//设置视频窗口
	virtual void SetPeerVideoWindow(const char* type, void* wnd);
public:
	const char* ToJsonString();
	void Update(const char* jsonPeer);
public:
	ShinevvFactory* _factory = NULL;
	const char* _peerName=NULL;
	const char* _displayName=NULL;
	const char* _role = NULL;
	const char* _userObject=NULL;
	const char* _source = NULL;;
};
#endif
