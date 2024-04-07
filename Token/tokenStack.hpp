#include <vector>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include "token.hpp"

// Define TokenType enum here (same as before)

// Define Token struct here (same as before)

class TokensStack {
private:
    std::vector<Token> tokens;
    int position;
    static const std::vector<TokenType> EMPTY_TOKENS;

public:
    TokensStack(const std::vector<Token>& tokensList) : tokens(tokensList), position(0) {}

    Token next(TokenType type, const std::vector<TokenType>& types) {
        skipEmptyTokens();
        std::vector<TokenType> allTypes = types;  // Copy the vector
        allTypes.push_back(type);
        if (position < tokens.size()) {
            Token token = tokens[position++];
            if (std::find(allTypes.begin(), allTypes.end(), token.type) != allTypes.end()) {
                return token;
            }
        }
        throw std::runtime_error("Expected token not found");
    }

    Token next(TokenType type, const std::string& value, const std::vector<std::string>& values) {
        skipEmptyTokens();
        if (position < tokens.size()) {
            std::vector<std::string> allValues = values;
            allValues.push_back(value);
            Token token = tokens[position++];
            if (token.type == type && std::find(allValues.begin(), allValues.end(), token.value) != allValues.end()) {
                return token;
            }
        }
        throw std::runtime_error("Expected token not found");
    }

    Token next() {
        skipEmptyTokens();
        if (position < tokens.size()) {
            return tokens[position++];
        }
        throw std::runtime_error("No more tokens available");
    }

    bool peek(TokenType type, const std::string& value, const std::vector<std::string>& values) {
        skipEmptyTokens();
        if (position < tokens.size()) {
            std::vector<std::string> allValues = values;
            allValues.push_back(value);
            Token token = tokens[position];
            return token.type == type && std::find(allValues.begin(), allValues.end(), token.value) != allValues.end();
        }
        return false;
    }

    bool peek(TokenType type, const std::vector<TokenType>& types) {
        skipEmptyTokens();
        if (position < tokens.size()) {
            Token token = tokens[position];
            return std::find(types.begin(), types.end(), token.type) != types.end();
        }
        return false;
    }

    bool peekSameLine(TokenType type, const std::string& value, const std::vector<std::string>& values) {
        return peek(type, value, values);
    }

    bool peekSameLine(TokenType type, const std::vector<TokenType>& types) {
        return peek(type, types);
    }

    void back() {
        if (position > 0) {
            position--;
        }
    }

private:
    void skipEmptyTokens() {
        while (position < tokens.size() && std::find(EMPTY_TOKENS.begin(), EMPTY_TOKENS.end(), tokens[position].type) != EMPTY_TOKENS.end()) {
            position++;
        }
    }
};

const std::vector<TokenType> TokensStack::EMPTY_TOKENS = {TokenType::LineBreak, TokenType::Comment};