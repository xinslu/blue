#include "lexer.hpp"

Lexer::Lexer(std::string file) {
    this->stringMode = false;
    this->row = 0;
    this->col = 0;
    this->input = file;
}

Lexer::~Lexer() {
    this->tokens.clear();
}

void Lexer::tokenize() {
}
