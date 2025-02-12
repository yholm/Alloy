#ifndef TOKEN_H
#define TOKEN_H

#include <optional>
#include <string>

enum class TokenType {
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, LEFT_BRACKET, RIGHT_BRACKET,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR, COLON,

    AND, OR,

    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
    AND_AND, OR_OR,

    CHAR, STRING, INTEGER, FLOAT, IDENTIFIER, 
    
    _NULL, TRUE, FALSE, IF, FOR, WHILE, RETURN, LET, FN, REF, CLASS,
    CHAR_T, STR_T, FLOAT_T,
    I8, I16, I32, I64, 
    U8, U16, U32, U64,

    _EOF
};

struct Token {
public: 
    TokenType type;
    std::optional<std::string> value;

    Token(TokenType _type) : type(_type) {}
    Token(TokenType _type, std::string _value) : type(_type), value(_value) {}
};

#endif
