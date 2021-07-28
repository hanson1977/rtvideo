#ifndef __SHINEVV__HPP_INC__HH_
#define __SHINEVV__HPP_INC__HH_
#include "shinevv.h"
#include "shinevv++/vv_server.hpp"
#include "shinevv++/vv_device.hpp"
#include "shinevv++/vv_room.hpp"
#include "shinevv++/vv_peer.hpp"
#include "shinevv++/vv_local_peer.hpp"
#include "shinevv++/vv_listener.hpp"
class SHINEVVAPI ShinevvFactory {
 public:
  static ShinevvFactory* Create(ShineVVListener* listener);
  static ShinevvFactory* Get();
  static void Destroy(ShinevvFactory* apiInter);
 public:
  //VVServer API interface
  VVServer* GetVVServer();
  //VVRoom API
  VVRoom* GetVVRoom();
  //VVDevice
  VVDevice* GetVVDevice();
  //LocalPeer
  VVLocalPeer* GetVVLocalPeer();
  //VVPeer
  virtual VVPeer* GetVVPeer(const char* peer_id)=0;
};
#endif