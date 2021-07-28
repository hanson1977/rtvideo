#ifndef __VV_ROOM__HPP_
#define __VV_ROOM__HPP_
#include "shinevv.h"
class VVRoom {
public:
	VVRoom() {};
	//加入房间
	virtual bool JoinRoom() = 0;
	//离开房间
	virtual void LeaveRoom() = 0;
	//全体禁音
	virtual void MuteRoomAudio(bool mute) = 0;
	//全体禁视
	virtual void MuteRoomVideo(bool mute) = 0;
public:
	void SetRoom(const char* room, const char* token) {
		strcpy((char*)_config._room_id, room);
		strcpy((char*)_config._token, token);
	}
	struct Config {
	public:
		Config() {};
		const char _room_id[MAX_STRING_LEN] = { 0 };
		const char _token[MAX_STRING_LEN] = { 0 };
	}_config;
}; 
#endif