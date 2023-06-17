#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "lexer.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "blue: You must specify a file to compile!" << std::endl;
        return 1;
    }

    std::ifstream inp_file(std::filesystem::current_path() / argv[1], std::ios::in);
    if (inp_file.is_open()) {
        std::string line;
        while (inp_file) {
            std::getline(inp_file, line);
            std::cout << line << std::endl;
        }
    }
    return 0;
}
