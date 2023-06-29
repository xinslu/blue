#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef TYPES_H
#define TYPES_H

enum Token {
  IDENTIFIER,
  NUMBER,
  INT,
  INT_TYPE,
  STRING_TYPE,
  STRING,
  FLOAT,
  FLOAT_TYPE,
  BOOL,
  TRUE,
  FALSE,
  AND,
  OR,
  NOT,
  IF,
  ELSE,
  VOID,
  FUNC,
  LEFT_PAREN,
  RIGHT_PAREN,
  EQUAL,
  RETURN,
  COLON,
  BRACE_OPEN,
  BRACE_CLOSE,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  COMMA,
  PRINT,
  STRUCT,
};

struct Lexed {
  Token token;
  std::optional<std::string> string;
  int row;
  int col;

  Lexed(Token token, int row, int col) {
    this->token = token;
    this->row = row;
    this->col = col;
  }

  Lexed(Token token, std::string value, int row, int col) {
    this->token = token;
    this->string = value;
    this->row = row;
    this->col = col;
  }
};

#endif // !TYPES_H
