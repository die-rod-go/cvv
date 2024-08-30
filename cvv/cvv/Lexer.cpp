#include "Lexer.h"
#include <iostream>
#include <sstream>

Lexer::Lexer()
{
}

std::vector<std::vector<Token>> Lexer::tokenize(std::string src)
{
    src = removeChar(src, ' ');
    src = removeChar(src, '\n');
    std::vector<std::string> lines = splitString(src, ';');
    std::vector<std::vector<Token>> tokenizedLines;
    for (std::string line : lines) {
        tokenizedLines.push_back(scanLine(line));
    }
    return tokenizedLines;
}



std::vector<Token> Lexer::scanLine(std::string line)
{
    std::vector<Token> tokens;
    int index = 0;
    bool skip = false;
    for (char currChar : line) {
        std::cout << currChar << std::endl;
    }
    for (char currChar : line) {
        if (!skip) {
            switch (currChar) {
            case '+':
                tokens.push_back(Token(TokenType::ADD, "+"));
                break;
            case '-':
                std::cout << "minus: ";
                std::cout << currChar << std::endl;
                tokens.push_back(Token(TokenType::SUBTRACT, "-"));
                break;
            case '*':
                tokens.push_back(Token(TokenType::MULT, "*"));
                break;
            case '/':
                tokens.push_back(Token(TokenType::DIVIDE, "/"));
                break;
            case '|':
                tokens.push_back(Token(TokenType::OR, "|"));
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
                tokens.push_back(Token(TokenType::INDEX, "@"));
                //skip = true;
                break;
            default:
                std::string charAsString{ currChar };
                tokens.push_back(Token(TokenType::LITERAL, charAsString));
                break;
            }
        }
        skip = false;
        index++;
    }

    return tokens;
}

std::vector<std::string> Lexer::splitString(std::string str, char delimiter) {
    std::vector<std::string> result;
    std::string token;
    std::stringstream ss(str);

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

std::string Lexer::removeChar(std::string str, char charToRemove) {
    std::string result;
    for (char ch : str) {
        if (ch != charToRemove) {
            result += ch;
        }
    }
    return result;
}