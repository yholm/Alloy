#ifndef STMT_H
#define STMT_H

#include <memory>
#include "expr.h"

class Stmt {
public:

};

class ExprStmt {
public:
    const std::shared_ptr<Expr> expr;

    ExprStmt(std::shared_ptr<Expr> _expr) : expr(_expr) {}
};

class IfStmt {
public:
    
};

#endif
