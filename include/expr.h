#ifndef EXPR_H
#define EXPR_H

#include <variant>
#include <string>
#include <memory>
#include "token.h"

template <typename T>
class IExprVisitor {
public:
    virtual T visitLiteral(Literal* literal) = 0;
    virtual T visitBinary(Binary* literal) = 0;
    virtual T visitUnary(Unary* literal) = 0;
};

class Expr {
public:
    virtual std::variant<int, double, std::string, bool> accept(IExprVisitor<std::variant<int, double, std::string, bool>>& visitor) = 0;
};

class Literal : public Expr {
public:
    using ValueType = std::variant<int, double, std::string, bool>;

    const ValueType value;
    Literal(ValueType _value) : value(_value) {}
    
    template <typename T>
    T accept(IExprVisitor<T>& visitor) {
        return visitor.visitLiteral(this);
    }
};

class Binary : public Expr {
public:
    const std::shared_ptr<Expr> lhs;
    const std::shared_ptr<Token> operation;
    const std::shared_ptr<Expr> rhs;

    Binary(std::shared_ptr<Expr> _lhs, 
           std::shared_ptr<Token> _operation, 
           std::shared_ptr<Expr> _rhs) : lhs(_lhs), operation(_operation), rhs(_rhs) {}

    template <typename T>
    T accept(IExprVisitor<T>& visitor) {
        return visitor.visitBinary(this);
    }
};

class Unary : public Expr {
public:
    const std::shared_ptr<Expr> rhs;
    const std::shared_ptr<Token> operation;

    Unary(std::shared_ptr<Token> _operation,
          std::shared_ptr<Expr> _rhs) : operation(_operation), rhs(_rhs) {}

    template <typename T>
    T accept(IExprVisitor<T>& visitor) {
        return visitor.visitUnary(this);
    }
};

#endif
