#include <iostream>
#include <vector>
#include "Type_Definitions.h"
#include "Tape.h"
#include "Scanner.h"
#include "Interpreter.h"
#include <fstream>
#include <sstream>

void runFile(std::string path);

int main(int argc, char* argv[])
{
	if (argc == 1)
		std::cout << "Please specify a file path." << std::endl;
	else if (argc == 2)
	{
		runFile(argv[1]);
	}
}

void runFile(std::string path)
{
	std::ifstream myFile(path); //	open file
	if (!myFile.is_open())
		std::cout << "Error opening file" << std::endl;

	std::stringstream buffer;	//	convert to string stream
	buffer << myFile.rdbuf();	//	read string stream into string
	myFile.close();

	//	run the file
	Scanner scanner(buffer.str());
	auto tokens = scanner.scanSource();
	//for (auto token : tokens) {
	//	std::cout << token.token << " " << (int)token.type << std::endl;
	//}
	Tape tape;
	Interpreter interpret(tokens, tape);
	interpret.runTokens();
	//interpret.printCommands();
	interpret.print();

}