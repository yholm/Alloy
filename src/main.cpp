#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "lexer.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: alloy [file]\n";
        exit(EXIT_FAILURE);
    }

    std::ifstream input(argv[1]);
    std::stringstream content_stream;

    content_stream << input.rdbuf();
    input.close();

    Lexer lexer = Lexer(content_stream.str());
    
    std::vector<Token> tokens = lexer.tokenize();

    return EXIT_SUCCESS;
}
