#pragma once
#include <string>
#include <vector>
#include "CVV.h"

enum class TokenType {
	PLUS = 0,
	DASH = 1,
	STAR = 2,
	SLASH = 3,
	AND = 4,
	PIPE = 5,
	QUESTION = 6,
	LESS = 7,
	GREATER = 8,
	EQUAL = 9,
	LITERAL = 10,
	AT = 11,
	SEMICOLON = 12,
	CREATE = 13,
	VAPORIZE = 14
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
		s += std::to_string((int)this->type);
		return s;
	}
};

class Scanner
{
public:
	Scanner(std::string src);
	std::vector<Token> scanSource();
private:
	int start;
	int current;

	void scanToken();
	std::string src;
	std::vector<Token> tokens;
	std::vector<std::string> splitString(std::string str, char delimiter);
	std::string removeChar(std::string str, char charToRemove);
	bool match(char expected);
	char advance();
	bool isAtEnd();
	char peek();
	char peekNext();
	std::string handleDigit();

};

