
//#include "pch.h"
#include <iostream> 
#include <winsock2.h>  

#pragma comment(lib,"ws2_32.lib")  
using namespace std;

int main(int argc, char* argv[])
{
	//��ʼ��WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	//�����׽���  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		cout << "create socket error !" << endl;
		return 0;
	}

	//��IP�Ͷ˿�  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	//sin.sin_addr.s_addr = inet_addr("192.168.199.245");  //���õ�ַ 
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		cout << "bind error !" << endl;
	}

	//��ʼ����  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		cout << "listen error !" << endl;
		return 0;
	}

	//ѭ����������  
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	while (true)
	{
		cout << "�������������ȴ����ӡ�����" << endl;
		sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET)
		{
			cout << "accept error !" << endl;
			continue;
		}

		cout << "���ܵ�һ�����ӣ�" << inet_ntoa(remoteAddr.sin_addr) << endl;

		//��������  
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			printf(revData);
		}

		//��������  
		const char* sendData = "��ã�TCP�ͻ��ˣ�\n";
		send(sClient, sendData, strlen(sendData), 0);
		closesocket(sClient);
	}

	closesocket(slisten);
	WSACleanup();
	return 0;
}