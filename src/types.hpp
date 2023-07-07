#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

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

const char *token_debug[] = {
    "IDENTIFIER", "NUMBER", "INT",        "INT_TYPE",   "STRING_TYPE",
    "STRING",     "FLOAT",  "FLOAT_TYPE", "BOOL",       "TRUE",
    "FALSE",      "AND",    "OR",         "NOT",        "IF",
    "ELSE",       "VOID",   "FUNC",       "LEFT_PAREN", "RIGHT_PAREN",
    "EQUAL",      "RETURN", "COLON",      "BRACE_OPEN", "BRACE_CLOSE",
    "PLUS",       "MINUS",  "MULTIPLY",   "DIVIDE",     "COMMA",
    "PRINT",      "STRUCT"};

struct Lexed {
  public:
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

inline std::ostream& operator<< (std::ostream &out, const Lexed& data) {
    out << "Row: " << data.row + 1;
    out << " Column: " << data.col + 1;
    out << " Token Type: " << token_debug[data.token];
    if (data.string) {
      out << " String Value: " << *data.string << " ";
    }
    return out;
}

#endif // !TYPES_H
