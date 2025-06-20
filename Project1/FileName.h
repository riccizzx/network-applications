#pragma once

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define port 9909 // 127.0.0.1
//fd_set fr, fw, fe;

class Net {
public:
	void initialize();
	void createSocket();
	void bindSocket();
	void run();
	void processRequest();

private:
	void closeSocket();
	SOCKET serverSock;
	SOCKET clientSock;
	int nRet =0;
};