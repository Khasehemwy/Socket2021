#pragma once
#include"includes.h"

class Client
{
private:
	sockaddr_in serverAddr;
	short serverPort = 6666;

public:
	int serverSocket;
	int Init();
	int ConnectToServer(const char* IP);
	int Boot(vector_t* positions,const Window& window);
};

