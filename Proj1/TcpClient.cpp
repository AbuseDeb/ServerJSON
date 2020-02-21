#include "pch.h"
#include "tcpclient.h"


void ClientHandler(TcpClient *obj)
{
	if (obj == nullptr)
		return;


	char cMsg[1024] = { 0 };

	int nBytes_recv = 0;

	while (true)
	{
		nBytes_recv = recv(obj->m_hClientSocket, &cMsg[0], sizeof(cMsg), 0);
		if (nBytes_recv == SOCKET_ERROR)
			break;

		std::string cBuff = cMsg;
		obj->OnReceive(cBuff);
		std::cout << "ID - " << obj->m_hClientSocket << " " << cMsg << std::endl;

	}
	std::cout << "Client disconected. ID - " << obj->m_hClientSocket << std::endl;

	obj->m_hClientSocket = INVALID_SOCKET;
}

TcpClient::TcpClient(SOCKET newConnection)
{
	m_hClientSocket = newConnection;
		
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, this, NULL, NULL);//TcpClient(newConnection)

}


TcpClient::~TcpClient()
{
	Close();
}

bool TcpClient::IsActive() const
{
	if (m_hClientSocket != INVALID_SOCKET)
		return true;
	else
		return false;
}

void TcpClient::Close()
{
	closesocket(m_hClientSocket);
	int nMs = 1000;
	while (IsActive() && nMs > 0)
	{
		nMs -= 10;
		Sleep(10);
	}
}

void TcpClient::Send(const std::string &data)
{
	char cMessage[1024];

	strcpy_s(cMessage, data.c_str());

	send(m_hClientSocket, cMessage, sizeof(cMessage), NULL);
}
