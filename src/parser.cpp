#include "parser.hpp"
#include <iostream>
#include <stdexcept>

Parser::~Parser() { this->lexed.clear(); }

Parser::Parser(std::vector<Lexed> lexed) {
  this->lexed = lexed;
  this->index = 0;
}

void Parser::parse() {
  Lexed &lex = this->lexed[this->index];
  switch (lex.token) {
  case Token::FUNC:
    this->increment_check(lex, Token::IDENTIFIER);
    FuncExpr func = FuncExpr();
    func.name = *lex.string;
    this->increment_check(lex, Token::LEFT_PAREN);
  }
}

void Parser::increment_check(Lexed &lex, Token expected) {
    this->index++;
    lex = this->get_current();
    this->expect_type(Token::LEFT_PAREN, lex);
}

Lexed Parser::get_current() {
    return this->lexed[this->index];
}

void Parser::expect_type(Token expected, Lexed current) {
    if (expected != current.token) {
        throw std::invalid_argument("blue: Expected "+std::string(token_debug[expected])+", got "+token_debug[current.token]+".");
    }

}
