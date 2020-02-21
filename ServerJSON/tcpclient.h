#pragma once
#include <iostream>
#include <Ws2tcpip.h>
#include <string>
#include "jsonparser.h"

class TcpClient
{
public:
	TcpClient(SOCKET newConnection);
	virtual ~TcpClient();
	virtual void OnReceive(const std::string &data) = 0;
	void Send(const std::string &data);
	bool IsActive() const;
	void Close();

public:
	SOCKET m_hClientSocket;
};

