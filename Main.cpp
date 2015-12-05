#include<Windows.h>
#include<iostream>
#include<sstream>


#include"ThreadActor.h"



int main(int argn,char* argv[])
{

	std::wcout << "Win32 MultiThread Programming Sample" << std::endl;

	ThreadActor actor;

	actor.Start();

	int count = 0;
	while (true)
	{
		::Sleep(250);

		std::wostringstream oss;

		oss << "Count ="
			<< std::to_wstring(count)
			;

		std::wcout << "+++" << std::endl;
		actor.Print(oss.str());
		std::wcout << "---" << std::endl;
		if ( count == 10)
		{
			break;
		}
		count++;
	}

	actor.Stop();

	return 0;
}