#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "tokens.h"

class Lexer {
    private:
        std::vector<Token> m_tokens;

        std::string strip_whitespace(std::string expr);

        Token create_token(char c);

        void parse_expr(std::string expr);

	void evaluate_expr();

    public:
        Lexer(std::string expr);
};

#endif
