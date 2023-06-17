#include <string>
class Lexer {
public:
    bool stringMode;
    int row;
    int col;
    Lexer(std::string);
    Lexer(Lexer &&) = default;
    Lexer(const Lexer &) = default;
    Lexer &operator=(Lexer &&) = default;
    Lexer &operator=(const Lexer &) = default;
    ~Lexer();

private:

};

