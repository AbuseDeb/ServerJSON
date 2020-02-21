#pragma once

#include "tpcserver.h"
#include "jsonparser.h"

class JsonServer : public TpcServer
{
public:
	JsonServer();
	~JsonServer();

	 void OnReceive(const std::string &data, const sParam &client_socket) override;

public:
	JsonParser json;
};

