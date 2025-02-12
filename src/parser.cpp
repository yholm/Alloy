#include "parser.h"

Parser::Parser(std::vector<Token> _tokens) {
    tokens = _tokens;
    current = 0;
}
