#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "token.h"

class Parser {
public:
    Parser(std::vector<Token> _tokens);
private:
    int current;
    std::vector<Token> tokens;
};

#endif
