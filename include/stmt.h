#ifndef STMT_H
#define STMT_H

#include <memory>
#include "expr.h"

class Stmt {
public:

};

class ExprStmt : public Stmt {
public:
    const std::shared_ptr<Expr> expr;

    ExprStmt(std::shared_ptr<Expr> _expr) 
        : expr(_expr) {}
};

class IfStmt : public Stmt {
public:
    const std::shared_ptr<Expr> condition;
    const std::shared_ptr<Stmt> stmt;
    const std::shared_ptr<Stmt> elseStmt;

    IfStmt(std::shared_ptr<Expr> _condition, std::shared_ptr<Stmt> _stmt) 
        : condition(_condition), stmt(_stmt) {}
    IfStmt(std::shared_ptr<Expr> _condition, std::shared_ptr<Stmt> _stmt, std::shared_ptr<Stmt> _elseStmt) 
        : condition(_condition), stmt(_stmt), elseStmt(_elseStmt) {}
};

#endif
