#include "Interpreter.h"
#include <iostream>

Interpreter::Interpreter(std::vector<Token> tokens, Tape tape) : tokens(tokens), tape(tape), currentState(InterpreterState::NEW_COMMAND)
{

}

void Interpreter::runTokens() {
	constructCommandList();
	runCommandList();
}

void Interpreter::print()
{
	for (auto cell : tape.getCells()) {
		std::cout << (int)cell << "|";
	}
}

void Interpreter::constructCommandList()
{
	Command tempCommand;
	for (auto token : tokens) {
		switch (currentState) {
		case InterpreterState::NEW_COMMAND :
			tempCommand = newCommand(tempCommand, token);
			break;
		case InterpreterState::AWAITING_INDEX:
			tempCommand = readIndex(tempCommand, token);
			break;
		case InterpreterState::AWAITING_COMMAND_VALUE:
			tempCommand = readCommandValue(tempCommand, token);
			break;
		case InterpreterState::AWAITING_DESCRIPTOR_OR_END:
			if (token.type == TokenType::QUESTION) {
				currentState = InterpreterState::AWAITING_OPERATOR;
			}
			else if (token.type == TokenType::SEMICOLON) {
				commands.push_back(tempCommand);
				tempCommand.reset();
				currentState = InterpreterState::NEW_COMMAND;
			}
			else {
				CVV::error("Invalid character at : '" + token.token + "'. Expected '?' or ';'.");
			}
			break;
		case InterpreterState::AWAITING_OPERATOR:
			tempCommand = readOperator(tempCommand, token);
			break;
		case InterpreterState::AWAITING_DESCRIPTOR_VALUE:
			tempCommand = readDescriptorValue(tempCommand, token);
			break;
		case InterpreterState::AWAITING_END:
			if (token.type == TokenType::SEMICOLON) {
				commands.push_back(tempCommand);
				tempCommand.reset();
				currentState = InterpreterState::NEW_COMMAND;
			}
			else {
				CVV::error("Invalid character at : '" + token.token + "'. Expected ';'");
			}
			break;
		default:
			commands.push_back(tempCommand);
			tempCommand.reset();
			break;
		}
	}
}

void Interpreter::runCommandList()
{
	for (auto command : commands) {
		switch (command.type) {
		case CommandType::ADD:
			if (command.oper == ' ')
				tape.add(command.num);
			else
				tape.add(command.num, command.oper, command.compareTo);
			break;
		case CommandType::SUB:
			if (command.oper == ' ')
				tape.subtract(command.num);
			else
				tape.subtract(command.num, command.oper, command.compareTo);
			break;
		case CommandType::MULT:
			if (command.oper == ' ')
				tape.multiply(command.num);
			else
				tape.multiply(command.num, command.oper, command.compareTo);
			break;
		case CommandType::DIV:
			if (command.oper == ' ')
				tape.divide(command.num);
			else
				tape.divide(command.num, command.oper, command.compareTo);
			break;
		case CommandType::AND:
			if (command.oper == ' ')
				tape.band(command.num);
			else
				tape.band(command.num, command.oper, command.compareTo);
			break;
		case CommandType::OR:
			if (command.oper == ' ')
				tape.bor(command.num);
			else
				tape.bor(command.num, command.oper, command.compareTo);
			break;
		case CommandType::CREATE:
			tape.addCells(command.index);
			break;
		case CommandType::VAPORIZE:
			tape.vaporize(command.index);
			break;
		}

	}
}

void Interpreter::printCommands()
{
	for (auto command : commands) {
		std::cout << "Type: " << (int)command.type << " Num: " << (int)command.num << " Oper: " << command.oper << " Comp: " << (int)command.compareTo << " Index: " << command.index << std::endl;
	}
}

Command Interpreter::newCommand(Command commandInProgress, Token token)
{

	switch (token.type) {
	case TokenType::PLUS:
		commandInProgress.type = CommandType::ADD;
		currentState = InterpreterState::AWAITING_COMMAND_VALUE;
		break;
	case TokenType::DASH:
		commandInProgress.type = CommandType::SUB;
		currentState = InterpreterState::AWAITING_COMMAND_VALUE;
		break;
	case TokenType::STAR:
		commandInProgress.type = CommandType::MULT;
		currentState = InterpreterState::AWAITING_COMMAND_VALUE;
		break;
	case TokenType::SLASH:
		commandInProgress.type = CommandType::DIV;
		currentState = InterpreterState::AWAITING_COMMAND_VALUE;
		break;
	case TokenType::AND:
		commandInProgress.type = CommandType::AND;
		currentState = InterpreterState::AWAITING_COMMAND_VALUE;
		break;
	case TokenType::PIPE:
		commandInProgress.type = CommandType::OR;
		currentState = InterpreterState::AWAITING_COMMAND_VALUE;
		break;
	case TokenType::CREATE:
		commandInProgress.type = CommandType::CREATE;
		currentState = InterpreterState::AWAITING_INDEX;
		break;
	case TokenType::VAPORIZE:
		commandInProgress.type = CommandType::VAPORIZE;
		currentState = InterpreterState::AWAITING_INDEX;
		break;
	default:
		CVV::error("Invalid character at : '" + token.token + "'. Expected COMMAND.");
		break;
	}
	return commandInProgress;
}

Command Interpreter::readCommandValue(Command commandInProgress, Token token)
{
	switch (token.type) {
	case TokenType::LITERAL:
		commandInProgress.num = stoi(token.token);
		break;
	case TokenType::AT:
		commandInProgress.num = tape.getValueAtIndex(stoi(token.token));
		break;
	default:
		CVV::error("Invalid character at : '" + token.token + "'. Expected LITERAL or AT (@).");
		break;
	}
	currentState = InterpreterState::AWAITING_DESCRIPTOR_OR_END;
	return commandInProgress;
}

Command Interpreter::readOperator(Command commandInProgress, Token token)
{
	if (token.type != TokenType::GREATER && token.type != TokenType::LESS && token.type != TokenType::EQUAL) {
		CVV::error("Invalid character at : '" + token.token + "'. Expected OPERATOR ('>', '<' '=')");
	}
	currentState = InterpreterState::AWAITING_DESCRIPTOR_VALUE;
	commandInProgress.oper = token.token[0];
	return commandInProgress;
}

Command Interpreter::readDescriptorValue(Command commandInProgress, Token token)
{
	switch (token.type) {
	case TokenType::LITERAL:
		commandInProgress.compareTo = stoi(token.token);
		break;
	case TokenType::AT:
		commandInProgress.compareTo = tape.getValueAtIndex(stoi(token.token));
		break;
	default:
		CVV::error("Invalid character at : '" + token.token + "'. Expected LITERAL or AT (@).");
		break;
	}

	currentState = InterpreterState::AWAITING_END;
	return commandInProgress;
}

Command Interpreter::readIndex(Command commandInProgress, Token token)
{
	switch (token.type) {
	case TokenType::LITERAL:
		commandInProgress.index = stoi(token.token);
		break;
	case TokenType::AT:
		commandInProgress.index = tape.getValueAtIndex(stoi(token.token));
		break;
	default:
		CVV::error("Invalid character at : '" + token.token + "'. Expected LITERAL or AT (@).");
		break;
	}
	currentState = InterpreterState::AWAITING_END;
	return commandInProgress;
}
