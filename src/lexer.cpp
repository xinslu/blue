#include "lexer.hpp"
#include <algorithm>
#include <iostream>
#include <string>

int count_space(std::string s) {
  return std::count_if(s.begin(), s.end(),
                       [](unsigned char c) { return std::isspace(c); });
}

Lexer::Lexer(std::string file) {
  this->stringMode = false;
  this->row = 0;
  this->col = 0;
  this->input = file;
  this->length = file.length();
  this->index = 0;
  this->waitForDelim = false;
  this->stringBuf = "";
}

Lexer::~Lexer() { this->tokens.clear(); }

void Lexer::tokenize() {
  while (this->index < this->length) {
    char token = this->input[this->index];
    switch (token) {
    case '{':
      handle_delimiter();
      this->tokens.push_back(Lexed(Token::BRACE_OPEN, this->row, this->col));
      break;
    case '}':
      handle_delimiter();
      this->tokens.push_back(Lexed(Token::BRACE_CLOSE, this->row, this->col));
      break;
    case '(':
      handle_delimiter();
      this->tokens.push_back(Lexed(Token::LEFT_PAREN, this->row, this->col));
      break;
    case ')':
      handle_delimiter();
      this->tokens.push_back(Lexed(Token::RIGHT_PAREN, this->row, this->col));
      break;
    case ':':
      handle_delimiter();
      this->tokens.push_back(Lexed(Token::COLON, this->row, this->col));
      break;
    case '\n':
      handle_delimiter();
      this->row++;
      this->col = 0;
      break;
    case ' ':
      handle_delimiter();
      break;
    default:
      if (!this->waitForDelim) {
        this->waitForDelim = true;
      }
      this->stringBuf.push_back(token);
      break;
    }
    this->index++;
    this->col++;
  }
}

void Lexer::print() {
  for (auto i : this->tokens) {
    std::cout << "Row: " << i.row + 1;
    std::cout << " Column: " << i.col + 1;
    std::cout << " Token Type: " << token_debug[i.token];
    if (i.string) {
      std::cout << " String Value: " << *i.string << " ";
    }

    std::cout << std::endl;
  }
}

void Lexer::handle_delimiter() {
  this->waitForDelim = false;
  int processed = count_space(this->stringBuf);

  if (!this->stringMode) {
    if (this->stringBuf == "func") {
      this->tokens.push_back(Lexed(Token::FUNC, this->row, this->col));
    } else if (this->stringBuf == "return") {
      this->tokens.push_back(Lexed(Token::RETURN, this->row, this->col));
    } else if (this->stringBuf == "int") {
      this->tokens.push_back(Lexed(Token::INT, this->row, this->col));
    } else if (this->stringBuf == "float") {
      this->tokens.push_back(Lexed(Token::FLOAT, this->row, this->col));
    } else if (this->stringBuf == "string") {
      this->tokens.push_back(Lexed(Token::STRING, this->row, this->col));
    } else if (this->stringBuf.length()) {
      this->tokens.push_back(Lexed{Token::IDENTIFIER, this->stringBuf, this->row, this->col});
    }
  }
  this->stringBuf = "";
}
