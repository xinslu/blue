#include <string>
#include <optional>
#include <vector>

enum Token {
    IDENTIFIER,
    NUMBER,
    INT,
    STRING_TYPE,
    STRING,
    FLOAT,
    FUNC,
    LEFT_PAREN,
    RIGHT_PAREN,
    EQUAL,
    RETURN,
    COLON,
    BRACE_OPEN,
    BRACE_CLOSE
};

const char *token_debug[] = {
    "IDENTIFIER",
    "NUMBER",
    "INT",
    "STRING_TYPE",
    "STRING",
    "FLOAT",
    "FUNC",
    "LEFT_PAREN",
    "RIGHT_PAREN",
    "EQUAL",
    "RETURN",
    "COLON",
    "BRACE_OPEN",
    "BRACE_CLOSE"
};

struct Lexed {
    Token token;
    std::optional<std::string> string;
    int row;
    int col;
};



