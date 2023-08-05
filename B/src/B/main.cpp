#include "bpch.h"
#include "Interpreter.h"

int main(int argc, char* argv[])
{
	
	std::vector<std::string> consoleArgs{};

	for (int i = 0; i < argc; i++)
	{
		char* arg = argv[i];
		consoleArgs.push_back(arg);
	}

	char* buff = new char[256];

	while (true)
	{
		std::string text;

		std::cout << "B-Lang> ";
		std::getline(std::cin, text);
		B::Interpreter::Interpret(text);
	}

	return 0;
}