#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <iterator>

#include "token.h"

// The lexer is used to read an expression and only an expression.
// An expression will not contain any characters other than whole numbers
// and operators. This might change in the future.
class Lexer {
    private:
        // Each `Token` in the vector is stored in the order received through `expr`
        // when `expr` is passed in the constructor.
        std::vector<Token> m_tokens;

        // An iterator of `Token`
        std::vector<Token>::iterator m_iter;

        bool m_iter_finished;

        int result;

        // Strips `expr` of all spaces
        std::string strip_spaces(std::string expr);

        // Creates and returns `Token` from `c`
        Token create_token(char c);

        // Creates tokens and populates `m_tokens`
        void parse_expr(std::string expr);

        bool has_iter_finished();

        // Returns the current token in the iterator then advances it.
        // Will return immediately if iterator is already at its end.
        Token lookahead();

        int perform_operation(Token lhs, Token op, Token rhs);

    public:
        // Evaluates the expression.
        // `current_token` will always be an `Operand` never an `Operator`.
        int eval_expr(Token current_token=Token());
        Lexer(std::string expr);
};

#endif
