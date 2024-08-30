#include "Interpreter.h"
#include <iostream>

struct Command {
    TokenType commandType;
    byte num;
    char oper;
    byte compareTo;
};

//  ASSUME ALL LINES ARE CURRENTLY VALID
bool Interpreter::runLine(Tape tape, std::vector<Token> line) 
{
    int lineSize = line.size();    
    if (lineSize < 2) {
        std::cout << "Error parsing line. Too Short" << std::endl;
        return false;
    }

    Command command;

    if (line[0].type == TokenType::ADD || line[0].type == TokenType::SUBTRACT || line[0].type == TokenType::MULT
        || line[0].type == TokenType::DIVIDE || line[0].type == TokenType::AND || line[0].type == TokenType::OR) {
        command.commandType = line[0].type;
    }
    else {
        std::cout << "Error parsing line. Expected COMMAND. Got: " << line[0].token << std::endl;
        return false;
    }

    if (line[1].type == TokenType::LITERAL) {
        command.num = line[1].token[0] - '0';
    }
        
    return false;
}

