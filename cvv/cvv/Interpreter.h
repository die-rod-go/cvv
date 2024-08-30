#pragma once
#include "Lexer.h"
#include "Tape.h"

class Interpreter
{
public:
	static bool runLine(Tape tape, std::vector<Token> line);
};

