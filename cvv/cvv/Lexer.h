#pragma once
#include <string>
#include <vector>

enum class TokenType {
	ADD = 0,
	SUBTRACT = 1,
	MULT = 2,
	DIVIDE = 3,
	AND = 4,
	OR = 5,
	QUESTION = 6,
	LESS = 7,
	GREATER = 8,
	EQUAL = 9,
	LITERAL = 10,
	INDEX = 11
};

struct Token {
	Token(TokenType type, std::string token) {
		this->type = type;
		this->token = token;
	}
	TokenType type;
	std::string token;
	std::string toString() {
		std::string s = token;
		s.push_back(' ');
		s.push_back(std::to_string((int)this->type).at(0));
		return s;
	}
};

class Lexer
{
public:
	Lexer();
	static std::vector<std::vector<Token>> tokenize(std::string src);
private:
	static std::vector<Token> scanLine(std::string line);
	static std::vector<std::string> splitString(std::string str, char delimiter);
	static std::string removeChar(std::string str, char charToRemove);
};

