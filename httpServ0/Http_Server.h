// Для корректной работы freeaddrinfo в MinGW
// Подробнее: http://stackoverflow.com/a/20306451
#define _WIN32_WINNT 0x501

#include <WinSock2.h>
#include <WS2tcpip.h>
#include "base64.h"
//#include <opencv2\core\core.hpp>

// Необходимо, чтобы линковка происходила с DLL-библиотекой
// Для работы с сокетам
#pragma comment(lib, "Ws2_32.lib")
#include <string>
#include <sstream>

class HttpServer
{
public:
	HttpServer(std::string IP, std::string Port);
	~HttpServer();
	//void readErr(int);
	
	void Send();
	void TakeMsg();
private:
	//std::string writeErr(int);
	int err;
	int WSALERR;
	int result;
	/*WSADATA wsadata;
	WSADATA ws();*/
	struct addrinfo* addr = NULL;
	struct addrinfo hints;
	int CreateSock;
	int client_socket;

	int max_client_buffer_size = 1024;
	char buf[1024];

	std::stringstream response;	     // сюда будет записываться ответ клиенту
	std::stringstream response_body; // тело ответа
	std::stringstream image;
	std::stringstream imagebody;
	
};