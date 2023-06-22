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
      this->append_token(Token::BRACE_OPEN);
      break;
    case '}':
      handle_delimiter();
      this->append_token(Token::BRACE_CLOSE);
      break;
    case '(':
      handle_delimiter();
      this->append_token(Token::LEFT_PAREN);
      break;
    case ')':
      handle_delimiter();
      this->append_token(Token::RIGHT_PAREN);
      break;
    case ':':
      handle_delimiter();
      this->append_token(Token::COLON);
      break;
    case '=':
      handle_delimiter();
      this->append_token(Token::EQUAL);
      break;
    case '+':
      handle_delimiter();
      this->append_token(Token::PLUS);
      break;
    case '-':
      handle_delimiter();
      this->append_token(Token::MINUS);
      break;
    case ',':
      handle_delimiter();
      this->append_token(Token::COMMA);
      break;
    case '*':
      handle_delimiter();
      this->append_token(Token::MULTIPLY);
      break;
    case '/':
      handle_delimiter();
      this->append_token(Token::DIVIDE);
      break;
    case ' ':
      handle_delimiter();
      break;
    case '\n':
      handle_delimiter();
      this->row++;
      this->col = 0;
      break;
    case '\"':
      if (!this->stringMode) {
        handle_delimiter();
        this->stringMode = true;
      } else {
        this->stringMode = false;
        this->tokens.push_back(Lexed(Token::STRING, this->stringBuf, this->row, this->col));
        this->stringBuf = "";
      }
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

  if (!this->stringMode and this->stringBuf.length()) {
    if (keyword_mapping.find(this->stringBuf) != keyword_mapping.end()) {
        this->append_token(keyword_mapping.at(this->stringBuf));
    } else if (this->stringBuf.find_first_not_of("0123456789") ==
               std::string::npos) {
      this->tokens.push_back(
          Lexed(Token::INT_TYPE, this->stringBuf, this->row, this->col));
    } else if (std::count_if(this->stringBuf.begin(), this->stringBuf.end(),
                             [](char c) { return c == '.'; }) == 1) {
      this->tokens.push_back(
          Lexed(Token::FLOAT_TYPE, this->stringBuf, this->row, this->col));
    } else {
      this->tokens.push_back(Lexed{Token::IDENTIFIER, this->stringBuf, this->row, this->col});
    }
    this->stringBuf = "";
  } else if (this->stringMode) {
    this->stringBuf.push_back(this->input[this->index]);
  }
}

void Lexer::append_token(Token token) {
    this->tokens.push_back(Lexed(token, this->row, this->col));
}
