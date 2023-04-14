#pragma once
class TCPConnect
{
public:
	TCPConnect();
	~TCPConnect();
	in_addr GetmyIP();
	SOCKET ConnectSocket;
	SOCKET clntSocket = INVALID_SOCKET;
	struct sockaddr_in serverService;
	struct sockaddr_in clientAddr;
	int     server_addr_size = sizeof(serverService);
	int     client_addr_size = sizeof(clientAddr);
	int SocketClose();
	int SocketConnect(in_addr ip, int port);
	int SocketServer(in_addr addr,int port);
	int ServerSend(void* data, int len);
	int ServerRecv(void* data, int len);
	int ClientSend(void* data, int len);
	int ClientRecv(void* data, int len);
	char AcceptThreadVal;
	char ConnectThreadVal;
	DWORD AcceptThreadID;
	HANDLE AcceptThreadHWND;
	DWORD ConnectThreadID;
	HANDLE ConnectThreadHWND;
};