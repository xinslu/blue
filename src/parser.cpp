#include "parser.hpp"

Parser::~Parser() { this->lexed.clear(); }

Parser::Parser(std::vector<Lexed> lexed) {
  this->lexed = lexed;
  this->index = 0;
}

void Parser::parse() {
  Lexed lex = this->lexed[this->index];
  switch (lex.token) {
  case Token::FUNC:
    this->index++;
  }
}
