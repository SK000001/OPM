#include <string>
#include <unordered_map>

enum class TokenType {
    Comment,
    LineBreak,
    Whitespace,
    Keyword,
    GroupDivider,
    Logical,
    Numeric,
    Null,
    This,
    Text,
    Operator,
    Variable
};

struct TokenTypeInfo {
    std::string regex;
};

const std::unordered_map<TokenType, TokenTypeInfo> tokenTypeInfoMap {
    {TokenType::Comment, {"\\#.*"}},
    {TokenType::LineBreak, {"[\\n\\r]"}},
    {TokenType::Whitespace, {"[\\s\\t]"}},
    {TokenType::Keyword, {"(if|elif|else|end|print|input|class|fun|return|loop|in|by|break|next|assert|raise|begin|rescue|ensure)(?=\\s|$)(?!_)"}},
    {TokenType::GroupDivider, {"(\\[|\\]|\\,|\\{|}|\\.{2}|(\\:(?!\\:)))"}},
    {TokenType::Logical, {"(true|false)(?=\\s|$)(?!_)"}},
    {TokenType::Numeric, {"([-]?(?=[.]?[0-9])[0-9]*(?![.]{2})[.]?[0-9]*)"}},
    {TokenType::Null, {"(null)(?=,|\\s|$)(?!_)"}},
    {TokenType::This, {"(this)(?=,|\\s|$)(?!_)"}},
    {TokenType::Text, {"\"([^\"]*)\""}},
    {TokenType::Operator, {"(\\+|-|\\*{1,2}|/{1,2}|%|>=?|<=|<{1,2}|={1,2}|!=|!|:{2}\\s+new|:{2}|\\(|\\)|(new|and|or|as|is)(?=\\s|$)(?!_))"}},
    {TokenType::Variable, {"[a-zA-Z_]+[a-zA-Z0-9_]*"}}
};

std::string getRegex(TokenType type) {
    return tokenTypeInfoMap.at(type).regex;
}
