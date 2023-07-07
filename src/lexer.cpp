#include "lexer.hpp"
#include <algorithm>
#include <iostream>
#include <string>


const std::unordered_map<std::string, Token> keyword_mapping = {
    {"int", Token::INT},      {"string", Token::STRING},
    {"float", Token::FLOAT},  {"bool", Token::BOOL},
    {"true", Token::TRUE},    {"false", Token::FALSE},
    {"and", Token::AND},      {"or", Token::OR},
    {"not", Token::NOT},      {"if", Token::IF},
    {"else", Token::ELSE},    {"void", Token::VOID},
    {"func", Token::FUNC},    {"print", Token::PRINT},
    {"struct", Token::STRUCT}};

const std::unordered_map<char, Token> delim_mapping = {
    {'{', Token::BRACE_OPEN}, {'}', Token::BRACE_CLOSE},
    {'(', Token::LEFT_PAREN}, {')', Token::RIGHT_PAREN},
    {':', Token::COLON},      {'=', Token::EQUAL},
    {'+', Token::PLUS},       {'-', Token::MINUS},
    {',', Token::COMMA},      {'*', Token::MULTIPLY},
    {'/', Token::DIVIDE},
};

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
    if (delim_mapping.find(token) != delim_mapping.end()) {
      handle_delimiter();
      this->append_token(delim_mapping.at(token));
    } else {

      switch (token) {
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
          this->tokens.push_back(
              Lexed(Token::STRING, this->stringBuf, this->row, this->col));
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
    }
    this->index++;
    this->col++;
  }
}

void Lexer::print() {
  for (auto i : this->tokens) {
    std::cout << i << std::endl;
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
      this->tokens.push_back(
          Lexed{Token::IDENTIFIER, this->stringBuf, this->row, this->col});
    }
    this->stringBuf = "";
  } else if (this->stringMode) {
    this->stringBuf.push_back(this->input[this->index]);
  }
}

void Lexer::append_token(Token token) {
  this->tokens.push_back(Lexed(token, this->row, this->col));
}
