#ifndef __SHINEVV_INC__HH_
#define __SHINEVV_INC__HH_
#if defined(_WIN32) && defined(_SHINEVV_BUILD_DLL)
/* We are building SHINEVV as a Win32 DLL */
#define SHINEVVAPI __declspec(dllexport)
#elif defined(_WIN32) && defined(_SHINEVV_DLL)
/* We are calling SHINEVV as a Win32 DLL */
#define SHINEVVAPI __declspec(dllimport)
#elif defined(__GNUC__) && defined(_SHINEVV_BUILD_DLL)
/* We are building SHINEVV as a shared / dynamic library */
#define SHINEVVAPI __attribute__((visibility("default")))
#else
/* We are building or calling SHINEVV as a static library */
#define SHINEVVAPI
#endif

#include "string.h"

typedef void (*OnWsConnected)(void* userdata);
typedef void (*OnWsDisConnected)(void* userdata,int errCode,const char* errMsg);
typedef void(*OnPeerConsumer)(void* userdata,const char* peerId, const char* kind, void* consumer);
typedef void(*OnConsumerClose)(void* userdata, const char* consumerId, const char* kind, void* consumer);
// shinevv instance
typedef void* SHINEVV;
typedef struct shinevv_callbacks_t {
  // connected call back
  OnWsConnected _on_ws_connected;
  OnWsDisConnected _on_ws_disconnected;
  OnPeerConsumer _on_peer_consumer;
  OnConsumerClose _on_consumer_closed;
} shinevv_callbacks_t;

#define MAX_STRING_LEN 120
//视频设备能力
typedef struct _vv_video_capability {
	int width = 0;
	int height = 0;
	int maxFps = 0;
	char videoType[20] = { 0 };
}vv_video_capability;
//设备信息
typedef struct _vv_device_info {
	const char pDeviceName[256] = { 0 };
	int nDeviceIndex = 0;
	int nNumCaps = 0;
	vv_video_capability capbilities[50] = { 0 };
}vv_device_info;

#ifdef __cplusplus
extern "C" {
#endif
// create shinevv instance
SHINEVVAPI SHINEVV create_shinevv_instance(shinevv_callbacks_t* callbacks,void* userdata);
SHINEVVAPI void destroy_shinevv_instance(SHINEVV _shinevv);

SHINEVVAPI void vvserver_set_server(SHINEVV _shinevv,const char* server, int server_port);
SHINEVVAPI void vvserver_connect(SHINEVV _shinevv, const char* room, const char* token, const char* server, int port);
SHINEVVAPI void vvserver_disconnect(SHINEVV _shinevv);
SHINEVVAPI bool is_vvserver_connected(SHINEVV _shinevv, int& errCode, const char* & errMsg);

SHINEVVAPI void vvroom_set_room(SHINEVV _shinevv, const char* room_id, const char* token);
SHINEVVAPI void vvroom_join(SHINEVV _shinevv);
SHINEVVAPI void vvroom_leave(SHINEVV _shinevv);

SHINEVVAPI void vvlocal_set_peer(SHINEVV _shinevv, const char* peer_id, const char* display_name, int bitRate);
//devices manager
SHINEVVAPI int vvdevice_get_video_devices(SHINEVV shinevv, vv_device_info deviceInfo[]);
//preview mananger
SHINEVVAPI void vvdevice_add_capture_preview(SHINEVV shinevv,void* window);
SHINEVVAPI void vvdevice_remove_capture_preview(SHINEVV shinevv,void* window);
SHINEVVAPI void vvdevice_reset_capture(SHINEVV shinevv, int idx, int width, int height, int fps);
SHINEVVAPI void vvdevice_start_capture(SHINEVV shinevv);
SHINEVVAPI void vvdevice_stop_capture(SHINEVV shinevv);



SHINEVVAPI const char* shinevv_consumer_get_id(void* consumer);

SHINEVVAPI void shinevv_set_consumer_window(SHINEVV _shinevv, void* consumer,void* window);


#ifdef __cplusplus
};
#endif
#endif