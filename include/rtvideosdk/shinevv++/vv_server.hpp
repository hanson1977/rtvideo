#ifndef __VV_SERVER_HPP__
#define __VV_SERVER_HPP__
class VVServer {
public:
	//连接服务器
	virtual void Connect(const char* room = 0, const char* token = 0, const char* server = 0, int port = 0) = 0;
	//断开连接
	virtual void DisConnect() = 0;
	//是否链接
	virtual bool IsConnected(int& errCode, const char* & errMsg) = 0;

	//设置夫服务器
	void SetServer(const char* server, int serverPort) {
		strcpy((char*)_server_config._server_ip, server);
		_server_config._server_port = serverPort;
	}
public:
	// vvserver define
	struct Config {
		const char _server_ip[256] = { 0 };
		int _server_port = 443;
		// timeout setting
		int _timeout_ms = 10000;
		bool _is_ping = true;
		bool _is_answer_server_ping = true;
		// second
		bool _ping_interval = 3;
		// auto reconnect
		bool _auto_reconnect = true;
		// auto reconnect interval
		int _auto_reconnect_interval = 10;
		bool _write_signal_msg = true;
	}_server_config;
}; 
#endif