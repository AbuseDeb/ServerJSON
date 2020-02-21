#pragma once

#include <string>
#include <WinSock2.h>
#include <vector>
#include <mutex>
#include "tcpclient.h"
#include "jsonclient.h"

class TpcServer;

struct sParam
{
	TpcServer *pTpcServer;
	SOCKET hSocket;
};


class TpcServer
{
public:
	TpcServer();
	~TpcServer();

	//void DeleteHandle(SOCKET hSocket);
	bool Start(std::string ip, int port);
	void Stop();	
	void CreateUserSocket(SOCKET newConnection);
public:
	int m_nPort;
	volatile bool m_bExit;
	std::string m_cIp;
	std::vector<TcpClient*> m_Clients;

private:
	std::mutex m_Mutex;
};

