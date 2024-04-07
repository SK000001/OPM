#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <stdexcept>
#include "Token/tokenType.hpp"

// Struct for Token
struct Token {
    TokenType type;
    std::string value;
    int rowNumber;
};

// Class LexicalParser
class LexicalParser {
private:
    std::vector<Token> tokens;
    std::string source;
    int rowNumber;

public:
    // Constructor
    LexicalParser(std::string sourceCode) : source(sourceCode), rowNumber(1) {}

    // Parse function
    static std::vector<Token> parse(std::string sourceCode) {
        LexicalParser parser(sourceCode);
        parser.parse();
        return parser.tokens;
    }

private:
    // Parse method
    void parse() {
        int position = 0;
        while (position < source.length()) {
            position += nextToken(position);
        }
    }

    // Find the next token
    int nextToken(int position) {
        std::string nextToken = source.substr(position);

        for (TokenType tokenType : {TokenType::Whitespace, TokenType::Keyword, TokenType::GroupDivider, TokenType::Logical, TokenType::Numeric, TokenType::Text, TokenType::Variable, TokenType::Operator}) {
            std::regex pattern("^" + getRegex(tokenType));
            std::smatch matches;
            if (std::regex_search(nextToken, matches, pattern)) {
                if (tokenType != TokenType::Whitespace) {
                    std::string value = matches.str(1);
                    Token token = {tokenType, value, rowNumber};
                    tokens.push_back(token);

                    if (tokenType == TokenType::LineBreak) {
                        rowNumber++;
                    }
                }
                return matches.str().length();
            }
        }

        throw std::runtime_error("Invalid expression at line " + std::to_string(rowNumber));
    }
};

int main() {
    // Example usage
    std::string sourceCode = "if (x < 10) { print(\"Hello, World!\"); }";
    std::vector<Token> tokens = LexicalParser::parse(sourceCode);
    std::cout << "Tokens:" << std::endl;
    for (const Token& token : tokens) {
        std::cout << "Type: " << static_cast<int>(token.type) << ", Value: " << token.value << ", Row Number: " << token.rowNumber << std::endl;
    }
    return 0;
}
