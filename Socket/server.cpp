#include"server.h"

/*
监听后，一直处于accept阻塞状态，
直到有客户端连接，
当客户端如数quit后，断开与客户端的连接
*/

unsigned int Server::threadCnt = 0;
vector_t Server::positions[2] = { {0,0,0,1},{0,0,0,1} };

void Server::ServiceClient(const ::sockaddr_in& clientAddr,const int& client,const int curThreadCnt)
{
	int iDataNum;

	//inet_ntoa ip地址转换函数，将网络字节序IP转换为点分十进制IP
	//表达式：char *inet_ntoa (struct in_addr);
	printf("IP is %s\n", inet_ntoa(clientAddr.sin_addr)); //把来访问的客户端的IP地址打出来
	printf("Port is %d\n", htons(clientAddr.sin_port));
	printf("正在传输信息 (来自:IP=%s , Port=%d) ...\n", inet_ntoa(clientAddr.sin_addr), htons(clientAddr.sin_port));

	int keyBuffer[512];
	while (1)
	{
		//printf("0\n");
		iDataNum = recv(client, (char*)keyBuffer, sizeof(keyBuffer), 0);
		if (iDataNum < 0)
		{
			//perror("recv null");
			continue;
		}

		if (keyBuffer[VK_UP]) { positions[curThreadCnt].z += 0.4f; /*printf("up\n");*/ }
		if (keyBuffer[VK_DOWN]) { positions[curThreadCnt].z -= 0.4f; /*printf("down\n");*/ }
		if (keyBuffer[VK_RIGHT]) { positions[curThreadCnt].x += 0.4f; /*printf("right\n");*/ }
		if (keyBuffer[VK_LEFT]) { positions[curThreadCnt].x -= 0.4f; /*printf("left\n");*/ }

		//服务端返回两个角色的位置信息
		send(client, (char*)positions, sizeof(positions), 0);
	}
}

int Server::Init()
{
	//必须先初始化 
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		printf("require version fail!");
		return -1;
	}

	//socket函数，失败返回-1
	//int socket(int domain, int type, int protocol);
	//第一个参数表示使用的地址类型，一般都是ipv4，AF_INET
	//第二个参数表示套接字类型：tcp：面向连接的稳定数据传输SOCK_STREAM
	//第三个参数设置为0
	//建立socket
	if ((this->socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror("socket");
		return 1;
	}

	//初始化 server_addr
	memset(&this->addr, 0, sizeof(this->addr));

	//初始化服务器端的套接字，并用htons和htonl将端口和地址转成网络字节序
	this->addr.sin_family = AF_INET;
	this->addr.sin_port = htons(this->port);

	//ip可是是本服务器的ip，也可以用宏INADDR_ANY代替，代表0.0.0.0，表明所有地址
	this->addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//对于bind，accept之类的函数，里面套接字参数都是需要强制转换成(struct sockaddr *)
	//bind三个参数：服务器端的套接字的文件描述符，
	if (bind(this->socket, (struct sockaddr*)&this->addr, sizeof(this->addr)) < 0)
	{
		perror("connect");
		return 1;
	}

	//设置服务器上的socket为监听状态
	if (listen(this->socket, 5) < 0)
	{
		perror("listen");
		return 1;
	}

	return 0;
}

int Server::Boot()
{
	while (1)
	{
		printf("监听端口: %d\n", this->port);
		sockaddr_in clientAddr;
		int addrLength = sizeof(clientAddr);
		int client;

		//接收新的客户端
		client = accept(this->socket, (struct sockaddr*)&clientAddr, (socklen_t*)&addrLength);
		if (client < 0)
		{
			perror("accept");
			continue;
		}
		std::thread t(this->ServiceClient, clientAddr, client, threadCnt);
		t.detach();
		threadCnt++; threadCnt %= 2;
	}

	return 0;
}

short Server::GetPort()
{
	return this->port;
}
