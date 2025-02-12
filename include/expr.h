#ifndef EXPR_H
#define EXPR_H

#include <variant>
#include <string>
#include <memory>
#include "token.h"

template <typename T>
class IExprVisitor;

class Expr {
public:

};

template <typename R>
class Literal : public Expr {
public:
    const R value;
    Literal(R _value) : value(_value) {}
};

class Binary : public Expr {
public:
    const std::shared_ptr<Expr> lhs;
    const std::shared_ptr<Token> operation;
    const std::shared_ptr<Expr> rhs;

    Binary(std::shared_ptr<Expr> _lhs, 
           std::shared_ptr<Token> _operation, 
           std::shared_ptr<Expr> _rhs) : lhs(_lhs), operation(_operation), rhs(_rhs) {}
};

class Unary : public Expr {
public:
    const std::shared_ptr<Expr> rhs;
    const std::shared_ptr<Token> operation;

    Unary(std::shared_ptr<Token> _operation,
          std::shared_ptr<Expr> _rhs) : operation(_operation), rhs(_rhs) {}
};

class Grouping : public Expr {
public:
    const std::shared_ptr<Expr> expr;

    Grouping(std::shared_ptr<Expr> _expr) : expr(_expr) {}
};

#endif
