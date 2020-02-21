#pragma once

#include "tcpclient.h"


class JsonClient : TcpClient
{
public:
	JsonClient(SOCKET newConnection);
	~JsonClient();

	void OnReceive(const std::string &data) override;
private:
	JsonParser pJson;
};

