#include <string>
#include <vector>
#include "types.hpp"

class Lexer {
public:
    // Fields
    bool stringMode;
    int row;
    int col;
    std::vector<Token> tokens;
    std::string input;

    // Constructors and Desctructors
    Lexer(std::string);
    Lexer(Lexer &&) = default;
    Lexer(const Lexer &) = default;
    Lexer &operator=(Lexer &&) = default;
    Lexer &operator=(const Lexer &) = default;
    ~Lexer();

    // Methods
    void tokenize();

private:

};

