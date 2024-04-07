#include <string>
#include "tokenType.hpp"

// Define Token struct
struct Token {
    TokenType type;
    std::string value;
    int rowNumber;
};