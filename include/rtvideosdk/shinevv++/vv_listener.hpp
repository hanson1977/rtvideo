#ifndef __VV__LISTENER__HPP__
#define __VV__LISTENER__HPP__
#include "shinevv.h"
#include "shinevv++/vv_peer.hpp"
class ShineVVListener{
public:
	ShineVVListener(shinevv_callbacks_t* callbacks, void* userdata) : _callbacks(callbacks), _userdata(userdata){};
	ShineVVListener() {};
public:
	shinevv_callbacks_t* _callbacks = NULL;
	void* _userdata = NULL;

public:
	virtual void OnFailure(const char* errClass, int errCode, const char* errDesc){
	};
	virtual void OnPeerJoined(VVPeer* peer){
	};
	virtual void OnPeerLeaved(VVPeer* peer){
	};
	virtual void OnPeerConsumer(const char* peer, const char* kind,void *consumer){
		if (_callbacks&&_callbacks->_on_peer_consumer)
			_callbacks->_on_peer_consumer(_userdata,peer, kind, consumer);
	}
	virtual void OnConsumerClose(const char* consumer_id, const char* kind, void* consumer){
		if (_callbacks&&_callbacks->_on_consumer_closed)
			_callbacks->_on_consumer_closed(_userdata, consumer_id, kind, consumer);
	}
};
#endif
