#ifndef LEXR_H
#define LEXR_H

#include <optional>
#include <string>
#include <vector>
#include <map>

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

    _EOF
};

struct Token {
public: 
    TokenType type;
    std::optional<std::string> value;

    Token(TokenType _type);
    Token(TokenType _type, std::string _value);
};

const std::map<std::string, TokenType> keywords {
    { "null", TokenType::_NULL },
    { "true", TokenType::TRUE },
    { "false", TokenType::FALSE },
    { "if", TokenType::IF },
    { "for", TokenType::FOR },
    { "while", TokenType::WHILE },
    { "return", TokenType::RETURN }, 
    { "let", TokenType::LET },
    { "fn", TokenType::FN },
    { "ref", TokenType::REF },
    { "class", TokenType::CLASS }
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
