#include "Header.h"
#include "ShootTCP_Connect.h"
#include "ShootTCP_Print.h"


TCPConnect::TCPConnect()
{
}


TCPConnect::~TCPConnect()
{
}


in_addr TCPConnect::GetmyIP()
{
	char szHostname[100];
	HOSTENT* pHostent;
	int nAdapter = 0;

	gethostname(szHostname, sizeof(szHostname));
	pHostent = gethostbyname(szHostname);
	return *((struct in_addr *)*pHostent->h_addr_list);
}


// 0:Running  1:Succeed  2:Failed
DWORD WINAPI AcceptThread(LPVOID p)
{
	TCPConnect *Parent = (TCPConnect*)p;
	char* returns = (char*)p + 4;
	*returns = 0;
	while (*returns == 0)
	{
		Parent->clntSocket = accept(Parent->ConnectSocket, (SOCKADDR*)&(Parent->clientAddr), &(Parent->client_addr_size));
		if (Parent->clntSocket == INVALID_SOCKET) {
			*returns = 2;
		}
		else
		{
			getpeername(Parent->ConnectSocket, (SOCKADDR*)&(Parent->clientAddr), &(Parent->client_addr_size));
			Sleep(200);
			*returns = 1;
		}
	}
	return 0;
}

// 0:Running  1:Succeed  2:Failed
DWORD WINAPI ConnectThread(LPVOID p)
{
	TCPConnect *Parent = (TCPConnect*)p;
	char* returns = (char*)p + 4;
	*returns = 0;
	while (*returns == 0)
	{
		if (connect(Parent->ConnectSocket, (SOCKADDR*)&(Parent->clientAddr), sizeof(Parent->clientAddr)) == SOCKET_ERROR) {
			closesocket(Parent->ConnectSocket);
			WSACleanup();
			*returns = 2;
		}
		*returns = 1;
	}
	return 0;
}

// 0:Failed  1:Connecting
int TCPConnect::SocketConnect(in_addr ip,int port) {
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}

	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server to be connected to.
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_addr = ip;
	clientAddr.sin_port = htons(port);

	//----------------------
	// Connect to server.
	void *pointer[2] = { this,&ConnectThreadVal };
	ConnectThreadHWND = CreateThread(NULL, 0, ConnectThread, pointer, 0, &ConnectThreadID);
	return 1;

}


// 0:Failed  1:Accepting
int TCPConnect::SocketServer(int port) {
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}

	serverService.sin_family = AF_INET;
	serverService.sin_addr.s_addr = inet_addr(inet_ntoa(GetmyIP()));
	serverService.sin_port = htons(port);

	int iResult;

	iResult = bind(ConnectSocket, (struct sockaddr*)&serverService, server_addr_size);
	if (iResult == SOCKET_ERROR)return 0;

	iResult = listen(ConnectSocket, 5);
	if (iResult == SOCKET_ERROR)return 0;

	void *pointer[2] = { this,&AcceptThreadVal };
	AcceptThreadHWND = CreateThread(NULL, 0, AcceptThread, pointer, 0, &AcceptThreadID);

	return 1;
}
int TCPConnect::ServerSend(void* data, int len) {
	return send(ConnectSocket, (char*)data, len, 0);
}
int TCPConnect::ServerRecv(void* data, int len) {
	return recv(ConnectSocket, (char*)data, len, 0);
}int TCPConnect::ClientSend(void* data, int len) {
	return send(clntSocket, (char*)data, len, 0);
}
int TCPConnect::ClientRecv(void* data, int len) {
	return recv(clntSocket, (char*)data, len, 0);
}