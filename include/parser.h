#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include <initializer_list>
#include "token.h"
#include "expr.h"

class Parser {
public:
    Parser(const std::vector<Token>& _tokens);
private:
    int current;
    std::vector<Token> tokens;
    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> comparison();
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> primary();
    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type);
    bool isAtEnd();
    std::shared_ptr<Token> peek();
    std::shared_ptr<Token> previous();
    std::shared_ptr<Token> advance();
    std::shared_ptr<Token> consume(TokenType token);
};

#endif
