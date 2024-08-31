#pragma once
#include "Scanner.h"
#include "Tape.h"
#include "CVV.h"

enum class CommandType {
	ERROR,
	ADD,
	SUB,
	MULT,
	DIV,
	AND,
	OR,
	CREATE,
	VAPORIZE
};

enum class InterpreterState {
	NEW_COMMAND,
	AWAITING_INDEX,
	AWAITING_COMMAND_VALUE,
	AWAITING_DESCRIPTOR_OR_END,
	AWAITING_OPERATOR,
	AWAITING_DESCRIPTOR_VALUE,
	AWAITING_END,
};

struct Command {
	Command() {
		type = CommandType::ERROR;
		index = -999;
		oper = ' ';
		num = 0b00000000;
		compareTo = 0b00000000;
	}

	void reset() {
		type = CommandType::ERROR;
		index = -999;
		oper = ' ';
		num = 0b00000000;
		compareTo = 0b00000000;
	}
	CommandType type;
	int index;
	byte num;
	char oper;
	byte compareTo;
};

class Interpreter
{
public:
	Interpreter(std::vector<Token> tokens, Tape tape);
	void printCommands();
	void runTokens();
	void print();
private:
	void constructCommandList();
	void runCommandList();
	Tape tape;
	InterpreterState currentState;
	std::vector<Token> tokens;
	std::vector<Command> commands;
	Command newCommand(Command commandInProgress, Token token);
	Command readIndex(Command commandInProgress, Token token);
	Command readCommandValue(Command commandInProgress, Token token);
	Command readOperator(Command commandInProgress, Token token);
	Command readDescriptorValue(Command commandInProgress, Token token);
};

