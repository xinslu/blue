#include "parser.hpp"

Parser::~Parser() {
    this->lexed.clear();
}

Parser::Parser(std::vector<Lexed> lexed) {
    this->lexed = lexed;
}

void Parser::parse() {
    for (size_t i = 0; i < this->lexed.size(); i++) {
        Lexed lex = this->lexed[i];
        switch (lex.token) {
        }
    }

}

