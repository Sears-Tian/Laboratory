#include "CSocketNet.h"


CSocketNet::CSocketNet()
{
	m_socket = INVALID_SOCKET;
	//加载套接字库
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
}

CSocketNet::~CSocketNet()
{
	Close();
}

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
	if (socketAddress)
		name.sin_addr.s_addr = inet_addr(socketAddress);
	return !bind(m_socket, (struct sockaddr*)&name, sizeof(struct sockaddr_in));
}

int CSocketNet::Accept(CSocketNet & socketConn, char* addrConn, int* portConn)
{	// accept
	struct sockaddr_in addr;
	int addrlen = sizeof(struct sockaddr_in);
	socketConn.m_socket = accept(m_socket, (struct sockaddr*)&addr, &addrlen);
	if (INVALID_SOCKET == socketConn.m_socket)
		return 0;

	if (addrConn)
		strcpy_s(addrConn, ADDRESS_SIZE, inet_ntoa(addr.sin_addr));
	if (portConn)
		*portConn = addr.sin_port;
	return 1;
}

int CSocketNet::Connect(const char * hostAddress, int hostPort)
{
	//struct sockaddr_in name;
	//name.sin_family = AF_INET;
	//name.sin_port = htons(hostPort);
	struct sockaddr_in name = { AF_INET, htons(hostPort) };
	name.sin_addr.s_addr = inet_addr(hostAddress);
	int namelen = sizeof(struct sockaddr_in);
	return !connect(m_socket, (struct sockaddr*)&name, namelen);
}

int CSocketNet::Listen(int backlog)
{
	return !listen(m_socket, backlog);
}

int CSocketNet::Send(const void * buf, int buflen, int flags)
{
	int result = send(m_socket, (char*)buf, buflen, flags);
	if (result < 0)
		std::cout << "Send failed! Error Code: " << WSAGetLastError() << std::endl;
	return result;
}

int CSocketNet::Receive(void * buf, int buflen, int flags)
{
	int result = recv(m_socket, (char*)buf, buflen, flags);
	if (result < 0)
		std::cout << "Recv failed! Error Code: " << GetLastError() << std::endl;
	else if (result == 0)
		std::cout << "connection interrupt! Error Code: " << GetLastError() << std::endl;
	return result;
}

int CSocketNet::SendTo(const void * buf, int buflen, const char * hostAddress, int hostPort, int flags)
{
	struct sockaddr_in to = { AF_INET, htons(hostPort) };
	to.sin_addr.s_addr = inet_addr(hostAddress);
	int tolen = sizeof(struct sockaddr_in);
	return sendto(m_socket, (char*)buf, buflen, flags, (struct sockaddr*)&to, tolen);
}

int CSocketNet::ReceiveFrom(void * buf, int buflen, char * socketAddress, int& socketPort, int flags)
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

int CSocketNet::GetSockName(char * socketAddress, int & socketPort)
{
	struct sockaddr_in name;
	int namelen = sizeof(struct sockaddr_in);
	if (SOCKET_ERROR == getsockname(m_socket, (struct sockaddr*)&name, &namelen))
		return 0;

	strcpy_s(socketAddress, ADDRESS_SIZE, inet_ntoa(name.sin_addr));
	socketPort = ntohs(name.sin_port);
	return 1;
}

int CSocketNet::GetPeerName(char * peerAddress, int & peerPort)
{
	struct sockaddr_in name;
	int namelen = sizeof(struct sockaddr_in);
	if (SOCKET_ERROR == getpeername(m_socket, (struct sockaddr*)&name, &namelen))
		return 0;

	strcpy_s(peerAddress, ADDRESS_SIZE, inet_ntoa(name.sin_addr));
	peerPort = ntohs(name.sin_port);
	return 1;
}

void CSocketNet::Close()
{
	closesocket(m_socket);		/// int closesocket(_In_ SOCKET s);
	WSACleanup();
	m_socket = INVALID_SOCKET;
}

SOCKET CSocketNet::getSocket(void) const
{
	return this->m_socket;
}

bool CSocketNet::operator==(const CSocketNet & rsocket) const
{
	return this->m_socket == rsocket.m_socket;
}

//bool CSocketNet::operator<(const CSocketNet & rsocket) const
//{
//	if (this->m_socket < rsocket.m_socket)
//		return true;
//	else
//		return false;
//}
