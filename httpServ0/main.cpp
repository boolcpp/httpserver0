//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif
#include "Http_Server.h"
#include <iostream>
#include <sstream>
#include <string>
//для работы с файлами картинок
#include <stdio.h>

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

using std::cerr;

int main()
{

//HttpServer Serv("192.168.0.122", "8000");
	
	HttpServer Server0("192.168.0.77", "8000");
	for (;;)
	{
		Server0.TakeMsg();
	}
	

    return 0;
}
