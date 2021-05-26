#include"server.h"

/*
������һֱ����accept����״̬��
ֱ���пͻ������ӣ�
���ͻ�������quit�󣬶Ͽ���ͻ��˵�����
*/

unsigned int Server::threadCnt = 0;
vector_t Server::positions[2] = { {0,0,0,1},{0,0,0,1} };

void Server::ServiceClient(const ::sockaddr_in& clientAddr,const int& client,const int curThreadCnt)
{
	int iDataNum;

	//inet_ntoa ip��ַת���������������ֽ���IPת��Ϊ���ʮ����IP
	//���ʽ��char *inet_ntoa (struct in_addr);
	printf("IP is %s\n", inet_ntoa(clientAddr.sin_addr)); //�������ʵĿͻ��˵�IP��ַ�����
	printf("Port is %d\n", htons(clientAddr.sin_port));
	printf("���ڴ�����Ϣ (����:IP=%s , Port=%d) ...\n", inet_ntoa(clientAddr.sin_addr), htons(clientAddr.sin_port));

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

		//����˷���������ɫ��λ����Ϣ
		send(client, (char*)positions, sizeof(positions), 0);
	}
}

int Server::Init()
{
	//�����ȳ�ʼ�� 
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
	if ((this->socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror("socket");
		return 1;
	}

	//��ʼ�� server_addr
	memset(&this->addr, 0, sizeof(this->addr));

	//��ʼ���������˵��׽��֣�����htons��htonl���˿ں͵�ַת�������ֽ���
	this->addr.sin_family = AF_INET;
	this->addr.sin_port = htons(this->port);

	//ip�����Ǳ���������ip��Ҳ�����ú�INADDR_ANY���棬����0.0.0.0���������е�ַ
	this->addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//����bind��accept֮��ĺ����������׽��ֲ���������Ҫǿ��ת����(struct sockaddr *)
	//bind�����������������˵��׽��ֵ��ļ���������
	if (bind(this->socket, (struct sockaddr*)&this->addr, sizeof(this->addr)) < 0)
	{
		perror("connect");
		return 1;
	}

	//���÷������ϵ�socketΪ����״̬
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
		printf("�����˿�: %d\n", this->port);
		sockaddr_in clientAddr;
		int addrLength = sizeof(clientAddr);
		int client;

		//�����µĿͻ���
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
