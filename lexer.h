#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "token.h"

// The lexer is used to read an expression and only an expression.
// An expression will not contain any characters other than whole numbers
// and operators. This might change in the future.
class Lexer {
    private:
        // Each `Token` in the vector is stored in the order received through `expr`
        // when `expr` is passed in the constructor.
        std::vector<Token> m_tokens;

        std::string strip_whitespace(std::string expr);

        Token create_token(char c);

        void parse_expr(std::string expr);

    public:
        Lexer(std::string expr);
};

#endif
