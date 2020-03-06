#include "pch.h"
#include "tpcserver.h"

#include <iostream>
#include <Ws2tcpip.h>
#include <WinNT.h>



#pragma comment (lib, "Ws2_32.lib")


TpcServer::TpcServer()
{
	m_bExit = false;
}

TpcServer::~TpcServer()
{

	m_bExit = true;
	m_Mutex.lock();
	for (int i = 0; i < m_Clients.size(); i++)
	{
		m_Clients[i]->Send("Server close");
		delete m_Clients[i];
	}	
	
	m_Clients.clear();

	m_Mutex.unlock();


}

void TpcServer::CreateUserSocket(SOCKET newConnection)
{
	JsonClient *pClient = new JsonClient(newConnection);

	m_Mutex.lock();
	
	for (int i = 0; i < m_Clients.size(); i++)
	{
		if(!m_Clients[i]->IsActive())
		{
			delete m_Clients[i];
			m_Clients.erase(m_Clients.begin() + i);
			if (i == 0)
				break;
			i--;
			std::cout << "Deleted clietn" << m_Clients[i]->m_hClientSocket;
		}
	}

	m_Clients.push_back((TcpClient *)pClient);
	
	std::cout << "Socket conected client" << newConnection;

	m_Mutex.unlock();

}

void Listener(LPVOID Listener_socket)
{
	sParam *psParam = (sParam*)(Listener_socket);
	if (psParam == nullptr)
		return;

	while (true)
	{
		SOCKET pNewConnection;
		//newConnection = accept(ListenerSocket, (SOCKADDR*)&hAddr, &nSizeofaddr);
		pNewConnection = accept(psParam->hSocket, NULL, NULL);

		if (pNewConnection == 0)
		{
			std::cout << "Error\n";
		}
		else
		{
			std::cout << "Client connected. Id - " << pNewConnection << std::endl;
			psParam->pTpcServer->CreateUserSocket(pNewConnection);
		}
	}

	delete psParam;
}


bool TpcServer::Start(std::string ip, int port)
{

	m_cIp = ip;
	m_nPort = port;	

	WSADATA pWsaData;
	int nResult;

	nResult = WSAStartup(MAKEWORD(2,2), &pWsaData);
	if (nResult != 0)
	{
		std::cout << "WSAStartup failed with error: %d\n" << nResult;
	}
	
	SOCKADDR_IN pAddr;
	int nSizeOfAddr = sizeof(pAddr);
	pAddr.sin_port = htons(m_nPort);//конверт порта
	pAddr.sin_family = AF_INET;//ipv4
	inet_pton(AF_INET, m_cIp.c_str(), &(pAddr.sin_addr));//конверт ip


	SOCKET pListenerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//sock_stream для tcp

	int nPortStatus = ::bind(pListenerSocket, (SOCKADDR*)&pAddr, nSizeOfAddr);//The bind function associates a local address with a socket.
	if (nPortStatus != SOCKET_ERROR)
	{
		std::cout << "Port " << m_nPort << " is open " << std::endl;
		
		::listen(pListenerSocket, 10);

		sParam *psParam = new sParam();
		psParam->pTpcServer = this;
		psParam->hSocket = pListenerSocket;


		HANDLE hHandle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Listener, psParam, NULL, NULL);

		std::cout << "Server started at " << m_cIp << "\n";

		return hHandle > 0;
	}
	else
	{
		std::cout << "Port " << m_nPort << " is close, restart" << std::endl;
		return false;
	}

	
}

void TpcServer::Stop()
{

}