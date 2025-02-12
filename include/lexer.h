#ifndef LEXR_H
#define LEXR_H

#include <string>
#include <vector>
#include <map>
#include "token.h"

const std::map<std::string, TokenType> keywords {
    { "null",   TokenType::_NULL },
    { "true",   TokenType::TRUE },
    { "false",  TokenType::FALSE },
    { "if",     TokenType::IF },
    { "for",    TokenType::FOR },
    { "while",  TokenType::WHILE },
    { "return", TokenType::RETURN }, 
    { "let",    TokenType::LET },
    { "fn",     TokenType::FN },
    { "ref",    TokenType::REF },
    { "class",  TokenType::CLASS },
    { "char",   TokenType::CHAR_T },
    { "str",    TokenType::STR_T },
    { "float",  TokenType::FLOAT_T },
    { "i8",     TokenType::I8 },
    { "i16",    TokenType::I16 },
    { "i32",    TokenType::I32 },
    { "i64",    TokenType::I64 },
    { "u8",     TokenType::U8 },
    { "u16",    TokenType::U16 },
    { "u32",    TokenType::U32 },
    { "u64",    TokenType::U64 },
};

class Lexer {
private:
    std::string source;
    std::vector<Token> tokens;
    int start;
    int current;

    bool isAtEnd();
    bool match(char c);
    char advance();
    char peek();
    char peek_next();
    void add_token(TokenType type, std::string value = "");
    void identifier();
    void number();
    void character();
    void string();
public:
    Lexer(const std::string& str);
    std::vector<Token> tokenize();
};

#endif
