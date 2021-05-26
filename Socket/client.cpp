#include"client.h"

int Client::Init()
{
	//��������ʼ�� 
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		printf("require version fail!");
		return -1;
	}

	//socket������ʧ�ܷ���-1
	//int socket(int domain, int type, int protocol);
	//��һ��������ʾʹ�õĵ�ַ���ͣ�һ�㶼��ipv4��AF_INET
	//�ڶ���������ʾ�׽������ͣ�tcp���������ӵ��ȶ����ݴ���SOCK_STREAM
	//��������������Ϊ0
	//����socket
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
	//ָ���������˵�ip�����ز��ԣ�127.0.0.1
	//inet_addr()�����������ʮ����IPת���������ֽ���IP
	serverAddr.sin_addr.s_addr = inet_addr(IP);

	if (connect(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("connect");
		return 1;
	}

	printf("�����ӵ������.(IP=%s , Port=%d)\n", inet_ntoa(serverAddr.sin_addr), htons(serverAddr.sin_port));

	return 0;
}

int Client::Boot(vector_t* positions, const Window& window)
{
	int iDataNum;
	std::mutex mu;
	while (1)
	{
		//printf("������Ϣ(�� IP=%s , Port=%d) :\n", inet_ntoa(serverAddr.sin_addr), htons(serverAddr.sin_port));
		//scanf("%s", sendbuf);
		//printf("\n");

		//�����˷�����Ϣ
		//mu.lock();
		send(serverSocket, (char*)window.screen_keys, sizeof(window.screen_keys), 0); 
		//mu.unlock();


		//���շ���˷�������Ϣ
		//mu.lock();
		iDataNum = recv(serverSocket, (char*)positions, sizeof(positions), 0); 
		//mu.unlock();
		//printf("position[0]:%f,%f,%f\n", positions[0].x, positions[0].y, positions[0].z);
		//printf("position[1]:%f,%f,%f\n", positions[1].x, positions[1].y, positions[1].z);
	}

	closesocket(serverSocket);
	return 0;
}
