#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <iostream>

#include "tokens.h"

class Lexer {
    private:
        std::vector<Token> m_tokens;

        std::string strip_whitespace(std::string expr);
        Token create_token(char c);
        void parse_expr(std::string expr);
        void evaluate_expr(Token token);

    public:
        Lexer(std::string expr);
};

#endif
