//для работы с файлами картинок
#include <stdio.h>

#include "Http_Server.h"

int main()
{
	HttpServer Server0("192.168.0.77", "8000");
	for (;;)
	{
		Server0.TakeMsg();
	}

    return 0;
}
