#include"client.h"

int Client::Init()
{
	//下面代码初始化 
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
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror("socket");
		return 1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(this->serverPort);

	return 0;
}

int Client::ConnectToServer(const char* IP)
{
	//指定服务器端的ip，本地测试：127.0.0.1
	//inet_addr()函数，将点分十进制IP转换成网络字节序IP
	serverAddr.sin_addr.s_addr = inet_addr(IP);

	if (connect(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("connect");
		return 1;
	}

	printf("已连接到服务端.(IP=%s , Port=%d)\n", inet_ntoa(serverAddr.sin_addr), htons(serverAddr.sin_port));

	return 0;
}

int Client::Boot(vector_t* positions, const Window& window)
{
	int iDataNum;
	std::mutex mu;
	while (1)
	{
		//printf("发送消息(至 IP=%s , Port=%d) :\n", inet_ntoa(serverAddr.sin_addr), htons(serverAddr.sin_port));
		//scanf("%s", sendbuf);
		//printf("\n");

		//向服务端发送消息
		//mu.lock();
		send(serverSocket, (char*)window.screen_keys, sizeof(window.screen_keys), 0); 
		//mu.unlock();


		//接收服务端发来的消息
		//mu.lock();
		iDataNum = recv(serverSocket, (char*)positions, sizeof(positions), 0); 
		//mu.unlock();
		//printf("position[0]:%f,%f,%f\n", positions[0].x, positions[0].y, positions[0].z);
		//printf("position[1]:%f,%f,%f\n", positions[1].x, positions[1].y, positions[1].z);
	}

	closesocket(serverSocket);
	return 0;
}
