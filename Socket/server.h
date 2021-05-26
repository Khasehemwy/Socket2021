#pragma once
#include"includes.h"

class Server
{
private:
	int socket;	//调用socket函数返回的文件描述符
	sockaddr_in addr;
	short port = 6666;
	static unsigned int threadCnt;
	static void ServiceClient(const ::sockaddr_in& clientAddr, const int& client, const int curThreadCnt);

	//渲染用
	static vector_t positions[2];

public:
	//static char buffer[200];	//存储 发送和接收的信息 
	int Init();
	int Boot();
	short GetPort();
};