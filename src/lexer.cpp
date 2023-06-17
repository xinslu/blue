#include "lexer.hpp"

Lexer::Lexer(std::string file) {
    stringMode = false;
    row = 0;
    col = 0;
}

Lexer::~Lexer() {
}
