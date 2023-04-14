#include "Header.h"
#include "TCPConnect.h"
#include "SDL_Print12864.h"


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
	in_addr address;
	int nAdapter = 0;

	if (gethostname(szHostname, sizeof(szHostname)) == 0)
	{
		if ((pHostent = (PHOSTENT)gethostbyname(szHostname)) != NULL)
		{
			address = *((struct in_addr *)*pHostent->h_addr_list);
		}
	}

	return address;
}


// 0:Running  1:Succeed  2:Failed
DWORD WINAPI AcceptThread(LPVOID p)
{
	TCPConnect *Parent = (TCPConnect*)p; Parent->AcceptThreadVal = 0;
	while (Parent->AcceptThreadVal == 0)
	{
		Parent->clntSocket = accept(Parent->ConnectSocket, (SOCKADDR*)&(Parent->clientAddr), &(Parent->client_addr_size));
		if (Parent->clntSocket == INVALID_SOCKET) {
			Parent->AcceptThreadVal = 2;
		}
		else
		{
			getpeername(Parent->ConnectSocket, (SOCKADDR*)&(Parent->clientAddr), &(Parent->client_addr_size));
			Parent->AcceptThreadVal = 1;
		}
	}
	return 0;
}

// 0:Running  1:Succeed  2:Failed
DWORD WINAPI ConnectThread(LPVOID p)
{
	TCPConnect *Parent = (TCPConnect*)p;
	Parent->ConnectThreadVal = 0;
	while (Parent->ConnectThreadVal == 0)
	{
		if (connect(Parent->ConnectSocket, (SOCKADDR*)&(Parent->clientAddr), sizeof(Parent->clientAddr)) == SOCKET_ERROR) {
			closesocket(Parent->ConnectSocket);
			Parent->ConnectThreadVal = 2;
		}
		Parent->ConnectThreadVal = 1;
	}
	return 0;
}

// 0:Failed  1:Connecting
int TCPConnect::SocketConnect(in_addr ip, int port) {
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET) {
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
	ConnectThreadHWND = CreateThread(NULL, 0, ConnectThread, this, 0, &ConnectThreadID);
	return 1;

}

int TCPConnect::SocketClose() {
	if (ConnectSocket != -1)closesocket(ConnectSocket);
	if (clntSocket != -1)closesocket(clntSocket);
	return 0;
}

// 0:Failed  1:Accepting
int TCPConnect::SocketServer(in_addr addr,int port) {
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	DWORD tcp_error = WSAGetLastError();
	if (ConnectSocket == INVALID_SOCKET) {
		return 0;
	}

	serverService.sin_family = AF_INET;
	serverService.sin_addr.s_addr = inet_addr(inet_ntoa(addr));
	serverService.sin_port = htons(port);

	int iResult;

	iResult = bind(ConnectSocket, (struct sockaddr*)&serverService, server_addr_size);
	if (iResult == SOCKET_ERROR)return 0;

	iResult = listen(ConnectSocket, 5);
	if (iResult == SOCKET_ERROR)return 0;

	AcceptThreadHWND = CreateThread(NULL, 0, AcceptThread, this, 0, &AcceptThreadID);

	return 1;
}
int TCPConnect::ServerSend(void* data, int len){
	return send(clntSocket, (char*)data, len, 0);
}
int TCPConnect::ServerRecv(void* data, int len) {
	return recv(clntSocket, (char*)data, len, 0);
}
int TCPConnect::ClientSend(void* data, int len) {
	return send(ConnectSocket, (char*)data, len, 0);
}
int TCPConnect::ClientRecv(void* data, int len) {
	return recv(ConnectSocket, (char*)data, len, 0);
}