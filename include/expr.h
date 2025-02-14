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

class AssignExpr : public Expr {
public:
    const std::string name;
    const std::shared_ptr<Expr> value;

    AssignExpr(std::string _name, std::shared_ptr<Expr> _value) 
        : name(_name), value(_value) {}
};

class LogicExpr : public Expr {
    const std::shared_ptr<Expr> lhs;
    const std::shared_ptr<Token> operation;
    const std::shared_ptr<Expr> rhs;

    LogicExpr(std::shared_ptr<Expr> _lhs, 
              std::shared_ptr<Token> _operation, 
              std::shared_ptr<Expr> _rhs) 
        : lhs(_lhs), operation(_operation), rhs(_rhs) {}
};

template <typename R>
class LiteralExpr : public Expr {
public:
    const R value;
    LiteralExpr(R _value) : value(_value) {}
};

class BinaryExpr : public Expr {
public:
    const std::shared_ptr<Expr> lhs;
    const std::shared_ptr<Token> operation;
    const std::shared_ptr<Expr> rhs;

    BinaryExpr(std::shared_ptr<Expr> _lhs, 
           std::shared_ptr<Token> _operation, 
           std::shared_ptr<Expr> _rhs) : lhs(_lhs), operation(_operation), rhs(_rhs) {}
};

class UnaryExpr : public Expr {
public:
    const std::shared_ptr<Expr> rhs;
    const std::shared_ptr<Token> operation;

    UnaryExpr(std::shared_ptr<Token> _operation,
          std::shared_ptr<Expr> _rhs) : operation(_operation), rhs(_rhs) {}
};

class GroupingExpr : public Expr {
public:
    const std::shared_ptr<Expr> expr;

    GroupingExpr(std::shared_ptr<Expr> _expr) : expr(_expr) {}
};

class VarExpr : public Expr {
public:
    const std::shared_ptr<Token> name;

    VarExpr(std::shared_ptr<Token> _name) : name(_name) {}
};

#endif
