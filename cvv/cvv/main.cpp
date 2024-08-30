#include <iostream>
#include <vector>
#include "Type_Definitions.h"
#include "Tape.h"
#include "Lexer.h"
#include "Interpreter.h"

int main()
{
	auto lines = Lexer::tokenize("-@3?>3;-3?2");
	Tape tape;
	tape.addCell();
	tape.addCell();
	tape.addCell();
	Interpreter::runLine(tape, lines[0]);
}