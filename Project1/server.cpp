#include "FileName.h"

FD_SET fr, fw, fe;
int nMaxFd;
//initialize winsock API
void Net::initialize() {
	//int nRet = 0;
	WSADATA ws;
	int start;
	WORD version = MAKEWORD(2, 2);
	start = WSAStartup(version, &ws);
	if (start != 0) {
		std::cout << "ERROR!\n";
	}
	else {
		std::cout << "INITIALIZE SUCEFFUL\n";
	}
}

//create server socket
void Net::createSocket() {
	//SOCKET serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSock == INVALID_SOCKET) {
		std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "Socket created successfully." << std::endl;
	}
}

//bind and config socket ip
void Net::bindSocket() {
	Net net;
	
	//addrrs config
	sockaddr_in srv;
	srv.sin_family = AF_INET;
	srv.sin_port = htons(port);
	srv.sin_addr.s_addr = INADDR_ANY;
	memset(&(srv.sin_zero), 0, 0);
	//memset(&(srv.sin_zero), 0, 8);

	//bind the socket bind (sock, (sockaddr*) &serveraddr, sizeof(serveraddr))
	nRet = bind(serverSock, (sockaddr*)&srv, sizeof(srv));
	if (nRet == SOCKET_ERROR) {
		std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
		closesocket(serverSock);
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "Socket bind successfully to local port." << std::endl;
	}

	//listen for connections
	nRet = listen(serverSock, SOMAXCONN);
	if (nRet == SOCKET_ERROR) {
		std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
		closesocket(serverSock);
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "Socket is now listening for connections." << std::endl;
	}
	
	nMaxFd = serverSock + 1; // set the maximum file descriptor for select
	FD_ZERO(&fr); // clear the read set
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;// set timeout to 0 seconds

	while(1){
		FD_ZERO(&fr, &fw, &fe); // clear all sets
		FD_SET(serverSock, &fr); // add server socket to the read set
		FD_SET(serverSock, &fe); // add server socket to the exception set

		std::cout << fr.fd_count << " sockets in read set." << std::endl;

		nRet = select(nMaxFd + 1, &fr, &fw, &fe, &tv);
		if (nRet == SOCKET_ERROR) {
			std::cerr << "Select failed with error: " << WSAGetLastError() << std::endl;
			closesocket(serverSock);
			exit(EXIT_FAILURE);
		}
		else if (nRet == 0) {
			std::cout << "No sockets ready for reading." << std::endl;
		}
		else {
			std::cout << nRet << " sockets are ready for reading." << std::endl;
			exit(EXIT_FAILURE);
		}
		std::cout << fr.fd_count << " sockets in read set after select." << std::endl;
		Sleep(2000);
	}
	std::cout << "\n" << "\n";

	//accept a connection
	//clientSock = accept(serverSock, NULL, NULL);

}

void Net::run() {
	Net net;
	net.initialize();
	net.createSocket();
	net.bindSocket();
	std::cout << "Network operations completed." << std::endl;
	return;
}