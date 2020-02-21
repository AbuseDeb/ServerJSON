#include "pch.h"
#include "jsonclient.h"
#include"cmdcommand.h"


JsonClient::JsonClient(SOCKET newConnection) : 
	TcpClient(newConnection)
{
	pJson.OpenJson("server.json");
}


JsonClient::~JsonClient()
{
	
}

void JsonClient::OnReceive(const std::string &data)
{
	//обращение к классу для команды из консоли
	CmdCommand pCommand;
	std::string cCommandSring = data;
	
	if (pCommand.GetCommand(cCommandSring) != true)
	{
		//exeption
	}

	std::string cAnswer = pJson.Answer(pCommand.m_Command, pCommand.m_cValue);
	Send(cAnswer);

}
