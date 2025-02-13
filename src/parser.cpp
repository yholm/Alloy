#include "parser.h"

#include "stmt.h"

Parser::Parser(const std::vector<Token>& _tokens)
    : tokens(_tokens), current(0) {}


std::shared_ptr<Expr> Parser::expression() {
    return equality();
}

std::shared_ptr<Expr> Parser::equality() {
    std::shared_ptr<Expr> expr = comparison();

    if (match({TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL})) {
        std::shared_ptr<Token> operation = previous();
        std::shared_ptr<Expr> rhs = comparison();
        return std::make_shared<BinaryExpr>(expr, operation, rhs);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::comparison() {
    std::shared_ptr<Expr> expr = term();

    if (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
        std::shared_ptr<Token> operation = previous();
        std::shared_ptr<Expr> rhs = term();
        return std::make_shared<BinaryExpr>(expr, operation, rhs);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::term() {
    std::shared_ptr<Expr> expr = factor();

    while (match({TokenType::PLUS, TokenType::MINUS})) {
        std::shared_ptr<Token> operation = previous();
        std::shared_ptr<Expr> rhs = factor();
        return std::make_shared<BinaryExpr>(expr, operation, rhs);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::factor() {
    std::shared_ptr<Expr> expr = unary();

    while (match({TokenType::SLASH, TokenType::STAR})) {
        std::shared_ptr<Token> operation = previous();
        std::shared_ptr<Expr> rhs = unary();
        return std::make_shared<BinaryExpr>(expr, operation, rhs);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::unary() {
    if (match({TokenType::BANG, TokenType::MINUS})) {
        std::shared_ptr<Token> operation = previous();
        std::shared_ptr<Expr> rhs = unary();
        return std::make_shared<UnaryExpr>(operation, rhs);
    }

    return primary();
}

std::shared_ptr<Expr> Parser::primary() {
    if (match({TokenType::TRUE})) return std::make_shared<LiteralExpr<bool>>(true);
    if (match({TokenType::FALSE})) return std::make_shared<LiteralExpr<bool>>(false);
    if (match({TokenType::_NULL})) return std::make_shared<LiteralExpr<std::nullptr_t>>(nullptr);

    if (match({TokenType::STRING})) return std::make_shared<LiteralExpr<std::string>>(previous()->value.value());
    if (match({TokenType::CHAR})) return std::make_shared<LiteralExpr<char>>(previous()->value.value().at(0));
    if (match({TokenType::INT})) return std::make_shared<LiteralExpr<int>>(std::stoi(previous()->value.value()));
    if (match({TokenType::FLOAT})) return std::make_shared<LiteralExpr<float>>(std::stof(previous()->value.value()));

    if (match({TokenType::LEFT_PAREN})) {
        std::shared_ptr<Expr> expr = expression();
        consume(TokenType::RIGHT_PAREN);
        return std::make_shared<GroupingExpr>(expr);
    }

    exit(EXIT_FAILURE);
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }

    return false;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return peek()->type == type;
}

bool Parser::isAtEnd() {
    return peek()->type == TokenType::_EOF;
}

std::shared_ptr<Token> Parser::peek() {
    return std::make_shared<Token>(tokens[current]);
}

std::shared_ptr<Token> Parser::previous() {
    return std::make_shared<Token>(tokens[current - 1]);
}

std::shared_ptr<Token> Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

std::shared_ptr<Token> Parser::consume(TokenType token) {
    if (check(token)) return advance();
    exit(EXIT_FAILURE);
}
