#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "lexer.cpp"
#include "parser.cpp"

int main(int argc, char *argv[]) {
    // If you only call the file with the bin, you should get an error.
    if (argc < 2) {
        std::cout << "blue: You must specify a file to compile!" << std::endl;
        return 1;
    }

    // Opens a file in binary mode and seeks to the end of the file
    std::ifstream inp_file(std::filesystem::current_path() / argv[1], std::ios::in | std::ios::binary | std::ios::ate);

    // Returns the position of the current character in the file, which is the file size
    std::ifstream::pos_type fileSize = inp_file.tellg();

    // Seek to the beginning of the file
    inp_file.seekg(0, std::ios::beg);

    // Read the file in bytes in data and convert to text.
    std::vector<char> bytes(fileSize);
    inp_file.read(bytes.data(), fileSize);
    std::string code = std::string(bytes.data(), fileSize);

    Lexer lexer = Lexer(code);

    lexer.tokenize();

    lexer.print();

    Parser parser = Parser(lexer.tokens);

    parser.parse();

    return 0;
}
