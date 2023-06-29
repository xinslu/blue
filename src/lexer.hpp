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
    ~Lexer();

    // Methods
    void tokenize();
    void print();

private:
    void handle_delimiter();
    void append_token(Token);
};
