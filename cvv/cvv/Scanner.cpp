#include "Scanner.h"
#include <iostream>
#include <sstream>

Scanner::Scanner(std::string src)
{
    this->src = src;
    this->src = removeChar(this->src, '\n');
    this->src = removeChar(this->src, '\r');
    this->src = removeChar(this->src, '\a');
    this->src = removeChar(this->src, '\b');
    this->src = removeChar(this->src, '\f');
    this->src = removeChar(this->src, '\t');
    this->src = removeChar(this->src, '\v');
    this->start = 0;
    this->current = 0;
}

std::vector<Token> Scanner::scanSource()
{
    while (!isAtEnd()) {
        //	at the beginning of the next lexeme
        start = current;
        scanToken();
    }
    return tokens;
}

void Scanner::scanToken()
{
    char c = advance();

    switch (c) {
    case '+':
        tokens.push_back(Token(TokenType::PLUS, "+"));
        break;
    case '-':
        tokens.push_back(Token(TokenType::DASH, "-"));
        break;
    case '*':
        tokens.push_back(Token(TokenType::STAR, "*"));
        break;
    case '/':
        tokens.push_back(Token(TokenType::SLASH, "/"));
        break;
    case '|':
        tokens.push_back(Token(TokenType::PIPE, "|"));
        break;
    case '&':
        tokens.push_back(Token(TokenType::AND, "&"));
        break;
    case '<':
        tokens.push_back(Token(TokenType::LESS, "<"));
        break;
    case '>':
        tokens.push_back(Token(TokenType::GREATER, ">"));
        break;
    case '=':
        tokens.push_back(Token(TokenType::EQUAL, "="));
        break;
    case '?':
        tokens.push_back(Token(TokenType::QUESTION, "?"));
        break;
    case '@':
        tokens.push_back(Token(TokenType::AT, handleDigit()));
        break;
    case 'c':
        tokens.push_back(Token(TokenType::CREATE, "c"));
        break;
    case 'v':
        tokens.push_back(Token(TokenType::VAPORIZE, "v"));
        break;
    case ';':
        tokens.push_back(Token(TokenType::SEMICOLON, ";"));
        break;
    default:
        if (isdigit(c)) {
            tokens.push_back(Token(TokenType::LITERAL, c + handleDigit()));
        }
        else {
            CVV::error("Invalid token at " + c);
        }

        break;
    }
}

std::vector<std::string> Scanner::splitString(std::string str, char delimiter) {
    std::vector<std::string> result;
    std::string token;
    std::stringstream ss(str);

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

std::string Scanner::removeChar(std::string str, char charToRemove) {
    std::string result;
    for (char ch : str) {
        if (ch != charToRemove) {
            result += ch;
        }
    }
    return result;
}

bool Scanner::match(char expected)
{
    if (isAtEnd())
        return false;
    if (src[current] != expected)
        return false;
    current++;
    return true;
}

char Scanner::advance()
{
    return src[current++];
}

bool Scanner::isAtEnd()
{
    return current >= src.length();
}

char Scanner::peek()
{
    if (isAtEnd())
        return '\0';
    return src[current];
}

char Scanner::peekNext()
{
    if (current + 1 >= src.length())
        return '\0';
    return src[current + 1];
}

std::string Scanner::handleDigit()
{
    std::string indexAsString;
    while (isdigit(peek()) && !isAtEnd()) {
        indexAsString.push_back(advance());
    }
    return indexAsString;
}