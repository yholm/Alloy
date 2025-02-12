#include "lexer.h"

#include <iostream>
#include <stdlib.h>

Lexer::Lexer(const std::string& str) {
    source = str;
    tokens = std::vector<Token>();
    start = 0;
    current = 0;
}

std::vector<Token> Lexer::tokenize() {
    while (!isAtEnd()) {
        char c = advance();

        switch (c) {
            case '(': add_token(TokenType::LEFT_PAREN); break;
            case ')': add_token(TokenType::RIGHT_PAREN); break;
            case '{': add_token(TokenType::LEFT_BRACE); break;
            case '}': add_token(TokenType::RIGHT_BRACE); break;
            case '[': add_token(TokenType::LEFT_BRACKET); break;
            case ']': add_token(TokenType::RIGHT_BRACKET); break;

            case ',': add_token(TokenType::COMMA); break;
            case '.': add_token(TokenType::DOT); break;
            case ';': add_token(TokenType::SEMICOLON); break;
            case ':': add_token(TokenType::COLON); break;

            case '-': add_token(TokenType::MINUS); break;
            case '+': add_token(TokenType::PLUS); break;
            case '*': add_token(TokenType::STAR); break;
            case '/': 
                if (match('/')) while (peek() != '\n' && !isAtEnd()) advance();
                else add_token(TokenType::SLASH);
                break;
            case '&':
                add_token(match('&') ? TokenType::AND_AND : TokenType::AND);
                break;
            case '|':
                add_token(match('|') ? TokenType::OR_OR : TokenType::OR);
                break;
            case '!':
                add_token(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
                break;
            case '=':
                add_token(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
                break;
            case '>':
                add_token(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
                break;
            case '<':
                add_token(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
                break;
            
            case '\'': character(); break;
            case '"': string(); break;

            case ' ':
            case '\t':
            case '\n':
            case '\v':
            case '\r':
            case '\f':
                break;

            default:
                if (isalpha(c) || c == '_') identifier();
                else if (isdigit(c)) number();
                break;
        }
    }

    add_token(TokenType::_EOF);
    return tokens;
}

bool Lexer::isAtEnd() {
    return current >= source.length();
}

bool Lexer::match(char c) {
    if (isAtEnd()) return false;
    if (peek() != c) return false;
    advance();
    return true;
}

char Lexer::advance() {
    return source[current++];
}

char Lexer::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Lexer::peek_next() {
    if (isAtEnd()) return '\0';
    return source[current + 1];
}

void Lexer::add_token(TokenType type, std::string value) {
    if (value == "") tokens.push_back(Token(type));
    else tokens.push_back(Token(type, value));
}

void Lexer::identifier() {
    while (isalnum(peek()) || peek() == '_' || peek() == '-') advance();
    std::string name = source.substr(start, current - start);
    if (keywords.find(name) != keywords.end()) {
        tokens.push_back(Token(keywords.find(name)->second));
    } else {
        tokens.push_back(Token(TokenType::IDENTIFIER, name));
    } 
}

void Lexer::number() {
    bool is_float = false;

    while (isdigit(peek())) advance();
    if (peek() == '.' && isdigit(peek_next())) {
        is_float = true;
        advance();
        while (isdigit(peek())) advance();
    }

    if (is_float) add_token(TokenType::FLOAT, source.substr(start, current - start));
    else add_token(TokenType::INT, source.substr(start, current - start));
}

void Lexer::character() {
    while (peek() != '\'' && !isAtEnd()) {
        advance();
    }

    if (isAtEnd()) exit(EXIT_FAILURE);
    advance();

    if ((current - 1) - (start + 1) < 1) exit(EXIT_FAILURE);
    std::string literal = source.substr(start + 1, 1);

    if (literal == "\\") {
        char c = peek();
        switch (c) {
            case 'n': literal = "\n"; break;
            case 't': literal = "\t"; break;
            case 'r': literal = "\r"; break;
            case 'f': literal = "\f"; break;
            case 'v': literal = "\v"; break;
            case '\\': literal = "\\"; break;
            case '"': literal = "\""; break;
            case '\'': literal = "'"; break;
        }
    }

    add_token(TokenType::CHAR, literal);
}

void Lexer::string() {
    while (peek() != '\'' && !isAtEnd()) {
        advance();
    }

    if (isAtEnd()) exit(EXIT_FAILURE);
    advance();

    std::string literal = source.substr(start + 1, current - start - 1);
    add_token(TokenType::CHAR, literal);
}
