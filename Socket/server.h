#pragma once
#include"includes.h"

class Server
{
private:
	int socket;	//����socket�������ص��ļ�������
	sockaddr_in addr;
	short port = 6666;
	static unsigned int threadCnt;
	static void ServiceClient(const ::sockaddr_in& clientAddr, const int& client, const int curThreadCnt);

	//��Ⱦ��
	static vector_t positions[2];

public:
	//static char buffer[200];	//�洢 ���ͺͽ��յ���Ϣ 
	int Init();
	int Boot();
	short GetPort();
};