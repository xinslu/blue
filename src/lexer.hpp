#include <string>
#include <vector>
#include "types.hpp"

class Lexer {
public:
    // Fields
    bool stringMode;
    bool waitForDelim;
    int row;
    int col;
    int index;
    std::vector<Lexed> tokens;
    std::string input;
    std::string stringBuf;
    size_t length;

    // Constructors and Desctructors
    Lexer(std::string);
    Lexer(Lexer &&) = default;
    Lexer(const Lexer &) = default;
    Lexer &operator=(Lexer &&) = default;
    Lexer &operator=(const Lexer &) = default;
    ~Lexer();

    // Methods
    void tokenize();
    void print();

private:
    void handle_delimiter();
};

