#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

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
};

const char *token_debug[] = {
    "IDENTIFIER", "NUMBER", "INT",        "INT_TYPE",   "STRING_TYPE",
    "STRING",     "FLOAT",  "FLOAT_TYPE", "BOOL",       "TRUE",
    "FALSE",      "AND",    "OR",         "NOT",        "IF",
    "ELSE",       "VOID",   "FUNC",       "LEFT_PAREN", "RIGHT_PAREN",
    "EQUAL",      "RETURN", "COLON",      "BRACE_OPEN", "BRACE_CLOSE",
    "PLUS",       "MINUS",  "MULTIPLY",   "DIVIDE",     "COMMA",
    "PRINT"};

const std::unordered_map<std::string, Token> keyword_mapping = {
    {"int", Token::INT},   {"string", Token::STRING}, {"float", Token::FLOAT},
    {"bool", Token::BOOL}, {"true", Token::TRUE},     {"false", Token::FALSE},
    {"and", Token::AND},   {"or", Token::OR},         {"not", Token::NOT},
    {"if", Token::IF},     {"else", Token::ELSE},     {"void", Token::VOID},
    {"func", Token::FUNC}, {"print", Token::PRINT}
};

const std::unordered_map<char, Token> delim_mapping = {
    {'{', Token::BRACE_OPEN}, {'}', Token::BRACE_CLOSE},
    {'(', Token::LEFT_PAREN}, {')', Token::RIGHT_PAREN},
    {':', Token::COLON},      {'=', Token::EQUAL},
    {'+', Token::PLUS},       {'-', Token::MINUS},
    {',', Token::COMMA},      {'*', Token::MULTIPLY},
    {'/', Token::DIVIDE},
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
