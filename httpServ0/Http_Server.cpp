// Äëÿ êîððåêòíîé ðàáîòû freeaddrinfo â MinGW
// Ïîäðîáíåå: http://stackoverflow.com/a/20306451
#define _WIN32_WINNT 0x501
//incoming commit 01
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Http_Server.h"
//#include <opencv2\core\core.hpp>

// Íåîáõîäèìî, ÷òîáû ëèíêîâêà ïðîèñõîäèëà ñ DLL-áèáëèîòåêîé
// Äëÿ ðàáîòû ñ ñîêåòàì
#pragma comment(lib, "Ws2_32.lib")
#include <string>
#include <sstream>

#include "FIleRead.h"

HttpServer::HttpServer(std::string StrIP, std::string StrPort)
{
	WSAData wsaData;
	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0)
	{
		printf("WSAStartup failed, err = %d\n", err);
		WSACleanup();
		return;
	}
	//ws();
	//WSAStartup(MAKEWORD(2, 2), &ws());
	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;		 // AF_INET îïðåäåëÿåò, ÷òî áóäåò èñïîëüçîâàòüñÿ ñåòü äëÿ ðàáîòû ñ ñîêåòîì
	hints.ai_socktype = SOCK_STREAM; // Çàäàåì ïîòîêîâûé òèï ñîêåòà
	hints.ai_protocol = IPPROTO_TCP; // Èñïîëüçóåì ïðîòîêîë TCP
	hints.ai_flags = AI_PASSIVE;	 // Ñîêåò áóäåò áèíäèòüñÿ íà àäðåñ, ÷òîáû ïðèíèìàòü âõîäÿùèå ñîåäèíåíèÿ

	err = getaddrinfo(StrIP.c_str(), StrPort.c_str(), &hints, &addr);
	if (err != 0)
	{
		printf("getaddrinfo failed, err = %d\n", err);
		WSACleanup();
		return;
	}
	CreateSock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if (CreateSock == -1)
	{
		WSALERR = WSAGetLastError();
		printf("createsocket error = %d\n", WSALERR);
		freeaddrinfo(addr);
		WSACleanup();
		return;
	}
	err = bind(CreateSock, addr->ai_addr, (int)addr->ai_addrlen);
	if (err == -1)
	{
		WSALERR = WSAGetLastError();
		printf("bind error = %d\n", WSALERR);
		freeaddrinfo(addr);
		WSACleanup();
		return;
	}
	err = listen(CreateSock, SOMAXCONN);
	if (err == -1)
	{
		WSALERR = WSAGetLastError();
		printf("listen error = %d\n", WSALERR);
		closesocket(CreateSock);
		WSACleanup();
		return;
	}

	client_socket = INVALID_SOCKET;
}

void HttpServer::TakeMsg()
{
	client_socket = accept(CreateSock, NULL, NULL);
	if (client_socket == -1)
	{
		WSALERR = WSAGetLastError();
		printf("error = %d\n", WSALERR);
	}
	result = recv(client_socket, buf, max_client_buffer_size, 0); //sizeof(buf), 0);
	if (result == SOCKET_ERROR)
	{
		WSALERR = WSAGetLastError();
		printf("recv failed with code = %d\n", WSALERR);
	}
	else if (result == 0)
	{
		printf("Connection closed\n");
	}
	else if (result > 0)
	{
		//char *file = "Page0.htm";
		char *file = "HTMLPage1.htm"; 
		response_body = readHTML(file);
		
		response << "HTTP/1.1 200 OK\r\n"
			<< "Version: HTTP/1.1\r\n"
			<< "Content-Type: text/html; charset=utf-8\r\n"
			<< "\r\n\r\n"
			<< response_body.str();

		int n = 0;
		n = response_body.str().length();
		result = send(client_socket, response.str().c_str(), response.str().length(), 0);
		if (result == SOCKET_ERROR)
		{
			WSALERR = WSAGetLastError();
			printf("send error: %d\n", WSALERR);
		}
		closesocket(client_socket);
		response_body.str("");
		response.str("");
	}
}

void HttpServer::Send() {
	
}

HttpServer::~HttpServer()
{
	closesocket(CreateSock);
	freeaddrinfo(addr);
	WSACleanup();
}
