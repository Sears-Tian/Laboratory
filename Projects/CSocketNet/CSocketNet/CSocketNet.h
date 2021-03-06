/*
	2018.12.11
	自定义封装类CSocketNet实现 TCP/	UDP Socket通讯，仿照 MFC CSocket类设计
*/
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define ADDRESS_SIZE 20		//储存地址的内存空间大小

class CSocketNet
{
public:
	CSocketNet()
	{
		m_socket = INVALID_SOCKET;
		//加载套接字库
		WSADATA wsadata;
		WSAStartup(MAKEWORD(2, 2), &wsadata);
	}
	virtual~CSocketNet()
	{
		Close();
	}
	//返回：1-成功；0-失败
	int Create(int socketPort = 0, int socketType = SOCK_STREAM, const char* socketAddress = nullptr);
	// TCP
	int Listen(int backlog = SOMAXCONN)
	{
		return !listen(m_socket, backlog);
	}
	int Accept(CSocketNet& socketConn, char* addrConn = nullptr, int* portConn = nullptr);
	int Connect(const char* hostAddress, int hostPort);
	int Send(const void* buf, int buflen, int flags = 0)
	{	
		return send(m_socket, (char*)buf, buflen, flags);
	}
	int Receive(void* buf, int buflen, int flags = 0)
	{
		return recv(m_socket, (char*)buf, buflen, flags);
	}
	// UDP
	int SendTo(const void * buf, int buflen, const char * hostAddress, int hostPort, int flags = 0);
	int ReceiveFrom(void * buf, int buflen, char * socketAddress, int& socketPort, int flags = 0);

	int GetSockName(char* socketAddress, int& socketPort);
	int GetPeerName(char* peerAddress, int& peerPort);

	void Close()
	{
		closesocket(m_socket);		/// int closesocket(_In_ SOCKET s);
		WSACleanup();
		m_socket = INVALID_SOCKET;
	}

	BOOL Attach(SOCKET sock)
	{
		if (INVALID_SOCKET != sock)
			return FALSE;
		m_socket = sock;
		return TRUE;
	}
	SOCKET Detach()
	{
		SOCKET sock = m_socket;
		m_socket = INVALID_SOCKET;
		return sock;
	}
private:
	SOCKET m_socket;
};

int CSocketNet::Create(int socketPort, int socketType, const char * socketAddress)
{	// socket & bind
	int protocol = 0;
	//switch (socketType)
	//{
	//case SOCK_STREAM: protocol = IPPROTO_TCP; break;
	//case SOCK_DGRAM: protocol = IPPROTO_UDP; break;
	//default: break;
	//}
	m_socket = socket(AF_INET, socketType, protocol);
	if (INVALID_SOCKET == m_socket)
		return 0;

	//SOCKADDR_IN name;
	//name.sin_family = AF_INET;
	//name.sin_port = htons(socketPort);
	struct sockaddr_in name = { AF_INET, htons(socketPort) };
	if(socketAddress)
		name.sin_addr.s_addr = inet_addr(socketAddress);
	return !bind(m_socket, (struct sockaddr*)&name, sizeof(struct sockaddr_in));
}

inline int CSocketNet::Accept(CSocketNet & socketConn, char* addrConn, int* portConn)
{	// accept
	struct sockaddr_in addr;
	int addrlen = sizeof(struct sockaddr_in);
	socketConn.m_socket = accept(m_socket, (struct sockaddr*)&addr, &addrlen);
	if (INVALID_SOCKET == socketConn.m_socket)
		return 0;

	if(addrConn)
		strcpy_s(addrConn, ADDRESS_SIZE, inet_ntoa(addr.sin_addr));
	if (portConn)
		*portConn = addr.sin_port;
	return 1;
}

inline int CSocketNet::Connect(const char * hostAddress, int hostPort)
{
	//struct sockaddr_in name;
	//name.sin_family = AF_INET;
	//name.sin_port = htons(hostPort);
	struct sockaddr_in name = { AF_INET, htons(hostPort) };
	name.sin_addr.s_addr = inet_addr(hostAddress);
	int namelen = sizeof(struct sockaddr_in);
	return !connect(m_socket, (struct sockaddr*)&name, namelen);
}

inline int CSocketNet::SendTo(const void * buf, int buflen, const char * hostAddress, int hostPort, int flags)
{
	struct sockaddr_in to = { AF_INET, htons(hostPort) };
	to.sin_addr.s_addr = inet_addr(hostAddress);
	int tolen = sizeof(struct sockaddr_in);
	return sendto(m_socket, (char*)buf, buflen, flags, (struct sockaddr*)&to, tolen);
}

inline int CSocketNet::ReceiveFrom(void * buf, int buflen, char * socketAddress, int& socketPort, int flags)
{
	struct sockaddr_in from;
	int fromlen = sizeof(struct sockaddr_in);
	int value = recvfrom(m_socket, (char*)buf, buflen, flags, (struct sockaddr*)&from, &fromlen);
	if (value > 0)
	{
		strcpy_s(socketAddress, ADDRESS_SIZE, inet_ntoa(from.sin_addr));
		socketPort = ntohs(from.sin_port);
		//cout << "ntohs(from.sin_port) = " << ntohs(from.sin_port) << endl;
		//cout << "htons(from.sin_port) = " << htons(from.sin_port) << endl;
		///ntohs() 与 htons() 结果一致！
	}
	return value;
}

inline int CSocketNet::GetSockName(char * socketAddress, int & socketPort)
{
	struct sockaddr_in name;
	int namelen = sizeof(struct sockaddr_in);
	if (SOCKET_ERROR == getsockname(m_socket, (struct sockaddr*)&name, &namelen))
		return 0;

	strcpy_s(socketAddress, ADDRESS_SIZE, inet_ntoa(name.sin_addr));
	socketPort = ntohs(name.sin_port);
	return 1;
}

inline int CSocketNet::GetPeerName(char * peerAddress, int & peerPort)
{
	struct sockaddr_in name;
	int namelen = sizeof(struct sockaddr_in);
	if (SOCKET_ERROR == getpeername(m_socket, (struct sockaddr*)&name, &namelen))
		return 0;

	strcpy_s(peerAddress, ADDRESS_SIZE, inet_ntoa(name.sin_addr));
	peerPort = ntohs(name.sin_port);
	return 1;
}

/***
int WSAStartup(					//返回：0-成功；WSASYSNOTREADY | WSAVERNOTSUPPORTED WSAEINVAL - 错误
	_In_ WORD wVersionRequested,
	_Out_ LPWSADATA lpWSAData
);

SOCKET socket(					//返回：SOCKET-成功；INVALID_SOCKET-失败，可使用WSAGetLastError()获得错误代码
	_In_ int af,
	_In_ int type,
	_In_ int protocol
);

int bind(						//返回：0-无错误；SOCKET_ERROR == -1-错误，可使用WSAGetLastError()获得错误代码
	_In_ SOCKET s,
	_In_reads_bytes_(namelen) const struct sockaddr FAR * name,
	_In_ int namelen
);

int listen(						//返回：0-无错误；SOCKET_ERROR == -1-错误，可使用WSAGetLastError()获得错误代码
	_In_ SOCKET s,
	_In_ int backlog
);

SOCKET accept(					//返回：SOCKET-成功；INVALID_SOCKET-失败，可使用WSAGetLastError()获得错误代码
	_In_ SOCKET s,
	_Out_writes_bytes_opt_(*addrlen) struct sockaddr FAR * addr,
	_Inout_opt_ int FAR * addrlen
);

int connect(					//返回：0-无错误；SOCKET_ERROR-错误，可使用WSAGetLastError()获得错误代码
	_In_ SOCKET s,
	_In_reads_bytes_(namelen) const struct sockaddr FAR * name,
	_In_ int namelen
);

int send(						//返回：len-无错误；SOCKET_ERROR-错误，可使用WSAGetLastError()获得错误代码
	_In_ SOCKET s,
	_In_reads_bytes_(len) const char FAR * buf,
	_In_ int len,
	_In_ int flags
);

int recv(						//返回：len-无错误；SOCKET_ERROR-错误；0-在等待协议接收数据时网络中断
	_In_ SOCKET s,
	_Out_writes_bytes_to_(len, return) __out_data_source(NETWORK) char FAR * buf,
	_In_ int len,
	_In_ int flags
);

int sendto(						//返回：len-成功；SOCKET_ERROR-失败
	_In_ SOCKET s,
	_In_reads_bytes_(len) const char FAR * buf,
	_In_ int len,
	_In_ int flags,
	_In_reads_bytes_(tolen) const struct sockaddr FAR * to,
	_In_ int tolen
);

int recvfrom(				//返回：len-成功；SOCKET_ERROR-失败
	_In_ SOCKET s,
	_Out_writes_bytes_to_(len, return) __out_data_source(NETWORK) char FAR * buf,
	_In_ int len,
	_In_ int flags,
	_Out_writes_bytes_to_opt_(*fromlen, *fromlen) struct sockaddr FAR * from,
	_Inout_opt_ int FAR * fromlen
);

int getsockname(		//返回：0-无错误；SOCKET_ERROR-错误，可使用WSAGetLastError()获得错误代码
	_In_ SOCKET s,
	_Out_writes_bytes_to_(*namelen,*namelen) struct sockaddr FAR * name,
	_Inout_ int FAR * namelen
);

int getpeername(		//返回：0-无错误；SOCKET_ERROR-错误，可使用WSAGetLastError()获得错误代码
	_In_ SOCKET s,
	_Out_writes_bytes_to_(*namelen,*namelen) struct sockaddr FAR * name,
	_Inout_ int FAR * namelen
);
*/