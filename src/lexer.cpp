#include "lexer.hpp"
#include <iostream>

Lexer::Lexer(std::string file) {
  this->stringMode = false;
  this->row = 0;
  this->col = 0;
  this->input = file;
  this->length = file.length();
  this->index = 0;
  this->waitForSpace = false;
  this->stringBuf = "";
}

Lexer::~Lexer() { this->tokens.clear(); }

void Lexer::tokenize() {
  while (this->index < this->length) {
    char token = this->input[this->index];
    switch (token) {
    case '{':
      this->tokens.push_back(Token::BRACE_OPEN);
      break;
    case '}':
      this->tokens.push_back(Token::BRACE_CLOSE);
      break;
    case '(':
      this->tokens.push_back(Token::LEFT_PAREN);
      break;
    case ')':
      this->tokens.push_back(Token::RIGHT_PAREN);
      break;
    case ':':
      this->tokens.push_back(Token::COLON);
      break;
    case '\n':
      this->row++;
      this->col = 0;
      break;
    case ' ':
        this->waitForSpace = false;
        if (this->stringBuf == "func") {
            this->tokens.push_back(Token::FUNC);
        } else if (this->stringBuf == "return") {
            this->tokens.push_back(Token::RETURN);
        } else if (this->stringBuf == "int") {
            this->tokens.push_back(Token::INT);
        } else if (this->stringBuf == "float") {
            this->tokens.push_back(Token::FLOAT);
        } else if (this->stringBuf == "string") {
            this->tokens.push_back(Token::STRING_TYPE);
        } else if (this->stringBuf == "string") {
            this->tokens.push_back(Token::STRING);
        } else {
            this->tokens.push_back(Token::IDENTIFIER);
        }
        this->stringBuf = "";
        break;
    default:
      if (this->waitForSpace == false) {
        this->waitForSpace = true;
      }
      this->stringBuf.push_back(token);
      break;
    }
    this->index++;
    this->col++;
  }
}
