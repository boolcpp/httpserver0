#include "FIleRead.h"

std::stringstream readHTML(char *fileName)
{
	std::ifstream file(fileName);
	char ch;
	std::stringstream ss;
	ss.str("");
	if (!file.is_open())
	{
		std::cout << "file not open " << fileName << std::endl;
		ss << "error";
		return ss;
	}
	else
	{
		while (!file.eof())
		{
			file.get(ch);
			ss << ch;
		}
		return ss;
	}
}