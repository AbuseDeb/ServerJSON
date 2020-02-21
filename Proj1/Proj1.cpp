// Proj1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "tpcserver.h"
#include "jsonparser.h"
#include "cmdcommand.h"


int main()
{
	/*JsonParser pJson;

	pJson.OpenJson("server.json");

	std::string b = "Dima";

	std::string a = pJson.Answer(CmdCommand::CmdCommandGetName, b);

	std::cout << a;

	return 0;*/

	TpcServer pServer;
	pServer.Start("127.0.0.1", 1111);

	char z = '\0';

	while (z != ' ') {
		std::cout << "Enter SPACE " << std::endl;
		z = getchar();
	}
	   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
