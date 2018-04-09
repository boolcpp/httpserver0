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
	//char _key[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//	FILE *fp;
////	std::cout <<  fopen_s(&fp, "C:\\сProjects\\httpServ0\\httpServ0\\imageTest.jpg", "rb");
//	std::cout << fopen_s(&fp, "E:\\imageTest.jpg", "rb");
//	if (fp == NULL)
//	{
//		std::cout << "file is not open.\n";
//		
//	}
//	unsigned char *picbuffer = new unsigned char[10000000];
//	//memset(picbuffer, 0, 10000000);
//	int flen = fread(picbuffer, 1, 10000000, fp);
//	std::string str = base64_encode(picbuffer, flen);
//	//sprintf_s(picbuffer, 10000000, "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.");
//	//int flen = strlen(picbuffer);
//	fclose(fp);
	//char *outBuffer = (char*)malloc(10000000);
	//memset(outBuffer, 0, 10000000);
	//int j=0;
	//long bb;
	//long b2;
	//for (int i = 0; i < flen; i += 3) {
	//	bb = (picbuffer[i]<<16) + (picbuffer[i+1]<<8) + picbuffer[i+2];
	//	//std::cout << bb << std::endl;
	//	for (int k = 0; k < 4; k++) {
	//		b2 = (bb & 0xFC0000) >> 18;
	//		outBuffer[j+k] = _key[b2];
	//		bb <<= 6;
	//	}
	//	j += 4;
	//}
	//long flen1 = flen / 3 * 3;
	//switch (flen - flen1) {
	//case 1:
	//	outBuffer[j - 1] = '=';
	//	break;
	//case 2:
	//	outBuffer[j - 1] = '=';
	//	break;
	//case 3:
	//	outBuffer[j - 1] = '=';
	//	outBuffer[j - 2] = '=';
	//	break;
	//}
	//
	//std::cout << outBuffer;

 //   WSADATA wsaData; // служебная структура для хранение информации о реализации Windows Sockets
 //   int result = WSAStartup(MAKEWORD(2, 2), &wsaData);// старт использования библиотеки сокетов процессом (подгружается Ws2_32.dll)

 //   // Если произошла ошибка подгрузки библиотеки
 //   if (result != 0) {
 //       cerr << "WSAStartup failed: " << result << "\n";
 //       return result;
 //   }

 //   struct addrinfo* addr = NULL; // структура, хранящая информацию об IP-адресе  слущающего сокета

 //   // Шаблон для инициализации структуры адреса
 //   struct addrinfo hints;
 //   ZeroMemory(&hints, sizeof(hints));

 //   hints.ai_family = AF_INET;		 // AF_INET определяет, что будет использоваться сеть для работы с сокетом
 //   hints.ai_socktype = SOCK_STREAM; // Задаем потоковый тип сокета
 //   hints.ai_protocol = IPPROTO_TCP; // Используем протокол TCP
 //   hints.ai_flags = AI_PASSIVE;	 // Сокет будет биндиться на адрес, чтобы принимать входящие соединения

 //   // Инициализируем структуру, хранящую адрес сокета - addr. Наш HTTP-сервер будет висеть на 8000-м порту локалхоста
 //   result = getaddrinfo("192.168.0.122", "8000", &hints, &addr);

 //   // Если инициализация структуры адреса завершилась с ошибкой, выведем сообщением об этом и завершим выполнение программы
 //   if (result != 0) {
 //       cerr << "getaddrinfo failed: " << result << "\n";
 //       WSACleanup(); // выгрузка библиотеки Ws2_32.dll
 //       return 1;
 //   }

 //   // Создание сокета
 //   int listen_socket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
 //   // Если создание сокета завершилось с ошибкой, выводим сообщение, освобождаем память, выделенную под структуру addr, выгружаем dll-библиотеку и закрываем программу
 //   if (listen_socket == INVALID_SOCKET) {
 //       cerr << "Error at socket: " << WSAGetLastError() << "\n";
 //       freeaddrinfo(addr);
 //       WSACleanup();
 //       return 1;
 //   }

 //   // Привязываем сокет к IP-адресу
 //   result = bind(listen_socket, addr->ai_addr, (int)addr->ai_addrlen);

 //   // Если привязать адрес к сокету не удалось, то выводим сообщение об ошибке, освобождаем память, выделенную под структуру addr и закрываем открытый сокет. Выгружаем DLL-библиотеку из памяти и закрываем программу.
 //   if (result == SOCKET_ERROR) {
 //       cerr << "bind failed with error: " << WSAGetLastError() << "\n";
 //       freeaddrinfo(addr);
 //       closesocket(listen_socket);
 //       WSACleanup();
 //       return 1;
 //   }

 //   // Инициализируем слушающий сокет
 //   if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
 //       cerr << "listen failed with error: " << WSAGetLastError() << "\n";
 //       closesocket(listen_socket);
 //       WSACleanup();
 //       return 1;
 //   }

 //   const int max_client_buffer_size = 1024;
	//
 //   char buf[max_client_buffer_size];
	//ZeroMemory(&buf, max_client_buffer_size);
	//int client_socket = INVALID_SOCKET;

 //   for (;;) {
 //       // Принимаем входящие соединения
 //       client_socket = accept(listen_socket, NULL, NULL);
 //       if (client_socket == INVALID_SOCKET) {
 //           cerr << "accept failed: " << WSAGetLastError() << "\n";
 //           closesocket(listen_socket);
 //           WSACleanup();
 //           return 1;
 //       }

 //       result = recv(client_socket, buf, max_client_buffer_size, 0);

 //       std::stringstream response;	     // сюда будет записываться ответ клиенту
 //       std::stringstream response_body; // тело ответа
	//	std::stringstream image;
	//	std::stringstream imagebody;

 //       if (result == SOCKET_ERROR) {
 //           // ошибка получения данных
 //           cerr << "recv failed: " << result << "\n";
 //           closesocket(client_socket);
 //       } else if (result == 0) {
 //           // соединение закрыто клиентом
 //           cerr << "connection closed...\n";
 //       } else if (result > 0) {
 //           // Мы знаем фактический размер полученных данных, поэтому ставим метку конца строки в буфере запроса.
	//		std::cout << '\n' << result << std::endl;
 //           buf[result] = '\0';
	//		
 //           // Данные успешно получены формируем тело ответа (HTML)
 //           response_body << "<title>Test C++ HTTP Server</title>\n"
 //               << "<h1>Test page</h1>\n"
 //               << "<p>This is body of the test page...</p>\n"
 //               << "<h2>Request headers</h2>\n"
 //               << "<pre>" << buf << "</pre>\n"
	//			//<<"<h3>" << "Content-Length: " << response_body.str().length() <<"</h3>\n"
	//			<< "<form method='post'><input type='submit' value='testbutton'>"
	//			<< "<textarea name='qwerty'></textarea></form>"
	//			//<< "<img src=\"data:image/jpeg;base64," << outBuffer <<"\" alt=\"внедренная иконка папки\"/>"
	//			<< "<img src=data:image/gif;base64," << str << ">"
 //               << "<em><small>Test C++ Http Server</small></em>\n";

 //           // Формируем весь ответ вместе с заголовками
 //           response << "HTTP/1.1 200 OK\r\n"
 //               << "Version: HTTP/1.1\r\n"
 //               << "Content-Type: text/html; charset=utf-8\r\n"
 //               //<< "Content-Length: " << response_body.str().length()
 //               << "\r\n\r\n"
 //               << response_body.str()
	//			<< "Content-Length: " << response_body.str().length();
	//		
	//		result = send(client_socket, response.str().c_str(), response.str().length(), 0); //отправка данных клиенту
 //           if (result == SOCKET_ERROR) {
 //               // произошла ошибка при отправле данных
 //               cerr << "send failed: " << WSAGetLastError() << "\n";
 //           }
 //           // Закрываем соединение к клиентом
 //           closesocket(client_socket);
 //       }
 //   }

 //   // Убираем за собой
 //   closesocket(listen_socket);
 //   freeaddrinfo(addr);
 //   WSACleanup();

//HttpServer Serv("192.168.0.122", "8000");
	
	HttpServer Server0("192.168.0.122", "8000");
	Server0.TakeMsg();
	//for (;;)
	//{
	//	Server0.TakeMsg();
	//	Server0.Send();
	//}

    return 0;
}
